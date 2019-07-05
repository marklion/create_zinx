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

	// ͨ�� Ichannel �̳�
	virtual bool init() override;
	virtual void fini() override;

	// ͨ�� Ichannel �̳�
	virtual ZinxHandler * GetInputNextStage(ByteMsg * _byte) override;
};

