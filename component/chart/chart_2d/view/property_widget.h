#ifndef PROPERTY_WIDGET_H_20241220
#define PROPERTY_WIDGET_H_20241220

#include <QtWidgets/QWidget>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include "property_data.h"
#include "mediator.h"

class property_widget
        : public QWidget
        , public base_component
{
    Q_OBJECT
public:
    explicit property_widget(property_data* data, QWidget *parent = nullptr);
    ~property_widget() override;

private:
    void _init();
public slots:
    //保存配置响应槽
    void on_button_ok_clicked();
signals:

private:
    QVBoxLayout                                             *m_vertical_layout;
    QFormLayout                                             *m_form_layout;
    QHBoxLayout                                             *m_horizontal_layout;
    property_data                                           *m_data;                                          //配置界面参数数据
};

#endif // PROPERTY_WIDGET_H_20241220
