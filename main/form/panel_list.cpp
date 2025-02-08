#include "panel_list.h"
#include <QTreeWidget>


panel_list::panel_list(const QString& name,  DCDockWindow* dock, QObject *parent)
    : panel_base(name, dock, parent)
{
    create(name);
}

int panel_list::create(const QString& name)
{
    QTreeWidget* treeWidget = new QTreeWidget;
    treeWidget->setAlternatingRowColors(true);
    treeWidget->setMinimumWidth(190);
    treeWidget->setHeaderHidden(true);

    QStringList strings;
    strings.append(tr("Item 1"));
    QTreeWidgetItem* mainItem = new QTreeWidgetItem(strings);
    mainItem->setCheckState(0, Qt::Checked);
    mainItem->setExpanded(false);
    mainItem->setIcon(0, QIcon(QStringLiteral(":/res/open16x16.png")));
    treeWidget->insertTopLevelItem(0, mainItem);

    strings.clear();
    strings.append(tr("Item 2"));
    QTreeWidgetItem* item = new QTreeWidgetItem(mainItem, strings);
    item->setCheckState(0, Qt::Checked);
    item->setIcon(0, QIcon(QStringLiteral(":/res/open16x16.png")));
    item->setExpanded(true);
    treeWidget->insertTopLevelItem(1, item);

    strings.clear();
    strings.append(tr("Item 3"));
    item = new QTreeWidgetItem(mainItem, strings);
    item->setCheckState(0, Qt::Checked);
    item->setIcon(0, QIcon(QStringLiteral(":/res/open16x16.png")));
    item->setExpanded(true);
    treeWidget->insertTopLevelItem(1, item);

    strings.clear();
    strings.append(tr("Item 4"));
    item = new QTreeWidgetItem(mainItem, strings);
    item->setCheckState(0, Qt::Checked);
    item->setIcon(0, QIcon(QStringLiteral(":/res/open16x16.png")));
    item->setExpanded(true);
    treeWidget->insertTopLevelItem(1, item);

    strings.clear();
    strings.append(tr("Item 5"));
    item = new QTreeWidgetItem(mainItem, strings);
    item->setCheckState(0, Qt::Checked);
    item->setIcon(0, QIcon(QStringLiteral(":/res/open16x16.png")));
    item->setExpanded(true);
    treeWidget->insertTopLevelItem(1, item);

    strings.clear();
    strings.append(tr("Item 6"));
    item = new QTreeWidgetItem(mainItem, strings);
    item->setCheckState(0, Qt::Checked);
    item->setIcon(0, QIcon(QStringLiteral(":/res/open16x16.png")));
    item->setExpanded(true);
    treeWidget->insertTopLevelItem(1, item);
    treeWidget->expandAll();

    set_widget(treeWidget);

    return 0;
}
