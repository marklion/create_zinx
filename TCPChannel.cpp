#include "TCPChannel.h"


TCPDataChannel::~TCPDataChannel()
{
}

bool TCPDataChannel::Init()
{
	/*如果是否服务器数据通道---》啥都不干*/
	if (isServer)
	{
		return true;
	}

	/*否则（客户端）----》socket，connect*/
	bool bRet = false;
	int iSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (iSocket >= 0)
	{
		struct sockaddr_in server_addr;
		server_addr.sin_family = AF_INET;
		server_addr.sin_port = htons(m_port);
		server_addr.sin_addr.s_addr = inet_addr(m_ip.c_str());

		/*设置socket为非阻塞*/
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
				/*正在连---》啥都不干*/
				bRet = true;
				m_socket = iSocket;
			}
			else
			{
				/*连接失败，关掉*/
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
	/*读socket数据，通过input参数带出*/
	char buff[1024] = { 0 };
	/*循环收，收完（接收长度< 总长度）为止*/
	while (1)
	{
		int recv_len = recv(m_socket, buff, sizeof(buff), MSG_DONTWAIT);
		/*第一次读socket得到的长度==0   ----》 连接断了---》返回false*/
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

	/*连接断开处理--->设置删除标记*/
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
	/*关闭数据socket*/
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
	/*监听通道初始化*/
	int iListenSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (iListenSocket >= 0)
	{
		struct sockaddr_in server_addr;
		server_addr.sin_family = AF_INET;
		server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
		server_addr.sin_port = htons(m_port);
		/*设置允许端口复用*/
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
	/*有客户端连接后会被调用*/
	struct sockaddr_in client_addr;
	socklen_t addr_len = sizeof(client_addr);
	int iDataSocket = accept(m_listen_socket, (struct sockaddr *)(&client_addr), &addr_len);
	if (iDataSocket >= 0)
	{
		/*创建数据通道对象---->调用工厂的创建函数*/
		auto pDataChannel = m_fact->CreateTcpDataChannel(iDataSocket);
		/*添加通道对象到kernel中*/
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
	/*自己已经处理完连接了，无需后续步骤*/
	return nullptr;
}
