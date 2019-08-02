#pragma once
#include <string>
#include "Ichannel.h"

class FuncProcess;
class stdin_channel:public Ichannel
{
public:
	stdin_channel();
	virtual ~stdin_channel();

	/*�����ݴ���������ָ��*/
	FuncProcess *m_process = NULL;


	// ͨ�� Ichannel �̳�
	virtual std::string ReadFd() override;

	virtual int WriteFd(std::string _output) override;

	virtual int GetFd() override;

	virtual bool Process(std::string _input) override;
};

