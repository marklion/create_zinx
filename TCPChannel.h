#pragma once
#include "zinx.h"
#include <string>
class TCPDataChannel :
	public Ichannel
{
	int m_socket = -1;
	/*标志位，真---》服务器TCP数据通道，否则----》客户端TCP数据通道*/
	bool isServer = true;
	std::string m_ip;
	unsigned short m_port = 0;
public:
	TCPDataChannel(int _socket):m_socket(_socket),isServer(true) {}
	/*静态多态：重载构造函数，此时构造的对象时客户端TCP通道*/
	TCPDataChannel(std::string _ip, unsigned short _port):m_ip(_ip),m_port(_port), isServer(false) {}
	virtual ~TCPDataChannel();

	// 通过 Ichannel 继承
	virtual bool Init() override;
	virtual bool ReadFd(std::string & _input) override;
	virtual bool WriteFd(std::string & _output) override;
	virtual void Fini() override;
	virtual int GetFd() {
		return m_socket;
	}
	virtual std::string GetChannelInfo() override;
	/*不重写获取下一个环节的函数----》交给用户写*/
};

class TCPConnFact {
public:
	/*创建数据通道函数，数据通道对应fd，需要参数指定通道所对应的fd*/
	virtual TCPDataChannel *CreateTcpDataChannel(int _fd) = 0;
};

class TCPListenChannel :public Ichannel {
public:
	TCPListenChannel(unsigned short _port, TCPConnFact *_fact):m_port(_port),m_fact(_fact) {}
	unsigned short m_port = 0;
	int m_listen_socket = -1;
	TCPConnFact *m_fact = NULL;
	// 通过 Ichannel 继承
	virtual bool Init() override;
	virtual bool ReadFd(std::string & _input) override;
	virtual bool WriteFd(std::string & _output) override;
	virtual void Fini() override;
	virtual int GetFd() {
		return m_listen_socket;
	}
	virtual std::string GetChannelInfo() override;
	virtual AZinxHandler * GetInputNextStage(BytesMsg & _oInput) override;
};

