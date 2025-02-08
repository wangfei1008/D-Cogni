#ifndef ABSTRACT_COMPONENT_INTERFACE_H_20241216
#define ABSTRACT_COMPONENT_INTERFACE_H_20241216

#include <QString>
#include <QPixmap>
#include "data_base.h"
using namespace std;

typedef enum ComponentType {
    NoTypeComponent = 0,        // 0 未知类型
    GridComponent,              // 1 表格组件
    Chart2DComponent            // 2 2D图形组件
}ComponentType;

typedef struct ComponentInfo
{
    ComponentType type;           //组件类型
    QString name;                 //组件名称
    QString version;              //组件版本
    QPixmap icon;                 //组件图标

    ComponentInfo(const ComponentType& _t, const QString& _n, const QString& _v, const QPixmap& _i)
        :type(_t)
        ,name(_n)
        ,version(_v)
        ,icon(_i)
    {}
    ComponentInfo& operator=(const ComponentInfo& other)
    {
        type = other.type;
        name = other.name;
        version = other.version;
        icon = other.icon;
        return *this;
    }
}ComponentInfo;

class abstract_component
{
public:
    virtual ~abstract_component(){}
    ////////////////////////////////////////////////////////////////////////////////////////
    ///第一部分：属性接口
    //获取组件信息
    virtual ComponentInfo info() = 0;
    //设置属性配置缓存
    virtual int set_json_property(const QString& property) = 0;
    //获取属性配置
    virtual QString json_property() = 0;


    ////////////////////////////////////////////////////////////////////////////////////////
    ///第二部分：数据接口
    //赋值数据，对数据重新设置
    virtual int set_data(const QString& id, const QVector<double>& x, const QVector<double>& y) = 0;
    //追加数据
    virtual int add_data(const QString& id, const QVector<double>& x, const QVector<double>& y) = 0;

    ////////////////////////////////////////////////////////////////////////////////////////
    ///第三部分：输出接口
    //获取属性配置界面句柄
    virtual QWidget* property() = 0;
    //获取图形显示界面句柄
    virtual QWidget* plot() = 0;
public:
    //GETSET(string, name);                                           //组件名称
};

#endif // ABSTRACT_COMPONENT_INTERFACE_H_20241216
