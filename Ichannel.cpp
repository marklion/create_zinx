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

message * Ichannel::internelHandle(message & _input)
{
	/*根据参数决定读数据还是写数据*/
	IO_direction &dic = dynamic_cast<IO_direction &>(_input);

	if (dic.m_dic == IO_direction::IN)
	{
		/*读数据*/
		auto read_content = ReadFd();
		auto pret = new ByteMsg(dic, read_content);
		return pret;
	}
	else
	{
		/*写数据*/
		int write_len = WriteFd(output_buff);
		/*若已发数据小于待发数据---》更新缓存*/
		if (write_len != output_buff.size())
		{
			/*弹出缓存中已发送的数据*/
			output_buff.erase(output_buff.begin(), output_buff.begin() + write_len);
		}
		else
		{
			/*若全部发送完成,去掉对EPOLLOUT事件的监听,清掉缓存*/
			kernel::GetInstance().ChannelOutDel(this);
			output_buff.clear();
		}
	}

	/*写操作执行完了，没有下一个环节需要处理的消息*/
	return nullptr;
}

AZinxHandler * Ichannel::GetNext(message & _next)
{
	IO_direction &dic = dynamic_cast<IO_direction &>(_next);
	/*若消息方向是输入，则根据实际情况返回下一个处理环节*/
	if (dic.m_dic == IO_direction::IN)
	{
		return GetNextInputStage(_next);
	}
	/*否则---》返回空*/
	return nullptr;
}
