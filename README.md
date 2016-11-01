# WidgetBrowser
Widget Browser is easy, simple, useful debugging support tool for Qt application.

![Screen Shot](https://github.com/tetsurom/WidgetBrowser/wiki/image/wbss.png "Screen Shot")

# Features

* Explore widgets hierarchy
* Copy widget's class name
* Take widget's snapshot

# Install

Copy `src/wb` to your Qt project. Then just call `wb::WbDialog::exec`.

```cpp
#include <wb/dialog.h>
⋮
wb::WbDialog dialog;
dialog.exec();
```
`WbDialog` gathers widgets information from `QApplication` automatically.

To launch Widget Browser with a hotkey, you can use `WbOpenListener`; an event filter to exec `WbDialog`.

```cpp
#include <QApplication>
#include <QKeySequence>
#include <wb/listener.h>
⋮
WbOpenListener listener;
listener.setKeySequenceToOpen(QKeySequence("Meta+F2"));
qApp->installEventfilter(&listener);
```
