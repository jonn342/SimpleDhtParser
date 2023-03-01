#include <PacketReader.hpp>
#include <pcap.h>
#include <UdpPacketStructure.hpp>
#include <FullPacket.hpp>
#include <iostream>

task_1::PacketReader* task_1::PacketReader::_ptr = nullptr;
task_1::PacketReaderDestroyer task_1::PacketReader::_destroyer;

namespace task_1
{
	PacketReader::PacketReader(pcap* device_descriptor)
	{
		try
		{
			if (device_descriptor == nullptr)
				throw "Device descriptor is not initialize.";
			_device_descriptor = device_descriptor;
		}
		catch (const char* msg)
		{
			std::cout << msg;
			exit(EXIT_FAILURE);
		}
	}

	bool PacketReader::get_next_packet(FullPacket& info)
	{
		const uint8_t* packet_data = nullptr;
		pcap_pkthdr* packet_header = nullptr;

		
		if (pcap_next_ex(_device_descriptor, &packet_header, &packet_data) > 0)
		{
			IpPacketStructure* ip_packet;
			UdpPacketStructure* udp_packet;

			ip_packet = (IpPacketStructure*)(packet_data + length_of_ethernet_header);

			unsigned offset_to_udp_packet = (ip_packet->ip_version_ihl & 0xf) * 4;
			udp_packet = (UdpPacketStructure*)((uint8_t*)(ip_packet + offset_to_udp_packet));

			char* data = (char*)packet_data + length_of_ethernet_header + 20 + 8;

			info.ip_part = *ip_packet;
			info.udp_part = *udp_packet;

			if (udp_packet->length < 8) return false;
			
			for (int i = 0; i < udp_packet->length - 8; ++i)
				info.payload += data[i];
			return true;
		}

		return false;
	}


	PacketReader& PacketReader::instance(pcap* device_descriptor)
	{
		if (_ptr == nullptr)
		{
			_ptr = new PacketReader(device_descriptor);
			_destroyer.initialize(_ptr);
		}
		return *_ptr;
	}

	PacketReaderDestroyer::~PacketReaderDestroyer()
	{
		delete _ptr;
	}

	void PacketReaderDestroyer::initialize(PacketReader* ptr)
	{
		_ptr = ptr;
	}

}
