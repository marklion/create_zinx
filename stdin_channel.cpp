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
	/*���ع��ܴ���������ָ��*/
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
