#include <TrafficFilter.hpp>
#include <stdexcept>
#include <iostream>

namespace task_1
{
	TrafficFilter::TrafficFilter(pcap* descriptor, const char* config, int optimize, long netmask)
		: _result_compile(0)
		, _result_setfilter(0)
	{
		_result_compile = pcap_compile(descriptor, &_bpf, config, optimize, netmask);
		if (_result_compile == 0)
		{
			_result_setfilter = pcap_setfilter(descriptor, &_bpf);
			if (_result_setfilter == -1)
				_setfilter_err = pcap_geterr(descriptor);
		}
		else
			_compile_err = pcap_geterr(descriptor);
	}
}