#ifndef PLOT_BUSINESS_DATA_H_WANGFEI_20241223
#define PLOT_BUSINESS_DATA_H_WANGFEI_20241223

#include "property_data.h"
#include "chart_typedef.h"

class plot_business_data
{
public:
    plot_business_data(property_data* data);

    //获取坐标类型
    CoordinatesType coordinates_type();

    //获取图形坐标显示方式
    MergeType merge_type();

    //获取数据点显示方式
    DotPlotType dot_plot_type();

    //获取坐标轴显示方式
    bool axis_visable(int index);

    //获取是否支持自动缩放
    bool auto_scale();

    //获取是否支持鼠标操作
    bool mouse_operation();
private:
    //获取单个元素
    DataUnit _data_unit(unsigned long long uuid);
private:
    property_data                         *m_data;
};

#endif // PLOT_BUSINESS_DATA_H_WANGFEI_20241223
