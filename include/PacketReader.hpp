#ifndef PACKET_READER_HPP
#define PACKET_READER_HPP

struct pcap;

namespace task_1
{
	struct FullPacket;
	class PacketReader;

	/*
	 * @brief �����-������������ ������������� ���������� PacketReader
	*/
	class PacketReaderDestroyer
	{
	public:
		/*
		* @brief ����������
		*/
		~PacketReaderDestroyer();

		/*
		* @brief ������� �������������
		* @param ptr - ��������� �� ������������ ��������� PacketReader
		*/ 
		void initialize(PacketReader* ptr);

	private:
		// ��������� �� ������������ ��������� PacketReader
		PacketReader* _ptr = nullptr;
	};


	/*
	 * @brief ����������� �������
	 */
	class PacketReader
	{
	private:
		/*
		 * @brief ����������� ��-���������
		*/
		PacketReader() = delete;

		/*
		 * @brief ����������� � �����������
		 * @param device_descriptor - ���������� ������������ ����������
		 */
		PacketReader(pcap* device_descriptor);


	public:
		/*
		 * @brief ������� ������������� ������������� ������� CaptureSource
		*/
		static PacketReader& instance(pcap* device_descriptor);

		/*
		 * @brief ��������� �����
		 * @param info - ���������, ���� ������������ ��� ������ �� ������
		 * @return ���������� true, ���� ����� �������� ������. ����� - false
		*/
		bool get_next_packet(FullPacket& info);

	private:
		//���������� ������������ ����������
		pcap* _device_descriptor = nullptr;

		// ��������� �� ������������ ��������� PacketReader
		static PacketReader* _ptr;
		
		//������������ PacketReader
		static PacketReaderDestroyer _destroyer;
	};
}


#endif
