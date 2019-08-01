#pragma once
#include <string>

class stdin_channel
{
public:
	stdin_channel();
	virtual ~stdin_channel();
	/*最重要的职责---》读键盘输入---》返回读到的内容*/
	std::string ReadFd();

	/*获取对应的fd*/
	int GetFd();
};

