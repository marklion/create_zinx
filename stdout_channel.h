#pragma once
#include "Ichannel.h"
class stdout_channel :
	public Ichannel
{
public:
	stdout_channel();
	virtual ~stdout_channel();

	// Í¨¹ý Ichannel ¼Ì³Ð
	virtual std::string ReadFd() override;
	virtual int WriteFd(std::string _output) override;
	virtual int GetFd() override;
	virtual bool Process(std::string _input) override;
};

