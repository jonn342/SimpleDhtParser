#ifndef IP_ADDRESS_STRUCTURE_HPP
#define IP_ADDRESS_STRUCTURE_HPP

#include <cstdint>

namespace task_1
{
	//Структура ip адреса
	struct IpAddressStructure
	{
		//Первая часть ip адреса
		uint8_t part_1;

		//Вторая часть ip адреса
		uint8_t part_2;

		//Третья часть ip адреса
		uint8_t part_3;

		//Четвертая часть ip адреса
		uint8_t part_4;
	};			
}


#endif