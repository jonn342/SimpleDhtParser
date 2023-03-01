#ifndef FULL_PACKET_HPP
#define FULL_PACKET_HPP

#include <IpPacketStructure.hpp>
#include <UdpPacketStructure.hpp>
#include <string>

namespace task_1
{
	/*
	 * @brief ��� ���������� �� ������
	 */
	struct FullPacket
	{
		//������ ip-������
		IpPacketStructure ip_part;

		//������ udp-������
		UdpPacketStructure udp_part;

		//��������� ����������
		std::string payload;
	};
}

#endif