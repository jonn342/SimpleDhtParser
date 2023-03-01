#ifndef DHT_INFO_HPP
#define DHT_INFO_HPP

#include <IpAddressStructure.hpp>
#include <string>

namespace task_1
{
	/*
	 *@brief Структура распределённой хэш-таблицы
	 */
	struct DhtInfo
	{
		using IpAddress = IpAddressStructure;

		// Ip адрес отправителя
		IpAddress	source_ip;		

		// Тип запроса
		std::string query_type;		

		// Infohash запроса
		std::string infohash;		
	};
}

#endif