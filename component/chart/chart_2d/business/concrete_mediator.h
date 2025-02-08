#ifndef CONCRETE_MEDIATOR_H
#define CONCRETE_MEDIATOR_H

#include "mediator.h"
#include "plot_widget.h"
#include "property_widget.h"

class concrete_mediator : public mediator
{
public:
    concrete_mediator(plot_widget* plot, property_widget* property);
    void notify(base_component *sender, int event) const override;
private:
    plot_widget             *m_plot;
    property_widget         *m_property;
};


#endif // CONCRETE_MEDIATOR_H
