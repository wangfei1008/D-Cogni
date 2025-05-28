#include "plot_widget.h"
#include "log/log.h"
#include "errorcode.h"

plot_widget::plot_widget(property_data* data, QWidget *parent)
    :QCustomPlot(parent)
    ,m_data(data)
{
    this->plotLayout()->clear();
    _init();
    // this->plotLayout()->insertRow(0);
    // QCPTextElement *title = new QCPTextElement(this, QStringLiteral("力-位移曲线"), QFont("sans", 17, QFont::Bold));
    // this->plotLayout()->addElement(0, 0, title);
}

int plot_widget::set_data(const QString &id, const QVector<double> &x, const QVector<double> &y)
{
    //1、检查通道id，如不存在对应的id则新建一个通道
    int res = _create_channel_plot(id);

    //2、设置数值
    res =  res == RES_SUCCESS ? channel_map::set_data(id, x, y, NULL) : res;

    //3、是否支持鼠标操作
    _set_mouse_option();

    //4、设置通道属性
    _set_channel_property(id);

    return res;
}

int plot_widget::add_data(const QString &id, const QVector<double> &x, const QVector<double> &y)
{
    //1、检查通道id，如不存在对应的id则新建一个通道
    int res = _create_channel_plot(id);

    //2、设置数值
    res =  res == RES_SUCCESS ? channel_map::add_data(id, x, y, NULL) : res;

    //3、是否支持鼠标操作
    _set_mouse_option();

    //4、设置通道属性
    _set_channel_property(id);

    return res;
}

int plot_widget::replot()
{
    QCustomPlot::replot();
    return RES_SUCCESS;
}

int plot_widget::updata_property()
{
    //设置图形、轴显示方式
    _set_grid_x_y_show();

    this->replot();

    return RES_SUCCESS;
}

void plot_widget::mousePressEvent(QMouseEvent *event)
{
    if (this->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
    {
        this->axisRect()->setRangeDrag(this->xAxis->orientation());
    }
    else
    {
        //单轴曲线拖拽方法
        this->axisRect()->setRangeDrag(Qt::Horizontal|Qt::Vertical);

        //多轴曲线拖拽方法
        QList<QCPAxis*> horz, vert;
        horz << this->axisRect()->axes(QCPAxis::atBottom);
        vert << this->axisRect()->axes(QCPAxis::atLeft);
        this->axisRect()->setRangeDragAxes(horz,vert);
    }
    QCustomPlot::mousePressEvent(event);
}

void plot_widget::wheelEvent(QWheelEvent *event)
{
    QList< QCPAxis * > axis_ys = this->axisRect()->axes(QCPAxis::atRight) ;
    foreach (QCPAxis * axis_y, axis_ys)
    {
        if(axis_y->selectedParts().testFlag(QCPAxis::spAxis))
        {
            this->axisRect()->setRangeZoom(axis_y->orientation());
            return;
        }
    }

    if (this->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
        this->axisRect()->setRangeZoom(this->xAxis->orientation());
    else
    {
        this->axisRect()->setRangeZoom(Qt::Vertical|Qt::Horizontal);
    }
    QCustomPlot::wheelEvent(event);
}

void plot_widget::_init()
{
    setBackgroundScaledMode(Qt::IgnoreAspectRatio);
    setBackground(QColor(0, 0, 0, 0));//设置默认背景为透明
}

int plot_widget::_create_channel_plot(const QString& id)
{
    channel_map::ChannelPlot ch;

    //1、检查是否需要新建
    if(contains(id)) return RES_SUCCESS;

    //2、分配资源
    ch.id = id;
    _create_channel(m_data.merge_type(), ch);
    channel_map::create(ch);

//    //3、初始化参数
//    CoordinatesType type = m_data.coordinates_type();
//    switch(type)
//    {
//    case CoordinatesType::POLAR:
//        default_polar(id);
//        break;
//    case CoordinatesType::CARTESIAN:
//        break;
//    case CoordinatesType::HOMOGENEOUS:
//        break;
//    }

    return RES_SUCCESS;
}

int plot_widget::_create_channel(MergeType type, channel_map::ChannelPlot& ch)
{
    if(type <= MergeType::MERGE_X_Y)
        return _create_channel_merge(type, ch);

    return _create_channel_split(type, ch);
}

int plot_widget::_create_channel_merge(MergeType type, channel_map::ChannelPlot& ch)
{
    QCPAxis *axis_x = NULL, *axis_y = NULL;
    int rows = this->plotLayout()->rowCount();
    this->setAutoAddPlottableToLegend(true);

    if(rows == 0)
    {
        ch.rect = new QCPAxisRect(this, true);
        if(ch.rect != NULL) this->plotLayout()->addElement(rows, 0, ch.rect);

        if(this->legend == NULL)
            this->legend = _set_channel_legend(ch.rect);
    }
    else
        ch.rect = (QCPAxisRect*)this->plotLayout()->element(0, 0);

    axis_x = ch.rect->axis(QCPAxis::atBottom);
    axis_y = ch.rect->axis(QCPAxis::atLeft);
    if(rows > 0)
    {
        if(type & 0x01) axis_x = ch.rect->addAxis(QCPAxis::atBottom);
        if(type & 0x02) axis_y = ch.rect->addAxis(QCPAxis::atLeft);
    }
    ch.graph = this->addGraph(axis_x, axis_y);
    ch.graph->setName(ch.id);

    ch.axis_index[QCPAxis::atBottom] = ch.rect->axisCount(QCPAxis::atBottom) - 1;
    ch.axis_index[QCPAxis::atLeft] = ch.rect->axisCount(QCPAxis::atLeft) - 1;

    return rows;
}

int plot_widget::_create_channel_split(MergeType type, channel_map::ChannelPlot& ch)
{
    int rows = this->plotLayout()->rowCount();
    int columns = this->plotLayout()->columnCount();
    this->setAutoAddPlottableToLegend(false);

    ch.rect = new QCPAxisRect(this);
    if(ch.rect != NULL)
    {
        if(type == MergeType::SPLIT_Y)
            this->plotLayout()->addElement(rows, 0, ch.rect);
        else
            this->plotLayout()->addElement(0, columns, ch.rect);
    }

    _set_common_axis(type);

    ch.graph = this->addGraph(ch.rect->axis(QCPAxis::atBottom), ch.rect->axis(QCPAxis::atLeft));
    ch.graph->setName(ch.id);

    //设置标签
    QCPLegend* _legend = _set_channel_legend(ch.rect);
    _legend->addItem(new QCPPlottableLegendItem(_legend, ch.graph));

    return RES_SUCCESS;
}

void plot_widget::_set_common_axis(MergeType type)
{
    if(!(type == MergeType::SPLIT_Y || type == MergeType::SPLIT_X)) return;

    QCPAxis::AxisType axis_type = type == MergeType::SPLIT_Y ? QCPAxis::atBottom : QCPAxis::atLeft;

    auto elements = this->plotLayout()->elementCount();
    for (int i = 0; i < elements; i++)
    {
        QCPAxisRect* rect = type == MergeType::SPLIT_Y ? (QCPAxisRect*)this->plotLayout()->element(i, 0) : (QCPAxisRect*)this->plotLayout()->element(0, i);

        if (rect)
        {
            bool res = false;
            //在合并x轴的情况，布局中最后一个元素进行设置；在合并y轴的情况下，布局中第一个元素进行设置
            if(type == MergeType::SPLIT_Y)
                res = i == (elements - 1) ? true : false;
            else
                res = i == 0 ? true : false;

            QCPAxis* axis = rect->axis(axis_type);
            axis->setVisible(res);
            axis->setTickLabels(res);
            axis->setSubTicks(res);

            for (int j = 0; j < elements; j++)
            {
                QCPAxisRect* _rect = type == MergeType::SPLIT_Y ? (QCPAxisRect*)this->plotLayout()->element(j, 0) : (QCPAxisRect*)this->plotLayout()->element(0, j);
                if (_rect && rect && i != j)
                    connect(rect->axis(axis_type), QOverload<const QCPRange&>::of(&QCPAxis::rangeChanged), _rect->axis(axis_type), QOverload<const QCPRange&>::of(&QCPAxis::setRange));
            }
        }
    }
}

void plot_widget::_set_channel_property(const QString &id)
{
    MergeType merge_type = m_data.merge_type();
    if(!(merge_type == MergeType::SPLIT_X || merge_type == MergeType::SPLIT_Y))
    {
        //轴是否显示
        set_visible_axis(id, QCPAxis::AxisType::atBottom, m_data.axis_visable(QCPAxis::AxisType::atBottom));
        set_visible_axis(id, QCPAxis::AxisType::atTop, m_data.axis_visable(QCPAxis::AxisType::atTop));
        set_visible_axis(id, QCPAxis::AxisType::atLeft, m_data.axis_visable(QCPAxis::AxisType::atLeft));
        set_visible_axis(id, QCPAxis::AxisType::atRight, m_data.axis_visable(QCPAxis::AxisType::atRight));
    }

    //设置随机颜色
    channel_map::set_grid_random_color(id);
    if((merge_type & 0x01) || (merge_type & 0x04)) channel_map::set_axis_random_color(id, QCPAxis::atBottom);
    if((merge_type & 0x02) || (merge_type & 0x08)) channel_map::set_axis_random_color(id, QCPAxis::atLeft);

    //设置轴标签
    int ch = channel_name_index(id);
    set_axis_label(id, QCPAxis::AxisType::atBottom, m_data.axis_label(ch,QCPAxis::AxisType::atBottom));
    set_axis_label(id, QCPAxis::AxisType::atTop, m_data.axis_label(ch,QCPAxis::AxisType::atTop));
    set_axis_label(id, QCPAxis::AxisType::atLeft, m_data.axis_label(ch,QCPAxis::AxisType::atLeft));
    set_axis_label(id, QCPAxis::AxisType::atRight, m_data.axis_label(ch,QCPAxis::AxisType::atRight));

    //是否支持自动缩放
    set_auto_scale(id, m_data.auto_scale());

    //设置数据点显示方式
    if(m_data.dot_plot_type() == DotPlotType::DOT)
        set_plot_dot(id);
}

QCPLegend* plot_widget::_set_channel_legend(QCPAxisRect* rect)
{
    QCPLegend* _legend = new QCPLegend;
    rect->insetLayout()->addElement(_legend, Qt::AlignTop | Qt::AlignRight);
    _legend->setVisible(true);
    _legend->setFont(QFont("Helvetica",9));
    _legend->setLayer("legend");
    _legend->setBrush(QBrush(QColor(255,255,255,100)));
    _legend->setBorderPen(Qt::NoPen);
    _legend->setBorderPen(QPen(Qt::DashDotLine));

    return _legend;
}

void plot_widget::_set_grid_x_y_show()
{
    QMap<QString, QVector<double>> key_map;
    QMap<QString, QVector<double>> value_map;
    //1、获取原来显示数据
    QStringList name_list = all_channel_name();
    for(QString name : name_list)
    {
        QVector<double> key, value;
        channel_map::data(name, key, value);
        key_map.insert(name, key);
        value_map.insert(name, value);

        //2、清理原来显示资源
        ChannelPlot ch;
        channel_map::remove(name, ch);
        this->removeGraph(ch.graph);
    }
    this->plotLayout()->clear();

    //3、重新创建显示资源
    for(QString name : name_list)
        set_data(name, key_map.find(name).value(), value_map.find(name).value());
}

void plot_widget::_set_mouse_option()
{
    if(m_data.mouse_operation())
    {
        QList<QCPAxis*> horz, vert;
        horz << this->axisRect()->axes(QCPAxis::atBottom);
        vert << this->axisRect()->axes(QCPAxis::atLeft);
        this->axisRect()->setRangeZoomAxes(horz, vert);
        this->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |  QCP::iSelectAxes | QCP::iSelectLegend | QCP::iSelectPlottables);
    }
    else
        this->setInteractions(QCP::iNone);
}
