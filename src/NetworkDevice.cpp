#include <NetworkDevice.hpp>
#include <stdexcept>
#include <iostream>

#if defined(unix)
#include <netinet/in.h>
#endif

task_1::NetworkDevice* task_1::NetworkDevice::_ptr = nullptr;
task_1::NetworkDeviceDestroyer task_1::NetworkDevice::_destroyer;

namespace task_1
{
	NetworkDevice::NetworkDevice(std::string&& device_description)
		: _netmask(0)
	{
		pcap_if_t* t_all_devices_rpcap = nullptr;
		char errbuf[PCAP_ERRBUF_SIZE];
		try
		{
#if defined(WIN32)
			pcap_findalldevs_ex(PCAP_SRC_IF_STRING,
								nullptr,
								&t_all_devices_rpcap,
								errbuf
							    );
#elif defined(unix)
            pcap_findalldevs(&t_all_devices_rpcap, errbuf);
#endif
			if (t_all_devices_rpcap == nullptr)
				throw std::runtime_error("No network devices found.");

			pcap_if_t* current_device = t_all_devices_rpcap;
			while (current_device != nullptr)
			{

#if defined(unix)
                std::string temp_network_device = current_device->name;
                if (temp_network_device.find(device_description) != std::string::npos)
                {
                    sockaddr_in* temp = (sockaddr_in*)current_device->addresses->netmask;
                    if (temp)
                        _netmask = temp->sin_addr.s_addr;
#elif defined(WIN32)
                std::string temp_network_device = current_device->description;
                if (temp_network_device.find(device_description) != std::string::npos)
                {
                    sockaddr_in* temp = (sockaddr_in*)current_device->addresses->netmask;
                    if (temp)
                        _netmask = temp->sin_addr.S_un.S_addr;
#endif
					_device_description = std::move(device_description);
					_device_name = current_device->name;
					break;
				}
				current_device = current_device->next;
			}

			if (!_device_description.size() || !_device_name.size())
				throw std::runtime_error("Network device not found.");

			pcap_freealldevs(t_all_devices_rpcap);
		}
		catch (std::exception& ex)
		{
			pcap_freealldevs(t_all_devices_rpcap);
			std::cout << ex.what() << " | "<< errbuf <<  '\n';
			exit(EXIT_FAILURE);
		}
	}

	NetworkDevice::operator const char* ()const
	{
		return _device_name.c_str();
	}

	const std::string& NetworkDevice::get_device_name()const
	{
		return _device_name;
	}

	const std::string& NetworkDevice::get_device_description()const
	{
		return _device_description;
	}

	long NetworkDevice::get_netmask()const
	{
		return _netmask;
	}

	NetworkDevice& NetworkDevice::instance(std::string&& device_description)
	{
		if (_ptr == nullptr)
		{
			_ptr = new NetworkDevice(std::move(device_description));
			_destroyer.initialize(_ptr);
		}
		return *_ptr;
	}

	NetworkDeviceDestroyer::~NetworkDeviceDestroyer()
	{
		delete _ptr;
	}

	void NetworkDeviceDestroyer::initialize(NetworkDevice* ptr)
	{
		_ptr = ptr;
	}

}
