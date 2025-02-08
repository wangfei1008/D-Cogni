#ifndef CHANNEL_MAP_H_WANGFEI_20241223
#define CHANNEL_MAP_H_WANGFEI_20241223

#include "qcustomplot.h"
#include <mutex>
#include <shared_mutex>
#include <QColor>
#include <QRandomGenerator>

class channel_map
{
public:

    typedef struct ChannelPlot
    {
        QCPAxisRect*   rect;                                //通道相对应的矩形框
        int            axis_index[QCPAxis::atBottom + 1];   //矩形轴标号
        QCPGraph*      graph;                               //通道所对应的曲线
        QString        id;                                   //通道名称或者唯一id
        QColor         color;                                //通道使用的颜色

        ChannelPlot()
        {
            rect = NULL, graph = NULL;
            memset(axis_index, '\0', sizeof(int)*(QCPAxis::atBottom + 1));
            id = "";
            color = RandomColor();
        }


        QColor RandomColor()// 创建一个随机颜色
        {
            int r = QRandomGenerator::global()->bounded(256); // 0-255
            int g = QRandomGenerator::global()->bounded(256); // 0-255
            int b = QRandomGenerator::global()->bounded(256); // 0-255
            return QColor(r, g, b);
        }
    }ChannelPlot;

    channel_map();
protected:
    int count();
    int create(ChannelPlot channel);
    int remove(const QString& id, ChannelPlot& channel);
    int set_data(const QString& id, const QVector<double>& key, const QVector<double>& value, QCPAxisRect** rect);
    int add_data(const QString& id, const QVector<double>& key, const QVector<double>& value, QCPAxisRect** rect);
    bool contains(const QString&id);
    QStringList all_channel_name() const;
    ChannelPlot channel_plot(const QString& id);
    void data(const QString& id, QVector<double>& key, QVector<double>& value);

    ////////////////////////////////////////////////////////////////////////////////////////////
    /// 初始化
    //默认的极坐标参数
    int default_polar(const QString& id);
    //默认的笛卡尔坐标参数
    int default_cartesian(const QString& id);

    ////////////////////////////////////////////////////////////////////////////////////////////
    /// 设置属性
    //设置x\y\x2\y2轴是否可见
    int set_visible_axis(const QString& id, QCPAxis::AxisType type, bool visible);
    //设置重新缩放
    int set_auto_scale(const QString& id, bool scale = false);
    //设置图形随机颜色
    int set_grid_random_color(const QString& id);
    //设置轴随机颜色
    int set_axis_random_color(const QString& id, QCPAxis::AxisType type);
    //设置按照点形式显示
    int set_plot_dot(const QString& id);

protected:
    QMap<QString, ChannelPlot>                       m_map;	                         //动态增加删除通道所对应的曲线图
    mutable std::shared_mutex                        m_mutex;				         //锁的mutex
};

#endif // CHANNEL_MAP_H_WANGFEI_20241223
