#include <iostream>
#include <memory>
#include <functional>
#include <windows.h>

using unique_handle = std::unique_ptr<std::remove_pointer_t<HANDLE>, decltype(&::CloseHandle)>;
using unique_remote_memory = std::unique_ptr<std::remove_pointer_t<LPVOID>, std::function<void(LPVOID)>>;

static std::system_error make_system_error(DWORD error)
{
	LPSTR msgBuffer = nullptr;
	::FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, error,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		msgBuffer, 0, nullptr);
	auto syserror = std::system_error(static_cast<int>(error), std::system_category(), msgBuffer);
	::LocalFree(msgBuffer);
	return syserror;
}

static unique_handle open_process(DWORD pid, DWORD desiredAccess)
{
	auto hp = ::OpenProcess(desiredAccess, FALSE, pid);
	if (!hp) { throw std::runtime_error("OpenProcess failed"); }
	return { hp, &::CloseHandle };
}

static unique_remote_memory remote_alloc(HANDLE proc, size_t size)
{
	auto ptr = ::VirtualAllocEx(proc, nullptr, size, MEM_COMMIT, PAGE_READWRITE);
	if (!ptr) { throw std::runtime_error("VirtualAllocEx failed"); }
	return { ptr, [=](LPVOID remote_ptr) { ::VirtualFreeEx(proc, remote_ptr, 0, MEM_RELEASE); } };
}

static unique_handle create_remote_thread(HANDLE proc, PTHREAD_START_ROUTINE routine, LPVOID parameter)
{
	::SetLastError(NO_ERROR);
	auto ht = ::CreateRemoteThread(proc, nullptr, 0, routine, parameter, 0, nullptr);
	if (!ht) throw make_system_error(::GetLastError());
	return { ht, &::CloseHandle };
}

static PTHREAD_START_ROUTINE get_start_routine(const char* dll, const char* function)
{
	auto routine = reinterpret_cast<PTHREAD_START_ROUTINE>(::GetProcAddress(::GetModuleHandleA(dll), function));
	if (!routine) { throw std::runtime_error("GetProcAddress failed"); }
	return routine;
}

static unique_remote_memory write_remote_buffer(HANDLE proc, const void* buffer, size_t size)
{
	auto remote_ptr = remote_alloc(proc, size);
	if (!::WriteProcessMemory(proc, remote_ptr.get(), buffer, size, nullptr)) {
		throw std::runtime_error("WriteProcessMemory failed");
	}
	return remote_ptr;
}

static DWORD wait_thread(HANDLE hThread)
{
	::WaitForSingleObject(hThread, INFINITE);
	DWORD exitCode;
	::GetExitCodeThread(hThread, &exitCode);
	return exitCode;
}

static void inject(DWORD pid, const std::string& dllname)
{
	auto process = open_process(pid, PROCESS_CREATE_THREAD | PROCESS_VM_OPERATION | PROCESS_VM_WRITE);
	auto remote_ptr = write_remote_buffer(process.get(), dllname.c_str(), dllname.size() + 1);
	auto thread = create_remote_thread(process.get(), get_start_routine("Kernel32", "LoadLibraryA"), remote_ptr.get());

	std::cout << "Waiting remote thread ..." << std::endl;
	const DWORD exitCode = wait_thread(thread.get());
	std::cout << "Completed. Exit with " << exitCode << std::endl;
}

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cout << "usage: " << argv[0] << " pid dllpath" << std::endl;
		return 0;
	}
	const int pid = atoi(argv[1]);
	try
	{
		inject(pid, argv[2]);
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	return 0;
}
