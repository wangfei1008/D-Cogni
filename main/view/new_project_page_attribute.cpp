#include <QtGui>
#include <QDesktopServices>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QToolButton>
#include <QLabel>
#include <QLineEdit>
#include "new_project_page_attribute.h"

ProjectAttribute::ProjectAttribute(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    //layout->setStretch(0, 1);
    //layout->setStretch(1, 19);
    QHBoxLayout *layout_h = new QHBoxLayout(this);
    layout_h->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum ));
    QToolButton* next = new QToolButton(this);
    next->setIcon(QIcon(":/res/image/next16x16.png"));
    next->setAutoRaise(true);
    connect(next, &QToolButton::clicked, this, &ProjectAttribute::on_slot_next_triggered);
    layout_h->addWidget(next);
    layout->addLayout(layout_h);


    layout_h = new QHBoxLayout(this);
    QLabel* lable = new QLabel("project name:", this);
    QLineEdit* text = new QLineEdit(this);
    layout_h->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum ));
    layout_h->addWidget(lable);
    layout_h->addWidget(text);
    layout_h->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum ));
    layout->addLayout(layout_h);

}

void ProjectAttribute::on_slot_next_triggered(bool checked)
{
    Q_EMIT signal_next_check();
}
