#include "Ichannel.h"
#include "kernel.h"


bool Ichannel::SendOut(std::string _output)
{
	/*若上次有数据没发完，缓存有数据---》不调用wirte-->直接缓存本次待发送数据*/
	if (output_buff.size() > 0)
	{
		output_buff.append(_output);
		return true;
	}

	/*试着写出参数内容*/
	int write_len = WriteFd(_output);
	if (write_len == _output.size())
	{
		return true;
	}
	/*没写完--》缓存剩余数据--》增加epollout事件监听*/
	output_buff.append(_output.substr(write_len, _output.size() - write_len));
	//增加epollout事件监听--》获取kernel对象
	kernel::GetInstance().ChannelOutAdd(this);
	return true;
}

Ichannel::Ichannel()
{
}


Ichannel::~Ichannel()
{
}
