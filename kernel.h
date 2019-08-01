#pragma once

/*类声明*/
class stdin_channel;

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

	/*添加标准输入通道对象*/
	bool AddChannel(stdin_channel *_pchannel);
	/*摘除标准输入通道对象*/
	void DelChannel(stdin_channel *_pchannel);

	/*包含一个标准输入通道类的对象---》调度的对象*/
	stdin_channel *pChannel  = nullptr;
};

