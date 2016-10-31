#include <QHBoxLayout>
#include <QApplication>
#include <QTreeView>
#include <QLabel>
#include <QScrollArea>
#include <QSplitter>
#include <QDesktopWidget>
#include "treeitem.h"
#include "widgettreemodel.h"
#include "widgettree.h"
#include "capturelabel.h"
#include "dialog.h"

namespace {
    QWidgetList wrapWithList(QWidget* widget)
    {
        QWidgetList list;
        list.append(widget);
        return list;
    }

    QWidget* widgetAtCursor()
    {
        return QApplication::widgetAt(QCursor::pos());
    }
}

using namespace wb;

WbDialog::WbDialog(QWidget* parent) : QDialog(parent)
{
    setWindowTitle("Widget Browser");

    QVector<std::pair<QString, QWidgetList>> list;

    list.push_back(std::make_pair(QString("Active Modal Widget"), wrapWithList(qApp->activeModalWidget())));
    list.push_back(std::make_pair(QString("Active Popup Widget"), wrapWithList(qApp->activePopupWidget())));
    list.push_back(std::make_pair(QString("Active Window"), wrapWithList(qApp->activeWindow())));
    list.push_back(std::make_pair(QString("Focus Widget"), wrapWithList(qApp->focusWidget())));
    list.push_back(std::make_pair(QString("Widget at Cursor"), wrapWithList(widgetAtCursor())));
    list.push_back(std::make_pair(QString("Top Level Widgets"), qApp->topLevelWidgets()));

    tree = new WbWidgetTree(list, this);

    QScrollArea* area = new QScrollArea();
    area->setBackgroundRole(QPalette::Dark);
    area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    area->setWidgetResizable(true);

    snapshotLabel = new WbCaptureLabel(this);
    area->setWidget(snapshotLabel);

    QSplitter* splitter = new QSplitter(Qt::Horizontal);
    splitter->addWidget(tree);
    splitter->addWidget(area);

    QList<int> sizes;
    sizes << 200 << 450;
    splitter->setSizes(sizes);

    resize(QDesktopWidget().availableGeometry(this).size() * 0.5);

    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(splitter);
    this->setLayout(layout);

    connect(tree, &WbWidgetTree::widgetSelected, snapshotLabel, &WbCaptureLabel::capture);
}
