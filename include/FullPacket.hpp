#ifndef FULL_PACKET_HPP
#define FULL_PACKET_HPP

#include <IpPacketStructure.hpp>
#include <UdpPacketStructure.hpp>
#include <string>

namespace task_1
{
	/*
	 * @brief Вся информация из пакета
	 */
	struct FullPacket
	{
		//Данные ip-пакета
		IpPacketStructure ip_part;

		//Данные udp-пакета
		UdpPacketStructure udp_part;

		//Остальная информация
		std::string payload;
	};
}

#endif