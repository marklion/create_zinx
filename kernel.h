#pragma once

/*������*/
class stdin_channel;

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

	/*��ӱ�׼����ͨ������*/
	bool AddChannel(stdin_channel *_pchannel);
	/*ժ����׼����ͨ������*/
	void DelChannel(stdin_channel *_pchannel);

	/*����һ����׼����ͨ����Ķ���---�����ȵĶ���*/
	stdin_channel *pChannel  = nullptr;
};

