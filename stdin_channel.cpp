#include "stdin_channel.h"
#include <iostream>


stdin_channel::stdin_channel()
{
}


stdin_channel::~stdin_channel()
{
}

std::string stdin_channel::ReadFd()
{
	return std::string();
}

int stdin_channel::WriteFd(std::string _output)
{
	return 0;
}

int stdin_channel::GetFd()
{
	return 0;
}

bool stdin_channel::Process(std::string _input)
{
	return false;
}

bool stdin_channel::SendOut(std::string _output)
{
	return false;
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
