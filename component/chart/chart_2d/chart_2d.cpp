#include "chart_2d.h"
#include "log/log.h"
#include "errorcode.h"
#include "plot_widget.h"
#include "property_widget.h"
#include "property_json.h"
#include "concrete_mediator.h"

using namespace std;

chart_2d::chart_2d()
    :m_info(ComponentType::Chart2DComponent, STR(TARGET), VER(SDK_VERSION), QString(QLatin1String(":/res/2D_32x32.png")))

{    
    m_plot = new plot_widget(&m_data);
    m_property = new property_widget(&m_data);

    m_mediator = new concrete_mediator((plot_widget*)m_plot, (property_widget*)m_property);
}

chart_2d::~chart_2d()
{
    delete m_mediator;
    m_mediator = NULL;
    delete m_plot;
    m_plot = NULL;
    delete m_property;
    m_property = NULL;
}

ComponentInfo chart_2d::info()
{
    return m_info;
}

int chart_2d::set_json_property(const QString &property)
{
    property_json json(m_data);
    json.set(property);
    m_data.set_datas(json.datas());
    return RES_SUCCESS;
}

QString chart_2d::json_property()
{
    property_json json(m_data);
    return json.get();
}

int chart_2d::set_data(const QString& id, const QVector<double>& x, const QVector<double>& y)
{
    return ((plot_widget*)m_plot)->set_data(id, x, y);
}

int chart_2d::add_data(const QString& id, const QVector<double>& x, const QVector<double>& y)
{
    return ((plot_widget*)m_plot)->add_data(id, x, y);;
}

int chart_2d::replot()
{
    return ((plot_widget*)m_plot)->replot();
}

QWidget* chart_2d::property()
{
    return m_property;
}

QWidget* chart_2d::plot()
{
    return m_plot;
}
