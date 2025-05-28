#ifndef DATA_DEVICE_H
#define DATA_DEVICE_H

#include <string>
#include <list>
#include <map>
#include "thread/MutexLock.h"
#include "data_base.h"


typedef enum deivce_data_type
{
    ATTRIBUTE_CONFIG = 0,
    ATTRIBUTE_BASE = 1,
    ATTRIBUTE_COMMAND = 2,
    RUNING_REAL = 3,
    RUNING_STATUS = 4,
    RUNING_COMMAND = 5,
    RELATION_DEVICES = 6,
    RELATION_BELONG = 7,
    RELATION_RESPONSIBLE = 8 
}deivce_data_type;

class data_base_attribute_device
{
public:
    data_base_attribute_device();
	virtual ~data_base_attribute_device();

    data_base_attribute_device(const data_base_attribute_device& data)
    {
		name = data.name;
		ip = data.ip;
		model = data.model;
		firmware_version = data.firmware_version;
		describe = data.describe;
		load_devices = data.load_devices;
    }

    data_base_attribute_device& operator=(const data_base_attribute_device& data)
	{
		name = data.name;
		ip = data.ip;
		model = data.model;
		firmware_version = data.firmware_version;
		describe = data.describe;
		load_devices = data.load_devices;
		return *this;
	}

	GETSET(std::string, name);
	GETSET(std::string, ip);
	GETSET(std::string, model);
	GETSET(std::string, firmware_version);
	GETSET(std::string, describe);
	GETSET(std::string, load_devices);
};

class subscriber_data_device_base
{
public:
    virtual ~subscriber_data_device_base(){};
    virtual void update(const data_base_attribute_device& attribute) = 0;
};

class publisher_data_device_base
{
public:
    virtual ~publisher_data_device_base(){};
    virtual void subscriber(deivce_data_type type, subscriber_data_device_base *subscriber) = 0;
    virtual void unsubscriber(deivce_data_type type, subscriber_data_device_base *subscriber) = 0;
    virtual void unsubscriber(subscriber_data_device_base* subscriber) = 0;
    virtual void notify(deivce_data_type type) = 0;
};


class publisher_data_device : public publisher_data_device_base
{
public:
    virtual ~publisher_data_device();

    void subscriber(deivce_data_type type, subscriber_data_device_base *subscriber) override;
    void unsubscriber(deivce_data_type type, subscriber_data_device_base *subscriber) override;
    void unsubscriber(subscriber_data_device_base* subscriber) override;
    
    void publisher(const data_base_attribute_device& attribute);

	void get(data_base_attribute_device& attribute);
private:
    void notify(deivce_data_type type) override;
private:
    std::map<deivce_data_type, std::list<subscriber_data_device_base *>>          m_map;
    MutexLock                                                                     m_mutex;
    data_base_attribute_device                                                    m_attribute_base;
};

class subscriber_data_device : public subscriber_data_device_base
{
public:
    subscriber_data_device(publisher_data_device_base & publisher);
    virtual ~subscriber_data_device();
private:
    publisher_data_device_base &m_publisher;
};
#endif // DATA_DEVICE_H
