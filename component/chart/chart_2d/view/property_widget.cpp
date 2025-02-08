#include "property_widget.h"
#include "chart_constants.h"
#include "chart_macros.h"
#include <QCheckBox>

property_widget::property_widget(property_data* data, QWidget *parent)
    : QWidget{parent}
    , m_data(data)
{
    _init();
}

property_widget::~property_widget()
{
}

void property_widget::_init()
{
    //1、总体布局
    m_vertical_layout = new QVBoxLayout(this);
    m_form_layout = new QFormLayout();
    m_horizontal_layout = new QHBoxLayout();
    m_vertical_layout->addLayout(m_form_layout);
    m_vertical_layout->addLayout(m_horizontal_layout);
    m_vertical_layout->setStretch(0, 9);
    m_vertical_layout->setStretch(1, 1);

    //2、布局上方配置信息
    QVector<DataUnit> datas = m_data->datas();
    for(int i = 0; i < datas.count(); i++)
    {
        DataUnit unit = datas[i];
        m_form_layout->setWidget(i, QFormLayout::LabelRole, new QLabel(unit.desc, this));

        //QComboBox类型
        if(    //((unsigned long long)&PROPERTY_COORDINATES_TYPE == unit.uuid) ||
               ((unsigned long long)&PROPERTY_DOT_PLOT_TYPE == unit.uuid) ||
               ((unsigned long long)&PROPERTY_GRAPH_TYPE == unit.uuid)
          )
        {
            QComboBox *combo = new QComboBox(this);
            //if((unsigned long long)&PROPERTY_COORDINATES_TYPE == unit.uuid) combo->addItems(PROPERTY_COORDINATES_TYPE);
            if((unsigned long long)&PROPERTY_DOT_PLOT_TYPE == unit.uuid) combo->addItems(PROPERTY_DOT_PLOT_TYPE);
            if((unsigned long long)&PROPERTY_GRAPH_TYPE == unit.uuid) combo->addItems(PROPERTY_GRAPH_TYPE);
            combo->setCurrentIndex(unit.value.toInt());
            combo->setObjectName(unit.desc.replace(" ", "_"));
            m_form_layout->setWidget(i, QFormLayout::FieldRole, combo);
        }

        //QCheckBox类型
        if(    ((unsigned long long)&PROPERTY_AXIS_TOP_VISABLE == unit.uuid)
               || ((unsigned long long)&PROPERTY_AXIS_LEFT_VISABLE == unit.uuid)
               || ((unsigned long long)&PROPERTY_AXIS_BOTTOM_VISABLE == unit.uuid)
               || ((unsigned long long)&PROPERTY_AXIS_RIGHT_VISABLE == unit.uuid)
               || ((unsigned long long)&PROPERTY_AUTO_RESCALE == unit.uuid)
               || ((unsigned long long)&PROPERTY_INTERACTIONS_MOUSE == unit.uuid)
          )
        {
            QCheckBox *check = new QCheckBox(this);
            check->setChecked(unit.value.toBool());
            check->setObjectName(unit.desc.replace(" ", "_"));
            check->setText("show/hide");
            m_form_layout->setWidget(i, QFormLayout::FieldRole, check);
        }
    }

    //3、布局下发按键
    QPushButton* button = new QPushButton("Cancel", this);
    m_horizontal_layout->addWidget(button);
    button = new QPushButton("OK", this);
    connect(button, &QPushButton::clicked, this, &property_widget::on_button_ok_clicked);
    m_horizontal_layout->addWidget(button);
}

void property_widget::on_button_ok_clicked()
{
    QVector<DataUnit> datas = m_data->datas();

    //1、修改为当前参数
    QList<QComboBox *> cbs = findChildren<QComboBox *>();
    foreach (QComboBox *cb, cbs)
    {
        for(int i = 0; i < datas.count(); i++)
        {
            DataUnit u = datas[i];
            QString desc = u.desc;
            if(desc.replace(" ", "_") == cb->objectName())
            {
                u.value = cb->currentIndex();
                datas[i] = u;
                break;
            }
        }
    }

    QList<QCheckBox *> cks = findChildren<QCheckBox *>();
    foreach (QCheckBox *ck, cks)
    {
        for(int i = 0; i < datas.count(); i++)
        {
            DataUnit u = datas[i];
            QString desc = u.desc;
            if(desc.replace(" ", "_") == ck->objectName())
            {
                u.value = ck->isChecked();
                datas[i] = u;
                break;
            }
        }
    }

    //2、赋值数据基础
    m_data->set_datas(datas);

    //3、通知中介
    m_mediator->notify(this, EVENT_MEDIATOR_OK_CLICKED);
}
