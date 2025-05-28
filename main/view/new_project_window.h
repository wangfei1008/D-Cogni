#ifndef WINDOW_H
#define WINDOW_H

#include <DevMachines/QtitanNavigationDesignUI>
#include <DevMachines/QtitanStyle>
#include "settings.h"
#include "new_project_page_network.h"
#include "new_project_page_attribute.h"

class ProjectWindow : public NavigationMainWindow
{
    Q_OBJECT
public:
    ProjectWindow();
protected:
    virtual void paintEvent(QPaintEvent *);
private Q_SLOTS:
    void on_slot_finish_check();
    void on_slot_next_check();
private:
    NavigationView* m_view;
    SettingsWidget* m_settings;
    ProjectAttribute* m_page_attribute;
    NetworkDevicePage* m_page_device;
};

#endif
