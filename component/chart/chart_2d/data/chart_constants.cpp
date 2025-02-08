#include "chart_constants.h"

///////////////////////////////////////////////////////////////////////////
///属性
//坐标类型，0：笛卡尔坐标；1：极坐标；2：齐次坐标
//QStringList  PROPERTY_COORDINATES_TYPE{
//    "Cartesian",
//    "Polar",
//    "Homogeneous"
//};

//绘制方式，0：点；1：line
QStringList  PROPERTY_DOT_PLOT_TYPE{
    "Dot",
    "Line"
};

//图形显示方式
//            0:曲线合并,x轴合并，y轴合并；
//            1:曲线合并,x轴合并，y轴分离；
//            2:曲线合并,x轴分离，y轴合并；
//            3:曲线合并,x轴分离，y轴分离；
//            4:曲线分离,x轴合并，y轴分离；
//            5:曲线分离,x轴分离，y轴合并；
//            6:曲线分离,x轴分离，y轴分离；
QStringList PROPERTY_GRAPH_TYPE{
    "full merge",
    "x-axis split",
    "y-axis split",
    "x/y-axis split",
    "grid/x-axis split",
    "grid/y-axis split",
    "full split"
};

//轴是否显示
bool PROPERTY_AXIS_TOP_VISABLE = true;
bool PROPERTY_AXIS_LEFT_VISABLE = true;
bool PROPERTY_AXIS_BOTTOM_VISABLE = true;
bool PROPERTY_AXIS_RIGHT_VISABLE = true;

//是否支持自动缩放
bool PROPERTY_AUTO_RESCALE = true;

//是否支持鼠标操作
bool PROPERTY_INTERACTIONS_MOUSE = true;

