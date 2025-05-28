#ifndef PANEL_LIST_H
#define PANEL_LIST_H

#include <QObject>
#include <QTreeWidget>
#include "panel_base.h"

class project_tree:public QTreeWidget
{
    Q_OBJECT
public:
    explicit project_tree(QWidget *parent = nullptr);
    void add(const QString& name);
private:
    QMap<QString, QTreeWidgetItem*> m_map;
};

class device_tree:public QTreeWidget
{
    Q_OBJECT
public:
    explicit device_tree(QWidget *parent = nullptr);
    void add(const QString& name);
private:
    QMap<QString, QTreeWidgetItem*> m_map;
};

class moniter_device_tree:public QTreeWidget
{
    Q_OBJECT
public:
    explicit moniter_device_tree(QWidget *parent = nullptr);
    void add(const QString& name);
private:
    QMap<QString, QTreeWidgetItem*> m_map;
};

class panel_list : public panel_base
{
    Q_OBJECT
public:
    explicit panel_list(const QString& name,  DCDockWindow* dock = nullptr,QObject *parent = nullptr);
    int count();
    QString at(int index);

private:
    int create(const QString& name) override;
    //int release() override;
private:
    QStringList m_names;
};

#endif // PANEL_LIST_H
