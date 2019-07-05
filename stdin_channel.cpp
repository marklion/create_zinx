#include "stdin_channel.h"
#include <iostream>


stdin_channel::stdin_channel()
{
}


stdin_channel::~stdin_channel()
{
}

void stdin_channel::WriteFd(std::string _output)
{
}

int stdin_channel::GetFd()
{
	return 0;
}

void stdin_channel::data_process(std::string _input)
{
	//将数据交给process_func类处理
	m_proc->DataProcess(_input);
}

bool stdin_channel::init()
{
	return true;
}

void stdin_channel::fini()
{
}

std::string stdin_channel::ReadFd()
{
	std::string ret;
	std::cin >> ret;
	return ret;
}
