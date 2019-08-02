#include "stdin_channel.h"
#include <iostream>
#include "FuncProcess.h"

stdin_channel::stdin_channel()
{
}


stdin_channel::~stdin_channel()
{
}

int stdin_channel::WriteFd(std::string _output)
{
	return 0;
}

AZinxHandler * stdin_channel::GetNextInputStage(message & _next)
{
	/*返回功能处理类对象的指针*/
	return m_process;
}

std::string stdin_channel::ReadFd()
{
	std::string ret;
	std::cin >> ret;
	return ret;
}

int stdin_channel::GetFd()
{
	return 0;
}
