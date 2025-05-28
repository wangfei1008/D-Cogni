#ifndef CHART_CONSTANTS_H_WANGFEI_20241220
#define CHART_CONSTANTS_H_WANGFEI_20241220

#include <QMap>
#include <QString>

///////////////////////////////////////////////////////////////////////////
///属性
//坐标类型，0：笛卡尔坐标；1：极坐标；2：齐次坐标
//extern QStringList  PROPERTY_COORDINATES_TYPE;

//绘制方式，0：点；1：line
extern QStringList  PROPERTY_DOT_PLOT_TYPE;

//图形显示方式
//            0:曲线合并,x轴合并，y轴合并；
//            1:曲线合并,x轴分离，y轴合并；
//            2:曲线合并,x轴合并，y轴分离；
//            3:曲线合并,x轴分离，y轴分离；
//            4:曲线分离,x轴分离，y轴合并；
//            5:曲线分离,x轴合并，y轴分离；
//            6:曲线分离,x轴分离，y轴分离；
extern QStringList PROPERTY_GRAPH_TYPE;

//轴是否显示
extern bool PROPERTY_AXIS_TOP_VISABLE;
extern bool PROPERTY_AXIS_LEFT_VISABLE;
extern bool PROPERTY_AXIS_BOTTOM_VISABLE;
extern bool PROPERTY_AXIS_RIGHT_VISABLE;


//是否支持自动缩放
extern bool PROPERTY_AUTO_RESCALE;

//是否支持鼠标操作
extern bool PROPERTY_INTERACTIONS_MOUSE;


//每个通道图形矩形框四边标签
extern QString  PROPERTY_CH_RECT_LABEL_LEFT;
extern QString  PROPERTY_CH_RECT_LABEL_BOTTOM;
extern QString  PROPERTY_CH_RECT_LABEL_RIGHT;
extern QString  PROPERTY_CH_RECT_LABEL_TOP;

#endif // CHART_CONSTANTS_H_WANGFEI_20241220
