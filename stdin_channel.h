#pragma once
#include <string>
#include "Ichannel.h"

class stdin_channel:public Ichannel
{
public:
	stdin_channel();
	virtual ~stdin_channel();

	/*�洢��������ͨ������ָ��*/
	Ichannel *m_output_channel = NULL;


	// ͨ�� Ichannel �̳�
	virtual std::string ReadFd() override;

	virtual int WriteFd(std::string _output) override;

	virtual int GetFd() override;

	virtual bool Process(std::string _input) override;
};

