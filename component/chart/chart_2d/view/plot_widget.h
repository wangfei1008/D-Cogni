#ifndef PLOT_WIDGET_H_WANGFEI_20241223
#define PLOT_WIDGET_H_WANGFEI_20241223

#include "channel_map.h"
#include "plot_business_data.h"
#include "mediator.h"


class plot_widget
        : public channel_map
        , public QCustomPlot
        , public base_component
{
public:
    plot_widget(property_data* data, QWidget *parent = nullptr);
    int set_data(const QString& id, const QVector<double>& x, const QVector<double>& y);
    int add_data(const QString& id, const QVector<double>& x, const QVector<double>& y);
    int replot();

    //更新所有界面配置
    int updata_property();

    void mousePressEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    //初始化
    void _init();

    //创建一个新通道矩形框绘图区域
    int _create_channel_plot(const QString& id);

    //创建曲线、x轴、y轴资源
    int _create_channel(MergeType type, channel_map::ChannelPlot& ch);
    //创建曲线合并显示方式
    int _create_channel_merge(MergeType type, channel_map::ChannelPlot& ch);
    //创建曲线分离显示方式
    int _create_channel_split(MergeType type, channel_map::ChannelPlot& ch);

    //在图形分离情况，设置公有轴
    void _set_common_axis(MergeType type);

    //设置通道属性
    void _set_channel_property(const QString& id);

    //设置通道标签
    QCPLegend* _set_channel_legend(QCPAxisRect* rect);

    //设置图形、x\y轴显示方式
    void _set_grid_x_y_show();

    //设置支持鼠标操作
    void _set_mouse_option();
private:
    plot_business_data                                           m_data;                                          //配置界面参数数据
};

#endif // PLOT_WIDGET_H_WANGFEI_20241223
