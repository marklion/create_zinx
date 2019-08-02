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

bool stdin_channel::Process(std::string _input)
{
	/*处理：交给功能处理类处理*/

	return m_process->DataProc(_input);
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
