#include "TCPChannel.h"


TCPDataChannel::~TCPDataChannel()
{
}

bool TCPDataChannel::Init()
{
	/*����Ƿ����������ͨ��---��ɶ������*/
	if (isServer)
	{
		return true;
	}

	/*���򣨿ͻ��ˣ�----��socket��connect*/
	bool bRet = false;
	int iSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (iSocket >= 0)
	{
		struct sockaddr_in server_addr;
		server_addr.sin_family = AF_INET;
		server_addr.sin_port = htons(m_port);
		server_addr.sin_addr.s_addr = inet_addr(m_ip.c_str());

		/*����socketΪ������*/
		int flag = fcntl(iSocket, F_GETFL);
		flag |= O_NONBLOCK;
		fcntl(iSocket, F_SETFL, flag);

		if (0 == connect(iSocket, (struct sockaddr *)(&server_addr), sizeof(server_addr)))
		{
			bRet = true;
			m_socket = iSocket;
		}
		else
		{
			if (EINPROGRESS == errno)
			{
				/*������---��ɶ������*/
				bRet = true;
				m_socket = iSocket;
			}
			else
			{
				/*����ʧ�ܣ��ص�*/
				perror("__FILE__:__function__:connect");
				close(iSocket);
			}
		}
	}
	else
	{
		perror("__FILE__:__function__:socket");
	}

	return bRet;
}

bool TCPDataChannel::ReadFd(std::string & _input)
{
	bool bRet = false;
	/*��socket���ݣ�ͨ��input��������*/
	char buff[1024] = { 0 };
	/*ѭ���գ����꣨���ճ���< �ܳ��ȣ�Ϊֹ*/
	while (1)
	{
		int recv_len = recv(m_socket, buff, sizeof(buff), MSG_DONTWAIT);
		/*��һ�ζ�socket�õ��ĳ���==0   ----�� ���Ӷ���---������false*/
		if (recv_len == 0 && _input.size() == 0) {
			break;
		}
		_input.append(buff, recv_len);
		bRet = true;
		if (recv_len < sizeof(buff))
		{
			break;
		}
	}

	/*���ӶϿ�����--->����ɾ�����*/
	if (bRet == false)
	{
		SetChannelClose();
	}
	
	return bRet;
}

bool TCPDataChannel::WriteFd(std::string & _output)
{
	bool bRet = false;
	if (_output.size() == send(m_socket, _output.data(), _output.size(), 0))
	{
		bRet = true;
	}
	return bRet;
}

void TCPDataChannel::Fini()
{
	/*�ر�����socket*/
	if (m_socket >= 0)
	{
		close(m_socket);
		m_socket = -1;
	}
}

std::string TCPDataChannel::GetChannelInfo()
{
	return "TCPDataChannel" + std::to_string(m_socket);
}

bool TCPListenChannel::Init()
{
	bool bRet = false;
	/*����ͨ����ʼ��*/
	int iListenSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (iListenSocket >= 0)
	{
		struct sockaddr_in server_addr;
		server_addr.sin_family = AF_INET;
		server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
		server_addr.sin_port = htons(m_port);
		/*��������˿ڸ���*/
		int flag = 1;
		setsockopt(iListenSocket, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag));

		if (0 == bind(iListenSocket, (struct sockaddr *)(&server_addr), sizeof(server_addr)))
		{
			if (0 == listen(iListenSocket, 10))
			{
				m_listen_socket = iListenSocket;
				bRet = true;
			}
			else
			{
				perror("__FILE__:__function__:listen");
				close(iListenSocket);
			}
		}
		else
		{
			perror("__FILE__:__function__:bind");
			close(iListenSocket);
		}
	}
	else
	{
		perror("__FILE__:__function__:socket");
	}

	return bRet;
}

bool TCPListenChannel::ReadFd(std::string & _input)
{
	bool bRet = false;
	/*�пͻ������Ӻ�ᱻ����*/
	struct sockaddr_in client_addr;
	socklen_t addr_len = sizeof(client_addr);
	int iDataSocket = accept(m_listen_socket, (struct sockaddr *)(&client_addr), &addr_len);
	if (iDataSocket >= 0)
	{
		/*��������ͨ������---->���ù����Ĵ�������*/
		auto pDataChannel = m_fact->CreateTcpDataChannel(iDataSocket);
		/*���ͨ������kernel��*/
		ZinxKernel::Zinx_Add_Channel(*(pDataChannel));
		bRet = true;
	}
	else
	{
		perror("__FILE__:__function__:accept");
	}
	return bRet;
}

bool TCPListenChannel::WriteFd(std::string & _output)
{
	return false;
}

void TCPListenChannel::Fini()
{
	if (m_listen_socket >= 0)
	{
		close(m_listen_socket);
		m_listen_socket = -1;
	}
}

std::string TCPListenChannel::GetChannelInfo()
{
	return "TCPListenChannel" + std::to_string(m_port);
}

AZinxHandler * TCPListenChannel::GetInputNextStage(BytesMsg & _oInput)
{
	/*�Լ��Ѿ������������ˣ������������*/
	return nullptr;
}
