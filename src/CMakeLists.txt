set(HEADERS
	../include/CaptureSource.hpp
	../include/NetworkDevice.hpp
	../include/PacketReader.hpp
	../include/IpPacketStructure.hpp
	../include/IpAddressStructure.hpp
	../include/UdpPacketStructure.hpp
	../include/DhtInfo.hpp
	../include/FullPacket.hpp
	../include/TrafficFilter.hpp
)
add_executable(${PROJECT_NAME}
	main.cpp
	CaptureSource.cpp
	NetworkDevice.cpp
	PacketReader.cpp
	TrafficFilter.cpp
	${HEADERS}
	)
	
if(WIN32)
	target_include_directories(${PROJECT_NAME} PUBLIC
		../include
                ../libs/include
	)
	target_link_directories(${PROJECT_NAME} PUBLIC
                ../libs/lib/x64
	)
	target_link_libraries(${PROJECT_NAME} PUBLIC
		Packet
		wpcap
	)
elseif(UNIX)
    target_include_directories(${PROJECT_NAME} PUBLIC
        ../include
        /usr/include
        )
    target_link_libraries(${PROJECT_NAME} PUBLIC
        pcap
        pthread
        )
endif()
