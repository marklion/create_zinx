#pragma once
#include <string>
#include "AZinxHandler.h"

class Ichannel;
class FuncProcess:public AZinxHandler
{
public:
	FuncProcess();
	virtual ~FuncProcess();

	/*存储输出所需的通道对象指针*/
	Ichannel *m_output_channel = NULL;

	/*数据处理函数*/
	bool DataProc(std::string _data);

	// 通过 AZinxHandler 继承
	virtual message * internelHandle(message & _input) override;
	virtual AZinxHandler * GetNext(message & _next) override;
};

