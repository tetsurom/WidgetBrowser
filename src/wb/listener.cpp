#include <QKeyEvent>
#include <QKeySequence>

#include "dialog.h"
#include "listener.h"

using namespace wb;

WbOpenListener::WbOpenListener(QObject* parent)
    : QObject(parent)
    , keySequenceToOpen("Meta+F2")
    , isOpened(false)
{
}

void WbOpenListener::setKeySequenceToOpen(const QKeySequence& sequence)
{
    keySequenceToOpen = sequence;
}

static QKeySequence keySeqFromEvent(QEvent* event)
{
    QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
    return QKeySequence(keyEvent->modifiers() | keyEvent->key());
}

bool WbOpenListener::eventFilter(QObject* /*obj*/, QEvent* event)
{
    if ( !isOpened && event->type() == QEvent::KeyPress )
    {
        if ( keySeqFromEvent(event).matches(keySequenceToOpen) )
        {
            isOpened = true;
            WbDialog dialog;
            dialog.exec();
            isOpened = false;
            return true;
        }
    }
    return false;
}
