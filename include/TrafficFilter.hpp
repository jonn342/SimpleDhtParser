#ifndef TRAFFIC_FILTER_HPP
#define TRAFFIC_FILTER_HPP

#include <string>
#include <pcap.h>


namespace task_1
{
	/*
	 * @�����, ��������������� ��������� ���������� �������� �������
	 */
	class TrafficFilter
	{
	public:
		/*
		 * @brief ����������� ��-���������
		 */
		TrafficFilter() = delete;

		/*
		 * @brief ����������� � �����������
		 * @param descriptor - ���������� ������������ ����������
		 * @param config - ������ ������������ �������
		 * @param optimize - �������� ���������� ����������� ��������������� ����
		 * @param netmask - ����� ����
		 */
		TrafficFilter(pcap* descriptor, const char* config, int optimize, long netmask);
		
	private:
		// ���������, ����������� �������� pcap_compile
		bpf_program _bpf;

		// ��������� ������ ������� pcap_compile
		int _result_compile;

		// ��������� ������ pcap_setfilter
		int _result_setfilter;

		// ��������� �� ������ - ��������� ��������� ������ ������� pcap_compile
		std::string _compile_err;

		// ��������� �� ������ - ��������� ��������� ������ ������� pcap_setfilter
		std::string _setfilter_err;

	};
}

#endif