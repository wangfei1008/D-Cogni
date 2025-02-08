#ifndef CHART_2D_QCUSTOMPLOT_LIB_H_20241216
#define CHART_2D_QCUSTOMPLOT_LIB_H_20241216

#include "abstract_component.h"
#include <QVector>
#include "property_data.h"
#include "mediator.h"

class chart_2d: public abstract_component
{
public:
    chart_2d();
    ~chart_2d();

    ////////////////////////////////////////////////////////////////////////////////////////
    ///第一部分：属性接口
    //获取组件信息
    ComponentInfo info() override;
    //设置属性配置缓存
    int set_json_property(const QString& property) override;
    //获取属性配置
    QString json_property() override;

    ////////////////////////////////////////////////////////////////////////////////////////
    ///第二部分：数据接口
    //赋值数据，对数据重新设置
    int set_data(const QString& id, const QVector<double>& x, const QVector<double>& y) override;
    //追加数据
    int add_data(const QString& id, const QVector<double>& x, const QVector<double>& y) override;

    ////////////////////////////////////////////////////////////////////////////////////////
    ///第三部分：输出接口
    //获取属性配置界面句柄
    QWidget* property() override;
    //获取图形显示界面句柄
    QWidget* plot() override;
private:
    ComponentInfo                   m_info;                       //插件信息
    QWidget                         *m_property;                  //属性界面
    QWidget                         *m_plot;                      //图形界面
    property_data                   m_data;                       //数据
    mediator                        *m_mediator;                  //界面之前的中介
};

#endif // CHART_2D_QCUSTOMPLOT_LIB_H_20241216
