#include <CaptureSource.hpp>
#include <NetworkDevice.hpp>
#include <stdexcept>
#include <iostream>

task_1::CaptureSource* task_1::CaptureSource::_ptr = nullptr;
task_1::CaptureSourceDestroyer task_1::CaptureSource::_destroyer;


namespace task_1
{
	CaptureSource::CaptureSource	(const char* device,
                                    int packet_bytes_needed_for_capture,
                                    int promiscuous_mode,
                                    int read_timeout,
                                    pcap_rmtauth* auth_ptr)
		: _addescriptor(nullptr)
	{
		char errbuf[PCAP_ERRBUF_SIZE];
		try
		{
#if defined(WIN32)
			_addescriptor = pcap_open(device,
				packet_bytes_needed_for_capture,
				promiscuous_mode,
				read_timeout,
				auth_ptr,
				errbuf);
#elif defined(unix)
            _addescriptor = pcap_open_live(device,
                                           packet_bytes_needed_for_capture,
                                           promiscuous_mode,
                                           read_timeout,
                                           errbuf);
#endif
			if (!_addescriptor)
				throw std::runtime_error("Cant open capture source.");
		}
		catch (const std::exception& ex)
		{
            std::cout << ex.what() << " | " << errbuf << '\n';
			exit(EXIT_FAILURE);
		}
	}

	CaptureSource::operator pcap* ()const
	{
		return _addescriptor;
	}

	CaptureSource::~CaptureSource()
	{
		if (_addescriptor)
		{
			pcap_close(_addescriptor);
			_addescriptor = nullptr;
		}
	}

	const pcap* CaptureSource::get_descriptor()const
	{
		return _addescriptor;
	}

	CaptureSource& CaptureSource::instance(const char* device,
											int packet_bytes_needed_for_capture,
											int promiscuous_mode,
											int read_timeout,
											pcap_rmtauth* auth_ptr)
	{
		if (_ptr == nullptr)
		{
			_ptr = new CaptureSource(device, packet_bytes_needed_for_capture, promiscuous_mode, read_timeout, auth_ptr);
			_destroyer.initialize(_ptr);
		}
		return *_ptr;
	}

	CaptureSourceDestroyer::~CaptureSourceDestroyer()
	{
		delete _ptr;
	}

	void CaptureSourceDestroyer::initialize(CaptureSource* ptr)
	{
		_ptr = ptr;
	}

}
