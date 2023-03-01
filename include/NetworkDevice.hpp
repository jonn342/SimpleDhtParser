#ifndef NETWORK_DEVICE_HPP
#define NETWORK_DEVICE_HPP

#include <string>
#include <pcap.h>

namespace task_1
{
	class NetworkDevice;
	
	/*
	* @brief Класс-уничтожитель единственного экземпляра  NetworkDevice
	*/
	class NetworkDeviceDestroyer
	{
	public:

		/*
		* @brief Деструктор
		*/
		~NetworkDeviceDestroyer();

		/*
		 * @brief Функция инициализации
		 * @param ptr - указатель на единственный экземпляр NetworkDevice
		*/
		void initialize(NetworkDevice* ptr);

	private:
		// Указатель на единственный экземпляр NetworkDevice
		NetworkDevice* _ptr = nullptr;
	};


	/*
	 * @brief Определённый на пк сетевой интерфейс
	 */
	class NetworkDevice
	{
	private:
		friend class NetworkDeviceDestroyer;

		/*
		 * @brief Конструктор по-умолчанию
		 */
		NetworkDevice() = delete;

		/*
		 * @brief Конструктор с параметрами
		 * @param Имя сетевого интерфейса Windows: Мой компьютер -> Управление -> Диспетчер устройств -> Сетевые интерфейсы
		 *								  Linux: Набрать в консоли "ip a", скорее всего, имя интерфейса - eth0
		 */
		NetworkDevice(std::string&& device_description);

	public:
		/*
		 * @brief Функция инициализации единственного объекта NetworkDevice
		 */
		static NetworkDevice& instance(std::string&& device_description);

		/*
		 * @brief Перегруженный оператор преобразования
		 * @return Возвращает полное имя сетевого интерфейса
		 */
		operator const char* ()const;

		/*
		 * @brief Возвращает имя сетевого интерфейса
		 */
		const std::string& get_device_name()const;

		/* 
		 * @brief Возвращает описание сетевого интерфейса
		 */
		const std::string& get_device_description()const;

		/*
		* @brief Возвращает маску сетевого интерфейса (нужна для настройки фильтра сетевого трафика)			
		*/
		long get_netmask()const;

	private:
		// Имя и описание сетевого интерфейса
		std::string _device_name, _device_description;

		//Маска сетевого интерфейса
        long _netmask;
		
		// Указатель на единственный экземпляр NetworkDevice
		static NetworkDevice* _ptr;

		// Уничтожитель NetworkDevice
		static NetworkDeviceDestroyer _destroyer;
	};
}

#endif
