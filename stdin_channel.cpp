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
	//�����ݻ��Ե���׼���--->���ñ�׼���ͨ�������sendout����
	m_out->data_sendout(_input);
}

std::string stdin_channel::ReadFd()
{
	std::string ret;
	std::cin >> ret;
	return ret;
}
