#include "stdout_channel.h"
#include <iostream>

using namespace std;


stdout_channel::stdout_channel()
{
}


stdout_channel::~stdout_channel()
{
}

std::string stdout_channel::ReadFd()
{
	/*���ؿ��ַ���*/
	return std::string();
}

int stdout_channel::WriteFd(std::string _output)
{
	/*����ֵ==ʵ��д�����ֽ���*/
	cout << _output << endl;
	return _output.size();
}

int stdout_channel::GetFd()
{
	return 1;
}

AZinxHandler * stdout_channel::GetNextInputStage(message & _next)
{
	/*ͨ��������������Ա�Ȼû�д����������һ������*/
	return nullptr;
}

