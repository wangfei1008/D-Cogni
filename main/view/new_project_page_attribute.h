#ifndef PROJECTATTRIBUTE_H
#define PROJECTATTRIBUTE_H

#include <QWidget>

class ProjectAttribute : public QWidget
{
    Q_OBJECT
public:
    explicit ProjectAttribute(QWidget *parent = nullptr);
private Q_SLOTS:
    void on_slot_next_triggered(bool checked);
Q_SIGNALS:
    void signal_next_check();
};

#endif // PROJECTATTRIBUTE_H
