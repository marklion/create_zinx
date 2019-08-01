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
	std::string ret;
	std::cin >> ret;
	return ret;
}

int stdin_channel::GetFd()
{
	return 0;
}
