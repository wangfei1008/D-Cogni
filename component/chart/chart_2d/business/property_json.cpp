#include "property_json.h"
#include "data_base.h"
#include "errorcode.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

property_json::property_json(const property_data& data)
    :property_data{data}
{

}

int property_json::set(const QString &buf)
{
    QVector<DataUnit> v;
    QJsonDocument doc = QJsonDocument::fromJson(buf.toUtf8().data());
    if(doc.isNull() || !doc.isArray()) return RES_ERR_IPUT_PARM;

    QJsonArray array = doc.array();
    for(int i = 0; i < array.size(); i++)
    {
        QJsonObject obj = array[i].toObject();
        if(obj.isEmpty()) return RES_ERR_IPUT_PARM;

        DataUnit _;
        if(   !obj.contains(_last_variable_string(STR(_.uuid)))
           || !obj.contains(_last_variable_string(STR(_.desc)))
           || !obj.contains(_last_variable_string(STR(_.value))))
            return RES_ERR_IPUT_PARM;

        _.uuid = obj.value(_last_variable_string(STR(_.uuid))).toVariant().toLongLong();
        _.desc = obj.value(_last_variable_string(STR(_.desc))).toString();
        _.value = obj.value(_last_variable_string(STR(_.value))).toVariant();
        v.append(_);
    }

    return set_datas(v);
}


QString property_json::get()
{
    QJsonArray array;
    for(DataUnit u : m_vector)
    {
        QJsonObject obj;
        obj.insert(_last_variable_string(STR(u.uuid)), (qint64)u.uuid);
        obj.insert(_last_variable_string(STR(u.desc)), u.desc);
        switch(u.value.type())
        {
        case QVariant::Type::Bool:
            obj.insert(_last_variable_string(STR(u.value)), u.value.toBool());
            break;
        case QVariant::Type::Int:
        case QVariant::Type::UInt:
            obj.insert(_last_variable_string(STR(u.value)), u.value.toInt());
            break;
        case QVariant::Type::Double:
            obj.insert(_last_variable_string(STR(u.value)), u.value.toDouble());
            break;
        case QVariant::Type::LongLong:
        case QVariant::Type::ULongLong:
            obj.insert(_last_variable_string(STR(u.value)), u.value.toLongLong());
            break;
        case QVariant::Type::String:
            obj.insert(_last_variable_string(STR(u.value)), u.value.toString());
            break;
        default:
            break;
        }

        array.append(obj);
    }

    QJsonDocument doc(array);
    return doc.toJson();
}

QString property_json::_last_variable_string(const QString &str)
{
    int pos  = str.lastIndexOf(".");
    if(pos > 0)
        return str.mid(pos + 1, str.length() - pos - 1);
    return str;
}
