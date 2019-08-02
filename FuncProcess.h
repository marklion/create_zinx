#pragma once
#include <string>

class Ichannel;
class FuncProcess
{
public:
	FuncProcess();
	virtual ~FuncProcess();

	/*存储输出所需的通道对象指针*/
	Ichannel *m_output_channel = NULL;

	/*数据处理函数*/
	bool DataProc(std::string _data);
};

