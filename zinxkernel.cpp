#include "zinxkernel.h"
#include <sys/epoll.h>
#include <unistd.h>
#include <iostream>

using namespace std;

zinxkernel zinxkernel::kernel;

zinxkernel::zinxkernel()
{
	int fd = epoll_create(1);
	if (fd >= 0)
	{
		m_epollFd = fd;
	}
}

zinxkernel::~zinxkernel()
{
	if (-1 != m_epollFd)
	{
		close(m_epollFd);
	}
}

void zinxkernel::run()
{
	while (1)
	{
		//1�����루epoll��
		struct epoll_event astEvents[200];
		int ready_count = epoll_wait(m_epollFd, astEvents, 200, -1);
		if (0 == ready_count)
		{
			if (EINTR == errno)
			{
				continue;
			}
		}
		//2����ͨ���Ķ�ȡ������д������
		for (int i = 0; i < ready_count; i++)
		{
			if (0 != (astEvents[i].events & EPOLLIN))
			{
				//��Ҫ�����ⲿ���������
				/*1.��������*/
				auto pchannel = static_cast<Ichannel *> (astEvents[i].data.ptr);
				auto content = pchannel->ReadFd();
				/*2.��������*/
				pchannel->data_process(content);
			}
			if (0 != (astEvents[i].events & EPOLLOUT))
			{
				//��Ҫ�������������
				auto pchannel = static_cast<Ichannel *> (astEvents[i].data.ptr);
				pchannel->flushout();
				//ɾ����������epoll����
				ModChannel_DelOut(pchannel);
			}
		}
	}	
}

void zinxkernel::AddChannel(Ichannel * _pChannel)
{
	if (true == _pChannel->init())
	{
		//���������ļ�������0����������epoll_ctl��
		struct epoll_event stEvent;
		stEvent.events = EPOLLIN;
		stEvent.data.ptr = _pChannel;

		epoll_ctl(m_epollFd, EPOLL_CTL_ADD, _pChannel->GetFd(), &stEvent);
	}
}

void zinxkernel::DelChannel(Ichannel * _pChannel)
{
	epoll_ctl(m_epollFd, EPOLL_CTL_DEL, _pChannel->GetFd(), NULL);
	_pChannel->fini();
}

void zinxkernel::ModChannel_AddOut(Ichannel * _pChannel)
{
	struct epoll_event stEvent;
	stEvent.events = EPOLLIN | EPOLLOUT;
	stEvent.data.ptr = _pChannel;
	epoll_ctl(m_epollFd, EPOLL_CTL_MOD, _pChannel->GetFd(), &stEvent);
}

void zinxkernel::ModChannel_DelOut(Ichannel * _pChannel)
{
	struct epoll_event stEvent;
	stEvent.events = EPOLLIN;
	stEvent.data.ptr = _pChannel;
	epoll_ctl(m_epollFd, EPOLL_CTL_MOD, _pChannel->GetFd(), &stEvent);
}
