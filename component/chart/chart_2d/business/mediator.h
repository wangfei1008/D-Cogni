#ifndef MEDIATOR_H_WANGFEI_20241225
#define MEDIATOR_H_WANGFEI_20241225


class base_component;

class mediator
{
public:
    virtual void notify(base_component* sender, int event) const = 0;
};

class base_component
{
public:
    base_component(mediator* itor = nullptr)
        :m_mediator(itor)
    {}
    void set_mediator(mediator* itor)
    {
        this->m_mediator = itor;
    }

protected:
    mediator      *m_mediator;
};

#endif // MEDIATOR_H_WANGFEI_20241225
