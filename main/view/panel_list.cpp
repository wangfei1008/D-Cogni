#include "panel_list.h"
#include <QHeaderView>

project_tree::project_tree(QWidget *parent)
    :QTreeWidget(parent)
{
    this->setAlternatingRowColors(true);
    this->setMinimumWidth(190);
    this->setHeaderHidden(true);
    this->setIconSize(QSize(64, 64));
}

void project_tree::add(const QString &name)
{
    QStringList strings;
    strings.append(name);
    QTreeWidgetItem* item = new QTreeWidgetItem(strings);
    item->setExpanded(false);
    item->setIcon(0, QIcon(QStringLiteral(":res/image/project64x64.png")));
    this->insertTopLevelItem(0, item);
    m_map.insert(name,item);
}

device_tree::device_tree(QWidget *parent)
{
    this->setAlternatingRowColors(true);
    this->setMinimumWidth(190);
    this->setHeaderHidden(true);
    this->setIconSize(QSize(48, 48));
}

void device_tree::add(const QString &name)
{
    QStringList strings;
    //strings.append();
    QTreeWidgetItem* main_item = new QTreeWidgetItem(strings);
    main_item->setExpanded(false);
    main_item->setIcon(0, QIcon(QStringLiteral(":res/image/firm_logo48x48.png")));
    this->insertTopLevelItem(0, main_item);
    m_map.insert(name,main_item);

    strings.clear();
    strings.append(tr("2001"));
    QTreeWidgetItem* item = new QTreeWidgetItem(main_item, strings);
    item->setIcon(0, QIcon(QStringLiteral(":res/image/device/2001.png")));
    item->setExpanded(true);
    this->insertTopLevelItem(1, item);

    strings.clear();
    strings.append(tr("2002"));
    item = new QTreeWidgetItem(main_item, strings);
    item->setIcon(0, QIcon(QStringLiteral(":res/image/device/2002.png")));
    item->setExpanded(true);
    this->insertTopLevelItem(1, item);

}

moniter_device_tree::moniter_device_tree(QWidget *parent)
{
    this->setAlternatingRowColors(true);
    this->setMinimumWidth(190);
    this->setHeaderHidden(true);
    this->setIconSize(QSize(48, 48));
    this->setHeaderItem(new QTreeWidgetItem());
    this->setColumnCount(3);
    this->setHeaderHidden(true);
    QHeaderView* head = this->header();
    head->setSectionResizeMode(0,QHeaderView::Stretch);
    head->setSectionResizeMode(1, QHeaderView::Fixed);
    head->setSectionResizeMode(2, QHeaderView::Fixed);
    this->setColumnWidth(1, 30);
    this->setColumnWidth(2, 30);
    // 4.（最重要的一步）去掉默认的拉伸最后列属性
    head->setStretchLastSection(false);
}

void moniter_device_tree::add(const QString &name)
{
    QStringList strings;
    strings.append(tr("project 1"));
    QTreeWidgetItem* main_item = new QTreeWidgetItem(strings);;
    main_item->setExpanded(false);
    main_item->setIcon(0, QIcon(QStringLiteral(":res/image/project64x64.png")));
    this->insertTopLevelItem(0, main_item);


    strings.clear();
    strings.append(tr("device 2002"));
    QTreeWidgetItem* item = new QTreeWidgetItem(main_item, strings);
    item->setIcon(0, QIcon(QStringLiteral(":res/image/device/2002.png")));
    item->setExpanded(true);
    this->insertTopLevelItem(1, item);

    strings.clear();
    strings<<"1"<<"1.1"<<"1.2";
    QTreeWidgetItem* metadata_item = new QTreeWidgetItem(item, strings);
    metadata_item->setCheckState(0, Qt::Checked);
    metadata_item->setExpanded(true);
    this->insertTopLevelItem(1, metadata_item);

    strings.clear();
    strings.append(tr("2"));
    metadata_item = new QTreeWidgetItem(item, strings);
    metadata_item->setCheckState(0, Qt::Checked);
    metadata_item->setExpanded(true);
    this->insertTopLevelItem(2, metadata_item);

    strings.clear();
    strings.append(tr("3"));
    metadata_item = new QTreeWidgetItem(item, strings);
    metadata_item->setCheckState(0, Qt::Checked);
    metadata_item->setExpanded(true);
    this->insertTopLevelItem(1, metadata_item);
}

panel_list::panel_list(const QString& name,  DCDockWindow* dock, QObject *parent)
    : panel_base(name, dock, parent)
{
    m_names << "Project" << "Device" << "Moniter device";
    create(name);
}

int panel_list::create(const QString& name)
{
    QTreeWidget* treeWidget = NULL;
    if(name.compare("Project") == 0)
    {
        treeWidget = new project_tree();
        ((project_tree*)treeWidget)->add("project 1");
        ((project_tree*)treeWidget)->add("project 2");
    }
    else
    {
        if(name.compare("Device") == 0)
        {
            treeWidget = new device_tree();
            ((device_tree*)treeWidget)->add("2001");
            //((device_tree*)treeWidget)->add("project 2");
        }
        else
        {
            treeWidget = new moniter_device_tree();
            ((moniter_device_tree*)treeWidget)->add("2001");
        }
    }
    treeWidget->expandAll();

    set_widget(treeWidget);

    return 0;
}
