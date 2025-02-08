#include "menu_view.h"
#include "menu_view_app_type.h"

menu_view::menu_view(QMenu* menu, DCDockWindow* dock, QObject *parent)
    : QObject{parent}
    , m_menu(menu)
    , m_dock(dock)
{
    add_actions();
}

QStringList menu_view::panel_names(PanelType type)
{
    return QStringList();
}

void menu_view::add_actions()
{
    //list...
    QMenu* menu_list = m_menu->addMenu(tr("Show list windows..."));
    m_list_project = new QAction(tr("Project"), this);
    m_list_project->setCheckable(true);
    connect(m_list_project, SIGNAL(triggered(bool)), this,  SLOT(slot_triggered(bool)));
    menu_list->addAction(m_list_project);
    m_list_device = new QAction(tr("Device"), this);
    m_list_device->setCheckable(true);
    connect(m_list_device, SIGNAL(triggered(bool)), this,  SLOT(slot_triggered(bool)));
    menu_list->addAction(m_list_device);
    m_list_monitor_device = new QAction(tr("Moniter device"), this);
    m_list_monitor_device->setCheckable(true);
    connect(m_list_monitor_device, SIGNAL(triggered(bool)), this,  SLOT(slot_triggered(bool)));
    menu_list->addAction(m_list_monitor_device);

    //data...
    QMenu* menu_data = m_menu->addMenu(tr("Show data windows..."));
    m_data_runing = new QAction(tr("Runing"), this);
    m_data_runing->setCheckable(true);
    connect(m_data_runing, SIGNAL(triggered(bool)), this,  SLOT(slot_triggered(bool)));
    menu_data->addAction(m_data_runing);
    m_data_attribute = new QAction(tr("Attribute"), this);
    m_data_attribute->setCheckable(true);
    connect(m_list_project, SIGNAL(triggered(bool)), this,  SLOT(slot_triggered(bool)));
    menu_data->addAction(m_data_attribute);
    m_data_command = new QAction(tr("Command"), this);
    connect(m_data_command, SIGNAL(triggered(bool)), this,  SLOT(slot_triggered(bool)));
    m_data_command->setCheckable(true);
    menu_data->addAction(m_data_command);

    //attribute
    m_set_attribute = new QAction(tr("Show attribute windows"), this);
    m_set_attribute->setCheckable(true);
    connect(m_set_attribute, SIGNAL(triggered(bool)), this,  SLOT(slot_triggered(bool)));
    m_menu->addAction(m_set_attribute);

    m_menu->addSeparator();

    //apptype
    menu_view_app_type* apptype = new menu_view_app_type(m_menu);
}

void menu_view::slot_triggered(bool checked)
{
    QAction* action_sender = qobject_cast<QAction*>(sender());
    if (action_sender == Q_NULL) return;

    Q_EMIT signal_triggered(action_sender->text(), checked);
}
