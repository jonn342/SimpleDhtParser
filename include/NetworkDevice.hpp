#ifndef NETWORK_DEVICE_HPP
#define NETWORK_DEVICE_HPP

#include <string>
#include <pcap.h>

namespace task_1
{
	class NetworkDevice;
	
	/*
	* @brief �����-������������ ������������� ����������  NetworkDevice
	*/
	class NetworkDeviceDestroyer
	{
	public:

		/*
		* @brief ����������
		*/
		~NetworkDeviceDestroyer();

		/*
		 * @brief ������� �������������
		 * @param ptr - ��������� �� ������������ ��������� NetworkDevice
		*/
		void initialize(NetworkDevice* ptr);

	private:
		// ��������� �� ������������ ��������� NetworkDevice
		NetworkDevice* _ptr = nullptr;
	};


	/*
	 * @brief ����������� �� �� ������� ���������
	 */
	class NetworkDevice
	{
	private:
		friend class NetworkDeviceDestroyer;

		/*
		 * @brief ����������� ��-���������
		 */
		NetworkDevice() = delete;

		/*
		 * @brief ����������� � �����������
		 * @param ��� �������� ���������� Windows: ��� ��������� -> ���������� -> ��������� ��������� -> ������� ����������
		 *								  Linux: ������� � ������� "ip a", ������ �����, ��� ���������� - eth0
		 */
		NetworkDevice(std::string&& device_description);

	public:
		/*
		 * @brief ������� ������������� ������������� ������� NetworkDevice
		 */
		static NetworkDevice& instance(std::string&& device_description);

		/*
		 * @brief ������������� �������� ��������������
		 * @return ���������� ������ ��� �������� ����������
		 */
		operator const char* ()const;

		/*
		 * @brief ���������� ��� �������� ����������
		 */
		const std::string& get_device_name()const;

		/* 
		 * @brief ���������� �������� �������� ����������
		 */
		const std::string& get_device_description()const;

		/*
		* @brief ���������� ����� �������� ���������� (����� ��� ��������� ������� �������� �������)			
		*/
		long get_netmask()const;

	private:
		// ��� � �������� �������� ����������
		std::string _device_name, _device_description;

		//����� �������� ����������
        long _netmask;
		
		// ��������� �� ������������ ��������� NetworkDevice
		static NetworkDevice* _ptr;

		// ������������ NetworkDevice
		static NetworkDeviceDestroyer _destroyer;
	};
}

#endif
