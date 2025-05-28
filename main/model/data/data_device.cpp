#include "data_device.h"

inline publisher_data_device::~publisher_data_device()
{
}

inline void publisher_data_device::subscriber(deivce_data_type type, subscriber_data_device_base* subscriber)
{
	MutexLockGuard lock(m_mutex);
	auto it = m_map.find(type);
	if (it != m_map.end())
	{
		it->second.push_back(subscriber);
	}
	else
	{
		std::list<subscriber_data_device_base*> list;
		list.push_back(subscriber);
		m_map[type] = list;
	}
}

inline void publisher_data_device::unsubscriber(deivce_data_type type, subscriber_data_device_base* subscriber)
{
	MutexLockGuard lock(m_mutex);
	auto it = m_map.find(type);
	if (it != m_map.end())
	{
		it->second.remove(subscriber);
	}
}

void publisher_data_device::unsubscriber(subscriber_data_device_base* subscriber)
{
	MutexLockGuard lock(m_mutex);
	for (auto& it : m_map)
		it.second.remove(subscriber);
}

inline void publisher_data_device::publisher(const data_base_attribute_device& attribute)
{
	m_attribute_base = attribute;
	notify(deivce_data_type::ATTRIBUTE_BASE);
}

inline void publisher_data_device::get(data_base_attribute_device& data) 
{
	data = m_attribute_base;
}

inline void publisher_data_device::notify(deivce_data_type type)
{
	MutexLockGuard lock(m_mutex);
	auto it = m_map.find(type);
	if(it != m_map.end())
	{
		for (auto& subscriber : it->second)
		{
			switch (type)
			{
			case ATTRIBUTE_CONFIG:
				break;
			case ATTRIBUTE_BASE:
				subscriber->update(m_attribute_base);
				break;
			case ATTRIBUTE_COMMAND:
				break;
			case RUNING_REAL:
				break;
			case RUNING_STATUS:
				break;
			case RUNING_COMMAND:
				break;
			case RELATION_DEVICES:
				break;
			case RELATION_BELONG:
				break;
			case RELATION_RESPONSIBLE:
				break;
			default:
				break;
			}
		}
	}	
}

inline subscriber_data_device::subscriber_data_device(publisher_data_device_base& publisher) 
	: m_publisher(publisher)
{
}

inline subscriber_data_device::~subscriber_data_device()
{
	this->m_publisher.unsubscriber(this);
}
