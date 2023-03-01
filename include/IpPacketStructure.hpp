#ifndef IP_PACKET_STRUCTURE_HPP
#define IP_PACKET_STRUCTURE_HPP

#include <IpAddressStructure.hpp>

namespace task_1
{
    //Смещение от начала пакета. 14 - длина заголовка Ethernet пакета
    static constexpr uint8_t length_of_ethernet_header = 14;

    /*
     * @brief Структура Ip пакета
     */
	struct IpPacketStructure
	{
		uint8_t             ip_version_ihl;		// Версия ip (4 бита) + Длина заголовка ip пакета (4 бита)
		uint8_t             tos_enc;			// Тип сервиса (6 бит) + Уведомление о перегрузке сети (2 бита)
        uint16_t            tlen;               // Длина всего ip пакета (16 бит)
        uint16_t            identification;     // Идентификатор ip пакета, если пакет фрагментирован (16 бит)
        uint16_t            flags_fo;           // Флаги фрагментации пакета (3 бита) + позиция фрагмента текущего ip пакета (13 бит)
        uint8_t             ttl;                // Время жизни пакета (8 бит)
        uint8_t             proto;              // Протокол транспорта (1 - ICMP, 6 - TCP, 17 - UDP) (8 бит)
        uint16_t            crc;                // Контрольная сумма пакета (16 бит)
        IpAddressStructure  saddr;              // Ip адрес источника (32 бита)
        IpAddressStructure  daddr;              // ip адрес получателя (32 бита)
        uint32_t            op_pad;             // Прочие параметры, используется при длине заголова ip пакета > 5 (безопасность, запись маршрута, отметка времени и т. д.)(32 бита)
	};
}


#endif