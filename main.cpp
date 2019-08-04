#include "TCPChannel.h"

class my_handler :public AZinxHandler {
	// ͨ�� AZinxHandler �̳�
	virtual IZinxMsg * InternelHandle(IZinxMsg & _oInput) override
	{
		/*ȡ��TCP�յ�������*/
		GET_REF2DATA(BytesMsg, byte, _oInput);
		/*���Ի�ȥ*/
		ZinxKernel::Zinx_SendOut(byte.szData, *(ZinxKernel::Zinx_GetChannel_ByInfo(byte.szInfo)));
		return nullptr;
	}
	virtual AZinxHandler * GetNextHandler(IZinxMsg & _oNextMsg) override
	{
		return nullptr;
	}
};

my_handler mh;

class my_tcp_channel :public TCPDataChannel {
public:
	my_tcp_channel(int _fd) :TCPDataChannel(_fd){}
	// ͨ�� TCPDataChannel �̳�
	virtual AZinxHandler * GetInputNextStage(BytesMsg & _oInput) override
	{
		return &mh;
	}
};

class my_tcp_client :public TCPDataChannel {
public:
	my_tcp_client(std::string _ip, unsigned short _port):TCPDataChannel(_ip, _port) {}
	// ͨ�� TCPDataChannel �̳�
	virtual AZinxHandler * GetInputNextStage(BytesMsg & _oInput) override
	{
		return &mh;
	}
};

class my_listenFact :public TCPConnFact {
	// ͨ�� TCPConnFact �̳�
	virtual TCPDataChannel * CreateTcpDataChannel(int _fd) override
	{
		return new my_tcp_channel(_fd);
	}
};

int main()
{
	auto plistenChannel = new TCPListenChannel(54321, new my_listenFact());
	auto pclientChannel = new my_tcp_client("192.168.64.1", 43210);
	ZinxKernel::ZinxKernelInit();
	ZinxKernel::Zinx_Add_Channel(*plistenChannel);
	ZinxKernel::Zinx_Add_Channel(*pclientChannel);
	ZinxKernel::Zinx_Run();
}