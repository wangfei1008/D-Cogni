#ifndef MENU_FILE_H
#define MENU_FILE_H

#include <QMenu>
#include <QObject>
#include <QAction>

class menu_file : public QObject
{
    Q_OBJECT
public:
    menu_file(QMenu* menu);
private:
    void add_actions();
private:
    QMenu               *m_menu;
    QAction             *m_new;
    QAction             *m_open;
    QAction             *m_save;
    QAction             *m_close;
};

#endif // MENU_FILE_H
