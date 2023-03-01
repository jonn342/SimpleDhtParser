#ifndef UDP_PACKET_STRUCTURE_HPP
#define UDP_PACKET_STRUCTURE_HPP

#include <cstdint>

namespace task_1
{
	/*
	 * @brief Структура Udp пакета
	 */
	struct UdpPacketStructure
	{
		uint16_t source_port;		// Порт отправителя (16 бит)
		uint16_t destination_port;	// Порт получателя (16 бит)
		uint16_t length;			// Длина всего UDP пакета (16 бит)
		uint16_t checksum;			// Контрольная сумма пакета (16 бит)
	};
}


#endif