#include <CaptureSource.hpp>
#include <NetworkDevice.hpp>
#include <PacketReader.hpp>
#include <iostream>
#include <queue>
#include <DhtInfo.hpp>
#include <FullPacket.hpp>
#include <thread>
#include <mutex>
#include <sstream>
#include <TrafficFilter.hpp>

int main(int argc, char**argv)
{
	std::string concat_arg;
	if (argc < 2)
	{
		std::cout << "Missing function parameter\n";
		return -1;
	}
	else
	{
		char** t_argv = argv + 1;
		while (*t_argv != nullptr)
		{
			concat_arg += (*t_argv++);
			if (*t_argv)
				concat_arg += " ";
		}
	}

	task_1::NetworkDevice dev = task_1::NetworkDevice::instance(std::move(concat_arg));
	task_1::CaptureSource cs  = task_1::CaptureSource::instance(dev);
	task_1::TrafficFilter filter(cs, "ip and udp", 1, dev.get_netmask());
	task_1::PacketReader packet_reader = task_1::PacketReader::instance(cs);
	
	std::queue<task_1::FullPacket> packets;
	bool is_read_packets_thr_work = false;
	bool is_analysis_and_write_thr_work = false;
	std::mutex mt;

	std::thread read_packets_thr([&]()
	{
			is_read_packets_thr_work = true;
			while (is_read_packets_thr_work)
			{
				task_1::FullPacket t_packet;
				bool is_reading = packet_reader.get_next_packet(t_packet);
				if (is_reading)
				{
					mt.lock();
					packets.push(t_packet);
					mt.unlock();
				}
			}
	});

	std::thread analisys_and_write_thr([&]() 
	{
			is_analysis_and_write_thr_work = true;
			while (is_analysis_and_write_thr_work)
			{
				if (packets.size() == 0)
					std::this_thread::yield();
				else
				{
					task_1::FullPacket current = packets.front();
					mt.lock();
					packets.pop();
					mt.unlock();
					
					task_1::DhtInfo dht_info;
					dht_info.source_ip = current.ip_part.saddr;
					while (current.payload.size())
					{
						size_t info_hash_pos = current.payload.find("info_hash20");
						if (info_hash_pos != std::string::npos)
						{
							dht_info.infohash = current.payload.substr(info_hash_pos + 12, 20);
							std::stringstream strstrm;
							for (const char& el : dht_info.infohash)
								strstrm << std::hex << (int)(uint8_t)el;
								
							dht_info.infohash = strstrm.str();

							if (current.payload.size() >= info_hash_pos + 32)
								current.payload = current.payload.substr(info_hash_pos + 32, current.payload.size() - (info_hash_pos + 32));
							else
								info_hash_pos = std::string::npos;
						}

						size_t announce_peer_pos = current.payload.find("announce_peer");
                        size_t get_peers_pos = current.payload.find("get_peers");
						if (announce_peer_pos != std::string::npos)
						{
							dht_info.query_type = current.payload.substr(announce_peer_pos, 13);
							if (current.payload.size() >= announce_peer_pos + 13)
								current.payload = current.payload.substr(announce_peer_pos + 13, current.payload.size() - (announce_peer_pos + 13));
							else
								announce_peer_pos = std::string::npos;
						}
                        else if (get_peers_pos != std::string::npos)
						{
							dht_info.query_type = current.payload.substr(get_peers_pos, 9);
							if (current.payload.size() >= get_peers_pos + 9)
								current.payload = current.payload.substr(get_peers_pos + 9, current.payload.size() - (get_peers_pos + 9));
							else 
								get_peers_pos = std::string::npos;
						}
						
						if (dht_info.query_type.size() && dht_info.infohash.size())
							std::cout << "<query type: " << dht_info.query_type
								<< "> <source ip: " << (int)dht_info.source_ip.part_1 << "."
								<< (int)dht_info.source_ip.part_2 << "."
								<< (int)dht_info.source_ip.part_3 << "."
								<< (int)dht_info.source_ip.part_4 
								<< "> <query info_hash: " << dht_info.infohash << ">\n";

						if (info_hash_pos == std::string::npos &&
							announce_peer_pos == std::string::npos &&
							get_peers_pos == std::string::npos)
							break;
					}
				}
			}
	});


	read_packets_thr.join();
	analisys_and_write_thr.join();
	return 0;
}

