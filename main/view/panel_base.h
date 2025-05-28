#ifndef PANEL_BASE_H
#define PANEL_BASE_H

#include <DevMachines/QtitanBase>
#include <DevMachines/QtitanDocking>
#include "dock_window.h"


class panel_base : public QObject
{
    Q_OBJECT
public:
    explicit panel_base(const QString& name,  DCDockWindow* dock = nullptr,QObject *parent = nullptr);

    DockWidgetPanel* panel();
protected:
    void set_widget(QWidget* widget);

private:
    virtual int create(const QString& name) = 0;
    virtual int release(){return 0;};
private:
    QString                                m_name;
    DCDockWindow                           *m_dock;
    DockWidgetPanel                        *m_panel;
};

#endif // PANEL_BASE_H
