#include "menu_file.h"

menu_file::menu_file(QMenu* menu)\
    :m_menu(menu)
{
    add_actions();
}

void menu_file::add_actions()
{
    m_new = new QAction(tr("New"), this);
    connect(m_new, SIGNAL(triggered()), this, SLOT(slot_new()));
    m_menu->addAction(m_new);

    m_open = new QAction(tr("Open"), this);
    connect(m_open, SIGNAL(triggered()), this, SLOT(slot_open()));
    m_menu->addAction(m_open);

    m_save = new QAction(tr("Save"), this);
    connect(m_save, SIGNAL(triggered()), this, SLOT(slot_save()));
    m_menu->addAction(m_save);

    m_close = new QAction(tr("Close"), this);
    connect(m_close, SIGNAL(triggered()), this, SLOT(slot_close()));
    m_menu->addAction(m_close);
}
