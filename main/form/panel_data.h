#ifndef PANEL_DATA_H
#define PANEL_DATA_H

#include "panel_base.h"
#include <QObject>

class panel_data : public panel_base
{
    Q_OBJECT
public:
    explicit panel_data(const QString& name,  DCDockWindow* dock = nullptr,QObject *parent = nullptr);
private:
    int create(const QString& name) override;
    //int release() override;
};

#endif // PANEL_DATA_H
