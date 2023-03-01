#ifndef TRAFFIC_FILTER_HPP
#define TRAFFIC_FILTER_HPP

#include <string>
#include <pcap.h>


namespace task_1
{
	/*
	 * @Класс, предоставляющий настройки фильтрации сетевого трафика
	 */
	class TrafficFilter
	{
	public:
		/*
		 * @brief Конструктор по-умолчанию
		 */
		TrafficFilter() = delete;

		/*
		 * @brief Конструктор с параметрами
		 * @param descriptor - дескриптор захваченного устройства
		 * @param config - строка конфигурации фильтра
		 * @param optimize - контроль выполнения оптимизации результирующего кода
		 * @param netmask - маска сети
		 */
		TrafficFilter(pcap* descriptor, const char* config, int optimize, long netmask);
		
	private:
		// Структура, заполняемая функцией pcap_compile
		bpf_program _bpf;

		// Результат работы функции pcap_compile
		int _result_compile;

		// Результат работы pcap_setfilter
		int _result_setfilter;

		// Сообщение об ошибке - результат неудачной работы функции pcap_compile
		std::string _compile_err;

		// Сообщение об ошибке - результат неудачной работы функции pcap_setfilter
		std::string _setfilter_err;

	};
}

#endif