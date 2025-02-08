#ifndef PROPERTY_JSON_H
#define PROPERTY_JSON_H

#include "property_data.h"

class property_json : public property_data
{
public:
    property_json(const property_data& data);

    //设置json形的配置
    int set(const QString& buf);
    //获取json形的配置
    QString get();
private:
    //或者字符串中"."后面的字符串，主要应用于结构体成员变量转换为字符串
    QString _last_variable_string(const QString& str);
};

#endif // PROPERTY_JSON_H
