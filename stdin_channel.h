#pragma once
#include <string>
#include "Ichannel.h"

class FuncProcess;
class stdin_channel:public Ichannel
{
public:
	stdin_channel();
	virtual ~stdin_channel();

	/*存数据处理类对象的指针*/
	FuncProcess *m_process = NULL;


	// 通过 Ichannel 继承
	virtual std::string ReadFd() override;

	virtual int WriteFd(std::string _output) override;

	virtual int GetFd() override;

	virtual bool Process(std::string _input) override;
};

