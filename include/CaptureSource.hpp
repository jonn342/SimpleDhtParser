#ifndef CAPTURE_SOURCE_HPP
#define CAPTURE_SOURCE_HPP


struct pcap_rmtauth;
struct pcap;


namespace task_1
{
	class CaptureSource;

	/*
	 * @brief �����-������������ ������������� ���������� CaptureSource
	*/
	class CaptureSourceDestroyer
	{
	public:

		/*
		 * @brief ����������
		*/
		~CaptureSourceDestroyer();

		/*
		 * @brief ������� �������������
		 * @param ptr - ��������� �� ������������ ��������� CaptureSource
		*/
		void initialize(CaptureSource* ptr);

	private:
		// ��������� �� ������������ ��������� CaptureSource
		CaptureSource* _ptr = nullptr;
	};


	/**
	 *	@brief �����, ������������ ���������� ������� ��� ��������� �������
	 */
	class CaptureSource
	{
	private:
		friend class CaptureSourceDestroyer;

		/*
		 * @brief ����������� ��-���������
		 */
		CaptureSource() = delete;

		/**
		 * @brief ����������� � �����������
		 * @param device - ��� ����������
		 * @param packet_bytes_needed_for_capture - ���������� ���� ������, ������� ����� ���������
		 * @param promiscuous_mode - ����, �������������, ��� ������ ������� ����� �������� ��������
		 * @param read_timeout - �������� ����� ��������� ������� ������� (��)
		 * @param auth_ptr - ��������� �� ���������, ������� ������ ����������, ����������� ���
		 *					 �������������� ������������ �� ��������� ������. ���� ��� �� ��������� ������,
		 *					 ���� ��������� ����� ���� ���������� �� NULL.
		 */
		CaptureSource(const char* device,
			int packet_bytes_needed_for_capture = 65535,
			int promiscuous_mode = 1,
			int read_timeout = 1000,
			pcap_rmtauth* auth_ptr = nullptr
			);

	public:
		/*
		 * @brief ������� ������������� ������������� ������� CaptureSource
		 */
		static CaptureSource& instance(const char* device,
										int packet_bytes_needed_for_capture = 65535,
										int promiscuous_mode = 1,
										int read_timeout = 1000,
										pcap_rmtauth* auth_ptr = nullptr);

		/*
		 * @brief ����������
		 */
		~CaptureSource();

		/*
		 * @brief ������������� �������� ��������������
		 * @return ���������� ���������� ������������ ����������
		*/
		operator pcap* ()const;

		/*
		 * @brief ���������� ���������� ������������ ����������
		*/
		const pcap* get_descriptor()const;

	private:
		// ���������� ������������ ����������
		pcap* _addescriptor;

		// ��������� �� ������������ ��������� CaptureSource
		static CaptureSource* _ptr;

		// ������������ CaptureSource
		static CaptureSourceDestroyer _destroyer;
	};
}

#endif
