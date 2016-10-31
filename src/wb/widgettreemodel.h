#pragma once

#include <QWidgetList>
#include <QAbstractItemModel>

namespace wb {

class WbTreeItem;

class WbWidgetTreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit WbWidgetTreeModel(const QVector<std::pair<QString, QWidgetList>>& topLevels, QObject* parent = nullptr);
    ~WbWidgetTreeModel();

    QVariant data(const QModelIndex& index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex& index) const override;

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    const WbTreeItem* getItem(const QModelIndex& index) const;
    WbTreeItem* getItem(const QModelIndex& index);

    QWidget* getWidget(const QModelIndex& index);

private:
    void setupModelData(QWidget* widget, WbTreeItem* parent);
    void setupModelData(const QWidgetList& widgets, WbTreeItem* parent);

    WbTreeItem* rootItem;
};

}
