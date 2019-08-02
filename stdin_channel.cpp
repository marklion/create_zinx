#include "stdin_channel.h"
#include <iostream>


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
	/*处理：回显到标准输出*/
	return m_output_channel->SendOut(_input);
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
