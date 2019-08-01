#pragma once
#include <string>
#include "Ichannel.h"

class stdin_channel:public Ichannel
{
public:
	stdin_channel();
	virtual ~stdin_channel();


	// ͨ�� Ichannel �̳�
	virtual std::string ReadFd() override;

	virtual int WriteFd(std::string _output) override;

	virtual int GetFd() override;

	virtual bool Process(std::string _input) override;

	virtual bool SendOut(std::string _output) override;

};

