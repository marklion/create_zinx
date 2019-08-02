#pragma once
#include "Ichannel.h"
class stdout_channel :
	public Ichannel
{
public:
	stdout_channel();
	virtual ~stdout_channel();

	// ͨ�� Ichannel �̳�
	virtual std::string ReadFd() override;
	virtual int WriteFd(std::string _output) override;
	virtual int GetFd() override;

	// ͨ�� Ichannel �̳�
	virtual AZinxHandler * GetNextInputStage(message & _next) override;
};

