#pragma once
#include <string>

class stdin_channel
{
public:
	stdin_channel();
	virtual ~stdin_channel();
	/*����Ҫ��ְ��---������������---�����ض���������*/
	std::string ReadFd();

	/*��ȡ��Ӧ��fd*/
	int GetFd();
};

