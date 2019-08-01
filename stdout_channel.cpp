#include "stdout_channel.h"



stdout_channel::stdout_channel()
{
}


stdout_channel::~stdout_channel()
{
}

std::string stdout_channel::ReadFd()
{
	return std::string();
}

int stdout_channel::WriteFd(std::string _output)
{
	return 0;
}

int stdout_channel::GetFd()
{
	return 0;
}

bool stdout_channel::Process(std::string _input)
{
	return false;
}

bool stdout_channel::SendOut(std::string _output)
{
	return false;
}
