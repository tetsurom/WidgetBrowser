#pragma once

#include <QDialog>

namespace wb {

class WbCaptureLabel;
class WbWidgetTree;

class WbDialog : public QDialog
{
    Q_OBJECT
public:
    explicit WbDialog(QWidget* parent = nullptr);
private:
    WbWidgetTree* tree;
    WbCaptureLabel* snapshotLabel;
};

}
