#include "kernel.h"
#include <sys/epoll.h>
#include <unistd.h>
#include "stdin_channel.h"
#include <iostream>
#include "AZinxHandler.h"

using namespace std;

kernel kernel::k;

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
			auto pchannel = static_cast<Ichannel *>(astEvent[i].data.ptr);
			if (0 != (astEvent[i].events & EPOLLIN))
			{
				IO_direction dic(IO_direction::IN);
				pchannel->Handle(dic);
			}
			/*�����ж��Ƿ���out�¼�*/
			if (0 != (EPOLLOUT & astEvent[i].events))
			{
				IO_direction dic(IO_direction::OUT);
				pchannel->Handle(dic);
			}
			/*��ͨ����Ҫɾ��---��ɾ��*/
			if (pchannel->NeedDel())
			{
				/*��ժ��ɾ*/
				DelChannel(pchannel);
				delete pchannel;
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

bool kernel::AddChannel(Ichannel * _pchannel)
{
	bool bRet = false;
	struct epoll_event my_event;
	my_event.events = EPOLLIN;
	/*��¼ͨ������ĵ�ַ��data��ָ����*/
	my_event.data.ptr = _pchannel;
	/*���ͨ����fd��epoll��*/
	if (0 == epoll_ctl(m_epollFd, EPOLL_CTL_ADD, _pchannel->GetFd(), &my_event))
	{
		bRet = true;
		/*��¼������channel_list*/
		m_channel_list.push_back(_pchannel);
	}
	return bRet;
}

void kernel::DelChannel(Ichannel * _pchannel)
{
	epoll_ctl(m_epollFd, EPOLL_CTL_DEL, _pchannel->GetFd(), nullptr);
	
	/*��channel_list��ժ��ͨ������*/
	m_channel_list.remove(_pchannel);
}

void kernel::ChannelOutAdd(Ichannel * _pchannel)
{
	struct epoll_event my_event;
	my_event.events = EPOLLIN|EPOLLOUT;
	/*��¼ͨ������ĵ�ַ��data��ָ����*/
	my_event.data.ptr = _pchannel;
	/*�޸�ͨ����fd��ΪEPOLLOUT*/
	epoll_ctl(m_epollFd, EPOLL_CTL_MOD, _pchannel->GetFd(), &my_event);
}

void kernel::ChannelOutDel(Ichannel * _pchannel)
{
	struct epoll_event my_event;
	my_event.events = EPOLLIN;
	/*��¼ͨ������ĵ�ַ��data��ָ����*/
	my_event.data.ptr = _pchannel;
	/*�޸�ͨ����fd��ΪEPOLLOUT*/
	epoll_ctl(m_epollFd, EPOLL_CTL_MOD, _pchannel->GetFd(), &my_event);
}

