#include <windows.h>
#include <QTimer>
#include <QThread>
#include <QApplication>
#include <QKeySequence>
#include <../../wb/listener.h>

class WBInstaller : public QObject
{
public:
	void install()
	{
		auto listener = new wb::WbOpenListener(qApp);
		qApp->installEventFilter(listener);
	}
};

class AppThread : public QThread
{
	void run() override
	{
		auto installer = new WBInstaller();
		installer->moveToThread(qApp->thread());
		QObject::connect(qApp, &QApplication::aboutToQuit, installer, &WBInstaller::deleteLater);
		QTimer::singleShot(0, installer, &WBInstaller::install);
	}
};

extern "C" __declspec(dllexport) BOOL WINAPI DllMain(HINSTANCE, DWORD fdwReason, LPVOID)
{
	if (fdwReason == DLL_PROCESS_ATTACH && qApp)
	{
		auto thread = new AppThread();
		QObject::connect(thread, &QThread::finished, thread, &QThread::deleteLater);
		thread->start();
	}
	return TRUE;
}
