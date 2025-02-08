#ifndef LIB_HANDLE_H
#define LIB_HANDLE_H

#include "abstract_component.h"
#include <string>
#include <QLibrary>


class lib_handle
{
    typedef bool (*CreateComponent)(abstract_component**);
    typedef bool (*ReleaseComponent)(abstract_component**);
public:
    lib_handle(const string& libname);

    //创建新组件
    abstract_component* create();
    //释放组件，当无组件时自动卸载动态库
    bool release(abstract_component* pcomponent);
    //释放所有组件，且卸载动态库
    bool release();

    lib_handle &operator=(const lib_handle& other);
private:
    QLibrary* load(const string& libname);
    abstract_component* init_component();
    bool release_component(abstract_component* pcomponent);

private:
    QLibrary* m_plib;                                                             //动态库句柄
    CreateComponent m_create_func;                                               //创建组件函数
    ReleaseComponent m_release_func;                                             //释放组件函数
    list<abstract_component*> m_list;                                            //组件指针队列
};

#endif // LIB_HANDLE_H
