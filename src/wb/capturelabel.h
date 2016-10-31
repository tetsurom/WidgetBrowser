#pragma once

#include <QLabel>

namespace wb {

class WbCaptureLabel : public QLabel
{
    Q_OBJECT
public:
    explicit WbCaptureLabel(QWidget* parent = nullptr);
public slots:
    void capture(QWidget* widget);
protected:
    void contextMenuEvent(QContextMenuEvent* event) override;
private:
    void saveImage();
};

}
