#pragma once

#include <QLine>
#include <QVector>
#include <QVariant>

namespace wb {

class WbTreeItem
{
public:
    explicit WbTreeItem(QWidget* widget, WbTreeItem* parent = 0);
    explicit WbTreeItem(const QString& label, WbTreeItem* parent = 0);
    ~WbTreeItem();

    const WbTreeItem* child(int number) const;
    WbTreeItem* child(int number);
    int childCount() const;
    int columnCount() const;
    QWidget* widget();
    QString toString() const;
    bool insertChildren(int position, int count);
    WbTreeItem* parent();
    const WbTreeItem* parent() const;
    bool removeChildren(int position, int count);
    int childNumber() const;
    void setData(QWidget* value);
    void setData(const QString& value);

private:
    QList<WbTreeItem*> childItems;
    QWidget* itemData;
    QString label;
    WbTreeItem* parentItem;
};

}
