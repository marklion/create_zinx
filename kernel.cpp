#include "kernel.h"
#include <sys/epoll.h>
#include <unistd.h>
#include "stdin_channel.h"
#include <iostream>

using namespace std;

kernel::kernel()
{
}


kernel::~kernel()
{
}

/*IO����*/
void kernel::run()
{
	/*IO��·����---��epoll*/
	while (1)
	{
		struct epoll_event astEvent[789];
		int event_count = epoll_wait(m_epollFd, astEvent, 789, -1);
		if (event_count < 0)
		{
			if (errno == EINTR)
			{
				continue;
			}
			else
			{
				break;
			}
		}
		if (event_count == 0)
		{
			break;
		}
		for (int i = 0; i < event_count; i++)
		{
			if (0 != (astEvent[i].events & EPOLLIN))
			{
				/*����׼����ͨ���Ķ�ȡ��*/
				auto pchannel = static_cast<stdin_channel *>(astEvent[i].data.ptr);
				auto input = pchannel->ReadFd();

				/*���Ե���׼���*/
				cout << input << endl;
			}
		}
	}
}

bool kernel::init()
{
	bool bRet = false;
	/*����epllfd*/
	int fd = epoll_create(1);
	if (fd >= 0)
	{
		m_epollFd = fd;
		bRet = true;
	}
	return bRet;
}

void kernel::fini()
{
	if (m_epollFd >= 0)
	{
		close(m_epollFd);
		m_epollFd = -1;
	}
}

bool kernel::AddChannel(stdin_channel * _pchannel)
{
	bool bRet = false;
	struct epoll_event my_event;
	my_event.events = EPOLLIN;
	/*��¼��׼����ͨ������ĵ�ַ��data��ָ����*/
	my_event.data.ptr = _pchannel;
	/*��ӱ�׼����ͨ����fd��epoll��*/
	if (0 == epoll_ctl(m_epollFd, EPOLL_CTL_ADD, _pchannel->GetFd(), &my_event))
	{
		bRet = true;
		pChannel = _pchannel;
	}
	return bRet;
}

void kernel::DelChannel(stdin_channel * _pchannel)
{
	epoll_ctl(m_epollFd, EPOLL_CTL_DEL, _pchannel->GetFd(), nullptr);
	pChannel = nullptr;
}
