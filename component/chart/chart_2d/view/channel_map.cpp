#include "channel_map.h"
#include "errorcode.h"
#include "thread/Lock.h"


channel_map::channel_map()
{

}

int channel_map::count()
{
    return m_map.count();
}

int channel_map::create(ChannelPlot channel)
{
    if(m_map.contains(channel.id))
        return RES_ERR_IPUT_PARM;

    if(channel.graph == NULL || channel.rect == NULL) return RES_ERR_IPUT_PARM;

    m_map.insert(channel.id, channel);

    return RES_SUCCESS;
}

int channel_map::remove(const QString &id, ChannelPlot &channel)
{
    if(m_map.contains(id))
    {
        channel = m_map.find(id).value();
        m_map.remove(id);
        return RES_SUCCESS;
    }
    return RES_ERR_IPUT_PARM;
}

int channel_map::set_data(const QString &id, const QVector<double> &key, const QVector<double> &value, QCPAxisRect** rect)
{
    if(m_map.contains(id))
    {
        ChannelPlot ch = m_map.find(id).value();
        WriteLock lock(m_mutex);
        ch.graph->setData(key, value);
        if(rect != NULL)
            *rect = ch.rect;
        return RES_SUCCESS;
    }
    return RES_ERR_IPUT_PARM;
}

int channel_map::add_data(const QString &id, const QVector<double> &key, const QVector<double> &value, QCPAxisRect **rect)
{
    if(m_map.contains(id) && key.size() > 0)
    {
        ChannelPlot ch = m_map.find(id).value();
        WriteLock lock(m_mutex);
        ch.graph->addData(key, value);
        if(rect != NULL)
            *rect = ch.rect;
        return RES_SUCCESS;
    }
    return RES_ERR_IPUT_PARM;
}

bool channel_map::contains(const QString &id)
{
    return m_map.contains(id);
}

QStringList channel_map::all_channel_name() const
{
    return m_map.keys();
}

channel_map::ChannelPlot channel_map::channel_plot(const QString &id)
{
    if(m_map.contains(id))
        return m_map.find(id).value();
    return ChannelPlot();
}

void channel_map::data(const QString &id, QVector<double>& key, QVector<double>& value)
{
    if(m_map.contains(id))
    {
        ChannelPlot ch = m_map.find(id).value();
        WriteLock lock(m_mutex);
        QSharedPointer<QCPGraphDataContainer> p = ch.graph->data();
        for(auto it = p->begin(); it != p->end(); it++)
        {
            key.push_back(it->mainKey());
            value.push_back(it->mainValue());
        }
    }
}

int channel_map::default_polar(const QString &id)
{
    ChannelPlot ch = channel_plot(id);
    if(ch.graph == NULL || ch.rect == NULL) return RES_ERR_IPUT_PARM;

//    set_visible_axis(id, QCPAxis::AxisType::atBottom, false);
//    set_visible_axis(id, QCPAxis::AxisType::atTop, false);
//    set_visible_axis(id, QCPAxis::AxisType::atLeft, false);
//    set_visible_axis(id, QCPAxis::AxisType::atRight, false);

    return RES_SUCCESS;
}

int channel_map::default_cartesian(const QString &id)
{
    return RES_SUCCESS;
}

int channel_map::set_visible_axis(const QString &id, QCPAxis::AxisType type , bool visible)
{
    ChannelPlot ch = channel_plot(id);
    if(ch.graph == NULL || ch.rect == NULL) return RES_ERR_IPUT_PARM;

    ch.rect->axis(type, ch.axis_index[type])->setVisible(visible);

    return RES_SUCCESS;
}

int channel_map::set_auto_scale(const QString &id, bool scale)
{
    ChannelPlot ch = channel_plot(id);
    if(ch.graph == NULL || ch.rect == NULL) return RES_ERR_IPUT_PARM;

    ch.graph->rescaleAxes(scale);

    return RES_SUCCESS;
}

int channel_map::set_grid_random_color(const QString &id)
{
    ChannelPlot ch = channel_plot(id);
    if(ch.graph == NULL || ch.rect == NULL) return RES_ERR_IPUT_PARM;

    ch.graph->setPen(QPen(QBrush(ch.color),1));

    return RES_SUCCESS;
}

int channel_map::set_axis_random_color(const QString &id, QCPAxis::AxisType type)
{
    ChannelPlot ch = channel_plot(id);
    if(ch.graph == NULL || ch.rect == NULL) return RES_ERR_IPUT_PARM;
    // 设置Y轴的颜色
    ch.rect->axis(type, ch.axis_index[type])->setTickPen(QPen(QBrush(ch.color),2));
    ch.rect->axis(type, ch.axis_index[type])->setSubTickPen(QPen(QBrush(ch.color),2));
    ch.rect->axis(type, ch.axis_index[type])->setTickLabelColor(ch.color);
    ch.rect->axis(type, ch.axis_index[type])->setBasePen(QPen(QBrush(ch.color),2));
    return RES_SUCCESS;
}

int channel_map::set_plot_dot(const QString &id)
{
    ChannelPlot ch = channel_plot(id);
    if(ch.graph == NULL || ch.rect == NULL) return RES_ERR_IPUT_PARM;

    QPen pen;
    pen.setWidth(4);
    pen.setColor(ch.color);
    ch.graph->setPen(pen);
    ch.graph->setLineStyle((QCPGraph::LineStyle)0);//设置线性
    ch.graph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDot, 4));//设置每个节点数据绘制风格，默认是空，这里设置为空心圆

    return RES_SUCCESS;
}
