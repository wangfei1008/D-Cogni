#include "property_data.h"
#include "chart_constants.h"
#include "errorcode.h"

property_data::property_data()
{
    _init();
}

QVector<DataUnit> property_data::datas()
{
    return m_vector;
}

int property_data::set_datas(const QVector<DataUnit> &v)
{
    //1、检查输入参数真确性，防止出现修改部分正常参数情况。
    for(int i = 0; i < v.count(); i++)
    {
        DataUnit _ = v[i];
        bool res = false;
        for(int j = 0; j < m_vector.count(); j++)
        {
            DataUnit u = m_vector[j];
            if(_.uuid == u.uuid && _.desc == u.desc)
            {
                res = true;
                break;
            }
        }
        if(!res) return RES_ERR_IPUT_PARM;
    }

    //2、修改参数
    for(int i = 0; i < v.count(); i++)
    {
        DataUnit _ = v[i];
        for(int j = 0; j < m_vector.count(); j++)
        {
            DataUnit u = m_vector[j];
            if(_.uuid == u.uuid && _.desc == u.desc)
            {
                m_vector[j] = _;
                break;
            }
        }
    }

    return RES_SUCCESS;
}

void property_data::_init()
{
    int index = 0;
    m_vector.clear();

    index = 0;
    //m_vector.insert(index + 0, DataUnit((unsigned long long)&PROPERTY_COORDINATES_TYPE, "coordinates type", 1, NULL));
    m_vector.insert(index + 0, DataUnit((unsigned long long)&PROPERTY_DOT_PLOT_TYPE, "dot plot type", 1, NULL));
    m_vector.insert(index + 1, DataUnit((unsigned long long)&PROPERTY_GRAPH_TYPE, "graph type", 0, NULL));

    index = m_vector.count();
    m_vector.insert(index + 0, DataUnit((unsigned long long)&PROPERTY_AXIS_TOP_VISABLE, "axis top visable", PROPERTY_AXIS_TOP_VISABLE, NULL));
    m_vector.insert(index + 1, DataUnit((unsigned long long)&PROPERTY_AXIS_BOTTOM_VISABLE, "axis bottom visable", PROPERTY_AXIS_BOTTOM_VISABLE, NULL));
    m_vector.insert(index + 2, DataUnit((unsigned long long)&PROPERTY_AXIS_LEFT_VISABLE, "axis left visable", PROPERTY_AXIS_LEFT_VISABLE, NULL));
    m_vector.insert(index + 3, DataUnit((unsigned long long)&PROPERTY_AXIS_RIGHT_VISABLE, "axis right visable", PROPERTY_AXIS_RIGHT_VISABLE, NULL));

    index = m_vector.count();
    m_vector.insert(index + 0, DataUnit((unsigned long long)&PROPERTY_AUTO_RESCALE, "auto rescale", PROPERTY_AUTO_RESCALE, NULL));

    index = m_vector.count();
    m_vector.insert(index + 0, DataUnit((unsigned long long)&PROPERTY_INTERACTIONS_MOUSE, "mouse operation", PROPERTY_INTERACTIONS_MOUSE, NULL));
 }
