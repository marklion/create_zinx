#include "Ichannel.h"
#include "kernel.h"


bool Ichannel::SendOut(std::string _output)
{
	/*���ϴ�������û���꣬����������---��������wirte-->ֱ�ӻ��汾�δ���������*/
	if (output_buff.size() > 0)
	{
		output_buff.append(_output);
		return true;
	}

	/*����д����������*/
	int write_len = WriteFd(_output);
	if (write_len == _output.size())
	{
		return true;
	}
	/*ûд��--������ʣ������--������epollout�¼�����*/
	output_buff.append(_output.substr(write_len, _output.size() - write_len));
	//����epollout�¼�����--����ȡkernel����
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
	/*���ݲ������������ݻ���д����*/
	IO_direction &dic = dynamic_cast<IO_direction &>(_input);

	if (dic.m_dic == IO_direction::IN)
	{
		/*������*/
		auto read_content = ReadFd();
		auto pret = new ByteMsg(dic, read_content);
		return pret;
	}
	else
	{
		/*д����*/
		int write_len = WriteFd(output_buff);
		/*���ѷ�����С�ڴ�������---�����»���*/
		if (write_len != output_buff.size())
		{
			/*�����������ѷ��͵�����*/
			output_buff.erase(output_buff.begin(), output_buff.begin() + write_len);
		}
		else
		{
			/*��ȫ���������,ȥ����EPOLLOUT�¼��ļ���,�������*/
			kernel::GetInstance().ChannelOutDel(this);
			output_buff.clear();
		}
	}

	/*д����ִ�����ˣ�û����һ��������Ҫ�������Ϣ*/
	return nullptr;
}

AZinxHandler * Ichannel::GetNext(message & _next)
{
	IO_direction &dic = dynamic_cast<IO_direction &>(_next);
	/*����Ϣ���������룬�����ʵ�����������һ��������*/
	if (dic.m_dic == IO_direction::IN)
	{
		return GetNextInputStage(_next);
	}
	/*����---�����ؿ�*/
	return nullptr;
}
