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

/*IO调度*/
void kernel::run()
{
	/*IO多路复用---》epoll*/
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
			/*继续判断是否有out事件*/
			if (0 != (EPOLLOUT & astEvent[i].events))
			{
				IO_direction dic(IO_direction::OUT);
				pchannel->Handle(dic);
			}
			/*若通道需要删除---》删掉*/
			if (pchannel->NeedDel())
			{
				/*先摘后删*/
				DelChannel(pchannel);
				delete pchannel;
			}
		}
	}
}

bool kernel::init()
{
	bool bRet = false;
	/*创建epllfd*/
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
	/*记录通道对象的地址到data的指针中*/
	my_event.data.ptr = _pchannel;
	/*添加通道的fd到epoll里*/
	if (0 == epoll_ctl(m_epollFd, EPOLL_CTL_ADD, _pchannel->GetFd(), &my_event))
	{
		bRet = true;
		/*记录参数到channel_list*/
		m_channel_list.push_back(_pchannel);
	}
	return bRet;
}

void kernel::DelChannel(Ichannel * _pchannel)
{
	epoll_ctl(m_epollFd, EPOLL_CTL_DEL, _pchannel->GetFd(), nullptr);
	
	/*从channel_list里摘出通道对象*/
	m_channel_list.remove(_pchannel);
}

void kernel::ChannelOutAdd(Ichannel * _pchannel)
{
	struct epoll_event my_event;
	my_event.events = EPOLLIN|EPOLLOUT;
	/*记录通道对象的地址到data的指针中*/
	my_event.data.ptr = _pchannel;
	/*修改通道的fd到为EPOLLOUT*/
	epoll_ctl(m_epollFd, EPOLL_CTL_MOD, _pchannel->GetFd(), &my_event);
}

void kernel::ChannelOutDel(Ichannel * _pchannel)
{
	struct epoll_event my_event;
	my_event.events = EPOLLIN;
	/*记录通道对象的地址到data的指针中*/
	my_event.data.ptr = _pchannel;
	/*修改通道的fd到为EPOLLOUT*/
	epoll_ctl(m_epollFd, EPOLL_CTL_MOD, _pchannel->GetFd(), &my_event);
}

