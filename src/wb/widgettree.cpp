#include <QApplication>
#include <QClipboard>
#include <QCursor>
#include <QMenu>
#include "treeitem.h"
#include "widgettreemodel.h"
#include "widgettree.h"

using namespace wb;

WbWidgetTree::WbWidgetTree(const QVector<std::pair<QString, QWidgetList>>& topLevels, QWidget* parent)
    : QTreeView(parent)
{
    model = new WbWidgetTreeModel(topLevels, this);
    setModel(model);
    setSelectionMode(QAbstractItemView::SingleSelection);
}

void WbWidgetTree::copyClassName()
{
    if( const QWidget* widget = model->getWidget(currentIndex()) )
    {
        QApplication::clipboard()->setText(widget->metaObject()->className());
    }
}

void WbWidgetTree::selectionChanged(const QItemSelection& selected, const QItemSelection& /*deselected*/)
{
    if( selected.indexes().isEmpty() )
    {
        return;
    }
    if( QWidget* widget = model->getWidget(selected.indexes().first()) )
    {
        emit widgetSelected(widget);
    }
}

void WbWidgetTree::contextMenuEvent(QContextMenuEvent* /*event*/)
{
    if( const QWidget* widget = model->getWidget(currentIndex()) )
    {
        QMenu menu(this);
        menu.addAction(QString("Copy Class Name"), this, &WbWidgetTree::copyClassName);
        menu.exec(QCursor::pos());
    }
}

