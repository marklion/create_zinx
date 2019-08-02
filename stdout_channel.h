#pragma once
#include "Ichannel.h"
class stdout_channel :
	public Ichannel
{
public:
	stdout_channel();
	virtual ~stdout_channel();

	// 通过 Ichannel 继承
	virtual std::string ReadFd() override;
	virtual int WriteFd(std::string _output) override;
	virtual int GetFd() override;

	// 通过 Ichannel 继承
	virtual AZinxHandler * GetNextInputStage(message & _next) override;
};

