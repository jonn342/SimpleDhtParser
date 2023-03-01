#ifndef IP_PACKET_STRUCTURE_HPP
#define IP_PACKET_STRUCTURE_HPP

#include <IpAddressStructure.hpp>

namespace task_1
{
    //�������� �� ������ ������. 14 - ����� ��������� Ethernet ������
    static constexpr uint8_t length_of_ethernet_header = 14;

    /*
     * @brief ��������� Ip ������
     */
	struct IpPacketStructure
	{
		uint8_t             ip_version_ihl;		// ������ ip (4 ����) + ����� ��������� ip ������ (4 ����)
		uint8_t             tos_enc;			// ��� ������� (6 ���) + ����������� � ���������� ���� (2 ����)
        uint16_t            tlen;               // ����� ����� ip ������ (16 ���)
        uint16_t            identification;     // ������������� ip ������, ���� ����� �������������� (16 ���)
        uint16_t            flags_fo;           // ����� ������������ ������ (3 ����) + ������� ��������� �������� ip ������ (13 ���)
        uint8_t             ttl;                // ����� ����� ������ (8 ���)
        uint8_t             proto;              // �������� ���������� (1 - ICMP, 6 - TCP, 17 - UDP) (8 ���)
        uint16_t            crc;                // ����������� ����� ������ (16 ���)
        IpAddressStructure  saddr;              // Ip ����� ��������� (32 ����)
        IpAddressStructure  daddr;              // ip ����� ���������� (32 ����)
        uint32_t            op_pad;             // ������ ���������, ������������ ��� ����� �������� ip ������ > 5 (������������, ������ ��������, ������� ������� � �. �.)(32 ����)
	};
}


#endif