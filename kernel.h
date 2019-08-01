#pragma once
#include <list>

/*类声明*/
class Ichannel;


class kernel
{
public:
	int m_epollFd = -1;
	kernel();
	virtual ~kernel();
	/*重要职责---》循环等待，调度IO*/
	void run();

	/*初始化函数*/
	bool init();

	/*去初始化*/
	void fini();

	/*添加通道对象*/
	bool AddChannel(Ichannel *_pchannel);
	/*摘除通道对象*/
	void DelChannel(Ichannel *_pchannel);

	/*增加epollout监听*/
	void ChannelOutAdd(Ichannel *_pchannel);
	/*删除epollout监听*/
	void ChannelOutDel(Ichannel *_pchannel);

	/*包含若干通道类的对象---》调度的对象*/
	std::list<Ichannel *> m_channel_list;
};

