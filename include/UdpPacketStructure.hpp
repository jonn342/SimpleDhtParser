#ifndef UDP_PACKET_STRUCTURE_HPP
#define UDP_PACKET_STRUCTURE_HPP

#include <cstdint>

namespace task_1
{
	/*
	 * @brief ��������� Udp ������
	 */
	struct UdpPacketStructure
	{
		uint16_t source_port;		// ���� ����������� (16 ���)
		uint16_t destination_port;	// ���� ���������� (16 ���)
		uint16_t length;			// ����� ����� UDP ������ (16 ���)
		uint16_t checksum;			// ����������� ����� ������ (16 ���)
	};
}


#endif