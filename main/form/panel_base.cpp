#include "panel_base.h"

panel_base::panel_base(const QString& name,  DCDockWindow* dock, QObject *parent)
    : QObject{parent}
    , m_name(name)
    , m_dock(dock)
{
    m_panel = new DockWidgetPanel(name, m_dock->dockPanelManager());
}

DockWidgetPanel *panel_base::panel()
{
    return m_panel;
}

void panel_base::set_widget(QWidget *widget)
{
    m_panel->setWidget(widget);
}
