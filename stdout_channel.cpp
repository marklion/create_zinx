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
	/*返回空字符串*/
	return std::string();
}

int stdout_channel::WriteFd(std::string _output)
{
	/*返回值==实际写出的字节数*/
	cout << _output << endl;
	return _output.size();
}

int stdout_channel::GetFd()
{
	return 1;
}

AZinxHandler * stdout_channel::GetNextInputStage(message & _next)
{
	/*通道用来输出，所以必然没有处理输入的下一个环节*/
	return nullptr;
}

