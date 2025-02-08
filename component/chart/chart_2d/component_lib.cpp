#include "component_lib.h"
#include "log/log.h"
#include "chart_2d.h"

typedef chart_2d A_C;

bool create_lib(abstract_component** component)
{
    abstract_component* p = new A_C();
    if(p != NULL)
    {
        LOGINFO("create component name = %s", p->info().name.toStdString().c_str());
        *component = (abstract_component*)p;
        return true;
    }
    return false;
}

bool release_lib(abstract_component** component)
{
    if(component == NULL || (*component) == NULL) return false;

    A_C* p = (A_C*)*component;
    delete p;
    p = NULL;

    LOGINFO("release component name = %s", (*component)->info().name.toStdString().c_str());

    return true;
}
