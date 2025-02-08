#include "lib_handle.h"
#include "log/log.h"
#include <QString>

lib_handle::lib_handle(const string& libname):
    m_plib(NULL)
{
    m_plib = load(libname);
    if(m_plib != NULL)
    {
        m_create_func = (CreateComponent)m_plib->resolve("create_lib");
        m_release_func = (ReleaseComponent)m_plib->resolve("release_lib");
    }
}

abstract_component *lib_handle::create()
{
    abstract_component* p = NULL;
    if(m_plib != NULL)
    {
        p = init_component();
        m_list.push_back(p);
    }
    return p;
}

bool lib_handle::release(abstract_component* pcomponent)
{
    if(m_plib != NULL)
    {
        for(auto it = m_list.begin(); it != m_list.end(); it++)
        {
            if(*it == pcomponent)
            {
                release_component(pcomponent);
                m_list.erase(it);
                break;
            }
        }

        if(m_list.size() == 0)
        {
            m_plib->unload();
            delete m_plib;
            m_plib = NULL;
            return true;
        }
    }

    return false;
}

bool lib_handle::release()
{
    if(m_plib != NULL)
    {
        for(auto it = m_list.begin(); it != m_list.end(); it++)
            release_component(*it);
        m_list.clear();

        m_plib->unload();
        delete m_plib;
        m_plib = NULL;
    }

    return true;
}

lib_handle &lib_handle::operator=(const lib_handle &other)
{
    if (this != &other)
    {
        m_plib = other.m_plib;
        m_create_func = other.m_create_func;
        m_release_func = other.m_release_func;
        m_list = other.m_list;
    }
    return *this;
}

QLibrary* lib_handle::load(const string& libname)
{
#ifdef Q_OS_WIN
    string libraryname = libname + ".dll";
#elif defined(Q_OS_MACOS)
    string libraryname = libname + ".dylib";
#elif defined(Q_OS_LINUX)
    string libraryname = libname + ".so";
#else
    string libraryname = "";
#endif

    QLibrary* qLib = NULL;
    if (!libraryname.empty())
    {
        qLib = new QLibrary(QString::fromStdString(libraryname));
        if (!qLib->load())
        {
            LOGERROR("%s Dynamic link library loaded fail", libname.c_str());
        }
        else
            LOGINFO("%s dynamic link library loaded successfully", libname.c_str());
    }
    else
    {
        LOGERROR("unsupported platform");
    }
    return qLib;
}

abstract_component* lib_handle::init_component()
{
    abstract_component* p = NULL;
    if(m_create_func){
        LOGINFO("%s create_lib function parsing successful", m_plib->fileName().toStdString().c_str());
        m_create_func(&p);
    }
    else{
        LOGERROR("%s create_lib function parsing fail", m_plib->fileName().toStdString().c_str());
    }

    return p;
}

bool lib_handle::release_component(abstract_component* pcomponent)
{
    if(m_release_func){
        LOGINFO("%s release_lib function parsing successful", m_plib->fileName().toStdString().c_str());
      return m_release_func(&pcomponent);

    }
    else{
        LOGERROR("%s release_lib function parsing fail", m_plib->fileName().toStdString().c_str());
    }
    return false;
}
