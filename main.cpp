#include "TCPChannel.h"

class my_handler :public AZinxHandler {
	// 通过 AZinxHandler 继承
	virtual IZinxMsg * InternelHandle(IZinxMsg & _oInput) override
	{
		/*取出TCP收到的数据*/
		GET_REF2DATA(BytesMsg, byte, _oInput);
		/*回显回去*/
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
	// 通过 TCPDataChannel 继承
	virtual AZinxHandler * GetInputNextStage(BytesMsg & _oInput) override
	{
		return &mh;
	}
};

class my_listenFact :public TCPConnFact {
	// 通过 TCPConnFact 继承
	virtual TCPDataChannel * CreateTcpDataChannel(int _fd) override
	{
		return new my_tcp_channel(_fd);
	}
};

int main()
{
	auto plistenChannel = new TCPListenChannel(54321, new my_listenFact());
	ZinxKernel::ZinxKernelInit();
	ZinxKernel::Zinx_Add_Channel(*plistenChannel);
	ZinxKernel::Zinx_Run();
}