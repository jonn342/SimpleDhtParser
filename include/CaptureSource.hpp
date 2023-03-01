#ifndef CAPTURE_SOURCE_HPP
#define CAPTURE_SOURCE_HPP


struct pcap_rmtauth;
struct pcap;


namespace task_1
{
	class CaptureSource;

	/*
	 * @brief Класс-уничтожитель единственного экземпляра CaptureSource
	*/
	class CaptureSourceDestroyer
	{
	public:

		/*
		 * @brief Деструктор
		*/
		~CaptureSourceDestroyer();

		/*
		 * @brief Функция инициализации
		 * @param ptr - указатель на единственный экземпляр CaptureSource
		*/
		void initialize(CaptureSource* ptr);

	private:
		// Указатель на единственный экземпляр CaptureSource
		CaptureSource* _ptr = nullptr;
	};


	/**
	 *	@brief Класс, определяющий устройство захвата для перехвата пакетов
	 */
	class CaptureSource
	{
	private:
		friend class CaptureSourceDestroyer;

		/*
		 * @brief Конструктор по-умолчанию
		 */
		CaptureSource() = delete;

		/**
		 * @brief Конструктор с параметрами
		 * @param device - имя устройства
		 * @param packet_bytes_needed_for_capture - количество байт пакета, которые будут захвачены
		 * @param promiscuous_mode - флаг, установленный, что захват пакетов будет совершён хаотично
		 * @param read_timeout - задержка перед повторным чтением пакетов (мс)
		 * @param auth_ptr - указатель на структуру, которая хранит информацию, необходимую для
		 *					 аутентификации пользователя на удаленной машине. Если это не удаленный захват,
		 *					 этот указатель может быть установлен на NULL.
		 */
		CaptureSource(const char* device,
			int packet_bytes_needed_for_capture = 65535,
			int promiscuous_mode = 1,
			int read_timeout = 1000,
			pcap_rmtauth* auth_ptr = nullptr
			);

	public:
		/*
		 * @brief Функция инициализации единственного объекта CaptureSource
		 */
		static CaptureSource& instance(const char* device,
										int packet_bytes_needed_for_capture = 65535,
										int promiscuous_mode = 1,
										int read_timeout = 1000,
										pcap_rmtauth* auth_ptr = nullptr);

		/*
		 * @brief Деструктор
		 */
		~CaptureSource();

		/*
		 * @brief Перегруженный оператор преобразования
		 * @return Возвращает дескриптор захваченного устройства
		*/
		operator pcap* ()const;

		/*
		 * @brief Возвращает дескриптор захваченного устройства
		*/
		const pcap* get_descriptor()const;

	private:
		// Дескриптор захваченного устройства
		pcap* _addescriptor;

		// Указатель на единственный экземпляр CaptureSource
		static CaptureSource* _ptr;

		// Уничтожитель CaptureSource
		static CaptureSourceDestroyer _destroyer;
	};
}

#endif
