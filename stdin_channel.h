#pragma once
#include <string>
#include "Ichannel.h"
#include "stdou_channel.h"
class stdin_channel:public Ichannel
{
	
public:
	stdin_channel();
	virtual ~stdin_channel();
	stdou_channel *m_out = NULL;

	// Í¨¹ý Ichannel ¼Ì³Ð
	virtual std::string ReadFd() override;
	virtual void WriteFd(std::string _output) override;
	virtual int GetFd() override;
	virtual void data_process(std::string _input) override;
};

