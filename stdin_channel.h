#pragma once
#include <string>
#include "Ichannel.h"
#include "stdou_channel.h"
#include "ProcessFunc.h"

class stdin_channel:public Ichannel
{
	
public:
	stdin_channel();
	virtual ~stdin_channel();
	ProcessFunc *m_proc = NULL;

	// ͨ�� Ichannel �̳�
	virtual std::string ReadFd() override;
	virtual void WriteFd(std::string _output) override;
	virtual int GetFd() override;
	virtual void data_process(std::string _input) override;

	// ͨ�� Ichannel �̳�
	virtual bool init() override;
	virtual void fini() override;
};

