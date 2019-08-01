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
				/*调用通道类的读取函数*/				
				auto input = pchannel->ReadFd();

				/*把读到的数据交给通道对象处理*/
				if (false == pchannel->Process(input))
				{
					/*设定通道删除标记*/
					pchannel->SetDelFlag();
				}
			}
			/*继续判断是否有out事件*/
			if (0 != (EPOLLOUT & astEvent[i].events))
			{
				int write_len = pchannel->WriteFd(pchannel->output_buff);
				/*若已发数据小于待发数据---》更新缓存*/
				if (write_len < pchannel->output_buff.size())
				{
					/*弹出缓存中已发送的数据*/
					pchannel->output_buff.erase(pchannel->output_buff.begin(), pchannel->output_buff.begin() + write_len);
				}

				/*若全部发送完成,去掉对EPOLLOUT事件的监听,清掉缓存*/
				ChannelOutDel(pchannel);
				pchannel->output_buff.clear();

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

