#ifndef IP_ADDRESS_STRUCTURE_HPP
#define IP_ADDRESS_STRUCTURE_HPP

#include <cstdint>

namespace task_1
{
	//��������� ip ������
	struct IpAddressStructure
	{
		//������ ����� ip ������
		uint8_t part_1;

		//������ ����� ip ������
		uint8_t part_2;

		//������ ����� ip ������
		uint8_t part_3;

		//��������� ����� ip ������
		uint8_t part_4;
	};			
}


#endif