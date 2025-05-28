#ifndef MENU_VIEW_H
#define MENU_VIEW_H

#include <QMenu>
#include <QObject>
#include <QAction>
#include "dock_window.h"
#include "menu_view_app_type.h"

class menu_view : public QObject
{
    Q_OBJECT
public:
    enum PanelType
    {
        LIST = 0,
        DATA = 1,
        SET = 2
    };
public:
    explicit menu_view(QMenu* menu, DCDockWindow* dock = nullptr, QObject *parent = nullptr);
    QStringList panel_names(PanelType type);
    menu_view_app_type *menu_view_app_stype();
private:
    void add_actions();
private Q_SLOTS:
    void slot_triggered(bool checked);
Q_SIGNALS:
    void signal_triggered(QString name, bool checked);
private:
    QMenu                        *m_menu;
    DCDockWindow                 *m_dock;
    QAction                      *m_list_project;
    QAction                      *m_list_device;
    QAction                      *m_list_monitor_device;
    QAction                      *m_data_runing;
    QAction                      *m_data_attribute;
    QAction                      *m_data_command;
    QAction                      *m_set_attribute;
    menu_view_app_type           *m_app_type;
};

#endif // MENU_VIEW_H
