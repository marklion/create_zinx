#pragma once
#include "Ichannel.h"
class stdou_channel :
	public Ichannel
{
public:
	stdou_channel();
	virtual ~stdou_channel();

	// ͨ�� Ichannel �̳�
	virtual std::string ReadFd() override;
	virtual void WriteFd(std::string _output) override;
	virtual int GetFd() override;
	virtual void data_process(std::string _input) override;
};

