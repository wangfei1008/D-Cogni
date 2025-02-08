#ifndef PANEL_LIST_H
#define PANEL_LIST_H

#include <QObject>
#include "panel_base.h"

class panel_list : public panel_base
{
    Q_OBJECT
public:
    explicit panel_list(const QString& name,  DCDockWindow* dock = nullptr,QObject *parent = nullptr);

private:
    int create(const QString& name) override;
    //int release() override;
};

#endif // PANEL_LIST_H
