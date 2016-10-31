#include <QFileDialog>
#include <QFile>
#include <QMenu>
#include "capturelabel.h"

using namespace wb;

WbCaptureLabel::WbCaptureLabel(QWidget* parent)
    : QLabel(parent)
{
    setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
}

void WbCaptureLabel::capture(QWidget* widget)
{
    const QRect rectangle(QPoint(), widget->size());
    QPixmap pixmap(rectangle.size());
    widget->render(&pixmap, QPoint(), QRegion(rectangle));
    setPixmap(pixmap);
}

void WbCaptureLabel::contextMenuEvent(QContextMenuEvent* /*event*/)
{
    QMenu menu(this);
    menu.addAction(QString("Save Image"), this, &WbCaptureLabel::saveImage);
    menu.exec(QCursor::pos());
}

void WbCaptureLabel::saveImage()
{
    const QString fileName = QFileDialog::getSaveFileName(this, "Save Image", QString(), "Image File (*.png)");
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    pixmap()->save(&file, "PNG");
}
