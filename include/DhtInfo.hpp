#ifndef DHT_INFO_HPP
#define DHT_INFO_HPP

#include <IpAddressStructure.hpp>
#include <string>

namespace task_1
{
	/*
	 *@brief ��������� ������������� ���-�������
	 */
	struct DhtInfo
	{
		using IpAddress = IpAddressStructure;

		// Ip ����� �����������
		IpAddress	source_ip;		

		// ��� �������
		std::string query_type;		

		// Infohash �������
		std::string infohash;		
	};
}

#endif