#include "plot_business_data.h"
#include "chart_constants.h"

plot_business_data::plot_business_data(property_data* data)
    :m_data(data)
{

}

CoordinatesType plot_business_data::coordinates_type()
{
//    DataUnit u = _data_unit((unsigned long long)&PROPERTY_COORDINATES_TYPE);
//    if(u.uuid != 0)
//        return (CoordinatesType)u.value.toInt();

    return CoordinatesType::CARTESIAN;
}

MergeType plot_business_data::merge_type()
{
    //return MergeType::SPLIT_FULL;
    DataUnit u = _data_unit((unsigned long long)&PROPERTY_GRAPH_TYPE);
    if(u.uuid != 0)
    {
        if(u.value.toInt() < 5)
            return (MergeType)u.value.toInt();
        if(u.value.toInt() == 5)
            return MergeType::SPLIT_Y;
        if(u.value.toInt() == 6)
            return MergeType::SPLIT_FULL;
    }

    return MergeType::MERGE_FULL;
}

DotPlotType plot_business_data::dot_plot_type()
{
    DataUnit u = _data_unit((unsigned long long)&PROPERTY_DOT_PLOT_TYPE);
    if(u.uuid != 0)
        return (DotPlotType)u.value.toInt();

    return DotPlotType::LINE;
}

bool plot_business_data::axis_visable(int index)
{
    unsigned long long id = 0;
    if(index == 1) id =(unsigned long long)&PROPERTY_AXIS_LEFT_VISABLE;
    if(index == 2) id =(unsigned long long)&PROPERTY_AXIS_RIGHT_VISABLE;
    if(index == 4) id =(unsigned long long)&PROPERTY_AXIS_TOP_VISABLE;
    if(index == 8) id =(unsigned long long)&PROPERTY_AXIS_BOTTOM_VISABLE;

    DataUnit u = _data_unit(id);
    if(u.uuid != 0) return u.value.toBool();

    return false;
}

bool plot_business_data::auto_scale()
{
    DataUnit u = _data_unit((unsigned long long)&PROPERTY_AUTO_RESCALE);
    if(u.uuid != 0) return u.value.toBool();

    return false;
}

bool plot_business_data::mouse_operation()
{
    DataUnit u = _data_unit((unsigned long long)&PROPERTY_INTERACTIONS_MOUSE);
    if(u.uuid != 0) return u.value.toBool();

    return false;
}

DataUnit plot_business_data::_data_unit(unsigned long long uuid)
{
    QVector<DataUnit> datas = m_data->datas();
    for(DataUnit u : datas)
        if(uuid == u.uuid) return u;

    return DataUnit();
}
