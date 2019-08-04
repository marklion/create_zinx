#pragma once
#include "zinx.h"
#include <string>
class TCPDataChannel :
	public Ichannel
{
	int m_socket = -1;
	/*��־λ����---��������TCP����ͨ��������----���ͻ���TCP����ͨ��*/
	bool isServer = true;
	std::string m_ip;
	unsigned short m_port = 0;
public:
	TCPDataChannel(int _socket):m_socket(_socket),isServer(true) {}
	/*��̬��̬�����ع��캯������ʱ����Ķ���ʱ�ͻ���TCPͨ��*/
	TCPDataChannel(std::string _ip, unsigned short _port):m_ip(_ip),m_port(_port), isServer(false) {}
	virtual ~TCPDataChannel();

	// ͨ�� Ichannel �̳�
	virtual bool Init() override;
	virtual bool ReadFd(std::string & _input) override;
	virtual bool WriteFd(std::string & _output) override;
	virtual void Fini() override;
	virtual int GetFd() {
		return m_socket;
	}
	virtual std::string GetChannelInfo() override;
	/*����д��ȡ��һ�����ڵĺ���----�������û�д*/
};

class TCPConnFact {
public:
	/*��������ͨ������������ͨ����Ӧfd����Ҫ����ָ��ͨ������Ӧ��fd*/
	virtual TCPDataChannel *CreateTcpDataChannel(int _fd) = 0;
};

class TCPListenChannel :public Ichannel {
public:
	TCPListenChannel(unsigned short _port, TCPConnFact *_fact):m_port(_port),m_fact(_fact) {}
	unsigned short m_port = 0;
	int m_listen_socket = -1;
	TCPConnFact *m_fact = NULL;
	// ͨ�� Ichannel �̳�
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

