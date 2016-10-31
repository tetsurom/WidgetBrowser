#pragma once
#include <QWidgetList>
#include <QTreeView>

class QItemSelectionModel;
class QContextMenuEvent;

namespace wb {

class WbWidgetTreeModel;

class WbWidgetTree : public QTreeView
{
    Q_OBJECT
public:
    explicit WbWidgetTree(const QVector<std::pair<QString, QWidgetList>>& topLevels, QWidget* parent = nullptr);
signals:
    void widgetSelected(QWidget*);
public slots:
    void copyClassName();
protected:
    void selectionChanged(const QItemSelection& selected, const QItemSelection& deselected) override;
    void contextMenuEvent(QContextMenuEvent* event) override;
private:
    WbWidgetTreeModel* model;
};

}
