#ifndef PACKET_READER_HPP
#define PACKET_READER_HPP

struct pcap;

namespace task_1
{
	struct FullPacket;
	class PacketReader;

	/*
	 * @brief Класс-уничтожитель единственного экземпляра PacketReader
	*/
	class PacketReaderDestroyer
	{
	public:
		/*
		* @brief Деструктор
		*/
		~PacketReaderDestroyer();

		/*
		* @brief Функция инициализации
		* @param ptr - указатель на единственный экземпляр PacketReader
		*/ 
		void initialize(PacketReader* ptr);

	private:
		// Указатель на единственный экземпляр PacketReader
		PacketReader* _ptr = nullptr;
	};


	/*
	 * @brief Перехватчик пакетов
	 */
	class PacketReader
	{
	private:
		/*
		 * @brief Конструктор по-умолчанию
		*/
		PacketReader() = delete;

		/*
		 * @brief Конструктор с параметрами
		 * @param device_descriptor - дескриптор захваченного устройства
		 */
		PacketReader(pcap* device_descriptor);


	public:
		/*
		 * @brief Функция инициализации единственного объекта CaptureSource
		*/
		static PacketReader& instance(pcap* device_descriptor);

		/*
		 * @brief Прочитать пакет
		 * @param info - структура, куда записываются все данные из пакета
		 * @return Возвращает true, если пакет прочитан удачно. Иначе - false
		*/
		bool get_next_packet(FullPacket& info);

	private:
		//Дескриптор захваченного устройства
		pcap* _device_descriptor = nullptr;

		// Указатель на единственный экземпляр PacketReader
		static PacketReader* _ptr;
		
		//Уничтожитель PacketReader
		static PacketReaderDestroyer _destroyer;
	};
}


#endif
