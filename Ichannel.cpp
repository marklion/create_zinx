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
