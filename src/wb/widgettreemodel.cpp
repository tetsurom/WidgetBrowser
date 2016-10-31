#include <QWidget>
#include <QVector>
#include "widgettreemodel.h"
#include "treeitem.h"

using namespace wb;

WbWidgetTreeModel::WbWidgetTreeModel(const QVector<std::pair<QString, QWidgetList>>& topLevels, QObject* parent)
    : QAbstractItemModel(parent)
{
    rootItem = new WbTreeItem("Hierarchy");

    for( const auto& p : topLevels )
    {
        rootItem->insertChildren(rootItem->childCount(), rootItem->columnCount());
        WbTreeItem* toplevel = rootItem->child(rootItem->childCount() - 1);
        toplevel->setData(p.first);
        setupModelData(p.second, toplevel);
    }
}

WbWidgetTreeModel::~WbWidgetTreeModel()
{
    delete rootItem;
}

const WbTreeItem* WbWidgetTreeModel::getItem(const QModelIndex& index) const
{
    if( index.isValid() )
    {
        if( WbTreeItem* item = static_cast<WbTreeItem*>(index.internalPointer()) )
        {
            return item;
        }
    }
    return rootItem;
}

WbTreeItem* WbWidgetTreeModel::getItem(const QModelIndex& index)
{
    return const_cast<WbTreeItem*>(const_cast<const WbWidgetTreeModel*>(this)->getItem(index));
}

QWidget* WbWidgetTreeModel::getWidget(const QModelIndex& index)
{
    return getItem(index)->widget();
}

int WbWidgetTreeModel::rowCount(const QModelIndex& parent) const
{
    return getItem(parent)->childCount();
}

int WbWidgetTreeModel::columnCount(const QModelIndex& /* parent */) const
{
    return 1;
}

QModelIndex WbWidgetTreeModel::index(int row, int column, const QModelIndex& parent) const
{
    if( parent.isValid() && parent.column() != 0 )
    {
        return QModelIndex();
    }
    const WbTreeItem* parentItem = getItem(parent);
    const WbTreeItem* childItem = parentItem->child(row);
    if( childItem )
    {
        return createIndex(row, column, (void*)childItem);
    }
    else
    {
        return QModelIndex();
    }
}

QVariant WbWidgetTreeModel::data(const QModelIndex& index, int role) const
{
    if( !index.isValid() )
    {
        return QVariant();
    }
    if( role != Qt::DisplayRole && role != Qt::EditRole )
    {
        return QVariant();
    }
    return getItem(index)->toString();
}

QVariant WbWidgetTreeModel::headerData(int /*section*/, Qt::Orientation orientation, int role) const
{
    if( orientation == Qt::Horizontal && role == Qt::DisplayRole )
    {
        return rootItem->toString();
    }
    return QVariant();
}

QModelIndex WbWidgetTreeModel::parent(const QModelIndex& index) const
{
    if( !index.isValid() )
    {
        return QModelIndex();
    }
    const WbTreeItem* childItem = getItem(index);
    const WbTreeItem* parentItem = childItem->parent();

    if( parentItem == rootItem )
    {
        return QModelIndex();
    }
    return createIndex(parentItem->childNumber(), 0, (void*)parentItem);
}

void WbWidgetTreeModel::setupModelData(QWidget* rootWidget, WbTreeItem* parent)
{
    foreach( QWidget* widget, rootWidget->findChildren<QWidget*>(QString(), Qt::FindDirectChildrenOnly) )
    {
        parent->insertChildren(parent->childCount(), rootItem->columnCount());
        WbTreeItem* child = parent->child(parent->childCount() - 1);
        child->setData(widget);
        setupModelData(widget, child);
    }
}

void WbWidgetTreeModel::setupModelData(const QWidgetList& widgets, WbTreeItem* parent)
{
    foreach( QWidget* widget, widgets )
    {
        parent->insertChildren(parent->childCount(), parent->columnCount());
        WbTreeItem* child = parent->child(parent->childCount() - 1);
        child->setData(widget);
        setupModelData(widget, child);
    }
}
