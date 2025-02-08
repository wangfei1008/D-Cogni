#ifndef CHART_TYPEDEF_H_WANGFEI_20241220
#define CHART_TYPEDEF_H_WANGFEI_20241220

#include <QString>
#include <QVariant>

//基础数据单元配置
typedef struct DataUnit
{
    unsigned long long uuid;                                    //唯一标识
    QString desc;                                               //名称描述，供显示使用
    QVariant value;                                             //当前值，包括具体类型
    QString unit;                                               //值的单位

    DataUnit(){uuid = 0; desc = "null"; value = 0; unit = "null";}
    DataUnit(unsigned long long _u, const QString& _d, const QVariant& _v, const QString& _t)
        :uuid(_u)
        ,desc(_d)
        ,value(_v)
        ,unit(_t)
    {}
    DataUnit& operator=(const DataUnit& other)
    {
        uuid = other.uuid;
        desc = other.desc;
        value = other.value;
        unit = other.unit;
        return *this;
    }
}DataUnit;

//坐标类型
typedef enum CoordinatesType
{
    CARTESIAN = 0,
    POLAR,
    HOMOGENEOUS
}CoordinatesType;

//数据点显示标识
typedef enum DotPlotType
{
    DOT = 0,
    LINE
}DotPlotType;

//图形合并状态
typedef enum MergeType
{
    MERGE_FULL = 0,                                              //曲线合并,x轴合并，y轴合并；
    MERGE_X,                                                     //曲线合并,x轴分离，y轴合并
    MERGE_Y,                                                     //曲线合并,x轴分离，y轴合并
    MERGE_X_Y,                                                   //曲线合并,x轴分离，y轴分离
    SPLIT_X,                                                     //曲线分离,x轴分离，y轴合并
    SPLIT_Y = 0x08,                                              //曲线分离,x轴合并，y轴分离
    SPLIT_FULL = 0x0C                                            //曲线分离,x轴分离，y轴分离
}MergeType;


#endif // CHART_TYPEDEF_H_WANGFEI_20241220
