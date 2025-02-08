#ifndef PROPERTY_DATA_H
#define PROPERTY_DATA_H

#include "chart_typedef.h"

class property_data
{
public:
    property_data();
    //获取属性数据
    QVector<DataUnit> datas();
    //设置属性数据
    int set_datas(const QVector<DataUnit>& v);
private:
    //初始化属性数据
    void _init();
protected:
    QVector<DataUnit> m_vector;
};

#endif // PROPERTY_DATA_H
