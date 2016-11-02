#include <QWidget>
#include "treeitem.h"

using namespace wb;

WbTreeItem::WbTreeItem(QWidget* data, WbTreeItem* parent)
{
    parentItem = parent;
    itemData = data;
}

WbTreeItem::WbTreeItem(const QString& label, WbTreeItem* parent)
{
    parentItem = parent;
    itemData = nullptr;
    this->label = label;
}

WbTreeItem::~WbTreeItem()
{
    qDeleteAll(childItems);
}

WbTreeItem* WbTreeItem::parent()
{
    return parentItem;
}

const WbTreeItem* WbTreeItem::parent() const
{
    return parentItem;
}

const WbTreeItem* WbTreeItem::child(int number) const
{
    return childItems.value(number);
}

WbTreeItem* WbTreeItem::child(int number)
{
    return childItems.value(number);
}

int WbTreeItem::childCount() const
{
    return childItems.count();
}

int WbTreeItem::childNumber() const
{
    if (parentItem)
    {
        return parentItem->childItems.indexOf(const_cast<WbTreeItem*>(this));
    }
    return 0;
}

int WbTreeItem::columnCount() const
{
    return 1;
}

QWidget* WbTreeItem::widget()
{
    return itemData;
}

QString WbTreeItem::toString() const
{
    if( !label.isEmpty() )
    {
        return label;
    }
    if ( !itemData )
    {
        return "(nullptr)";
    }
    if( !itemData->objectName().isEmpty() )
    {
        return QString("%1 [%2]").arg(itemData->objectName()).arg(itemData->metaObject()->className());
    }
    return itemData->metaObject()->className();
}

void WbTreeItem::setData(QWidget* value)
{
    itemData = value;
    label = "";
}

void WbTreeItem::setData(const QString& value)
{
    itemData = nullptr;
    label = value;
}

bool WbTreeItem::insertChildren(int position, int count)
{
    if( position < 0 || position > childItems.size() )
    {
        return false;
    }
    for( int row = 0; row < count; ++row ) {
        WbTreeItem* item = new WbTreeItem(nullptr, this);
        childItems.insert(position, item);
    }
    return true;
}

bool WbTreeItem::removeChildren(int position, int count)
{
    if( position < 0 || position + count > childItems.size() )
    {
        return false;
    }
    for( int row = 0; row < count; ++row )
    {
        delete childItems.takeAt(position);
    }
    return true;
}
