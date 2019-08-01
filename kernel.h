#pragma once
#include <list>

/*������*/
class Ichannel;


class kernel
{
public:
	int m_epollFd = -1;
	kernel();
	virtual ~kernel();
	/*��Ҫְ��---��ѭ���ȴ�������IO*/
	void run();

	/*��ʼ������*/
	bool init();

	/*ȥ��ʼ��*/
	void fini();

	/*���ͨ������*/
	bool AddChannel(Ichannel *_pchannel);
	/*ժ��ͨ������*/
	void DelChannel(Ichannel *_pchannel);

	/*����epollout����*/
	void ChannelOutAdd(Ichannel *_pchannel);
	/*ɾ��epollout����*/
	void ChannelOutDel(Ichannel *_pchannel);

	/*��������ͨ����Ķ���---�����ȵĶ���*/
	std::list<Ichannel *> m_channel_list;
};

