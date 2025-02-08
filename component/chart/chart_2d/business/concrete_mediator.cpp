#include "concrete_mediator.h"
#include "chart_macros.h"
concrete_mediator::concrete_mediator(plot_widget *plot, property_widget *property)
    :m_plot(plot)
    ,m_property(property)
{
    m_plot->set_mediator(this);
    m_property->set_mediator(this);
}

void concrete_mediator::notify(base_component *sender, int event) const
{
    switch(event)
    {
    case EVENT_MEDIATOR_OK_CLICKED:
        m_plot->updata_property();
        break;
    }
}
