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
	/*�����������ܴ����ദ��*/

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
