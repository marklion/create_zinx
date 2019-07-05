#include "Ichannel.h"
#include "zinxkernel.h"


Ichannel::Ichannel()
{
}


Ichannel::~Ichannel()
{
}

void Ichannel::flushout()
{
	WriteFd(m_buffer);
	m_buffer.clear();
}

//�������--����������¼������
void Ichannel::data_sendout(std::string _output)
{
	m_buffer.append(_output.begin(), _output.end());
	//�޸�epoll��������--�����out����ļ���
	zinxkernel::GetInstance().ModChannel_AddOut(this);
}

ZinxMsg * Ichannel::internel_handle(ZinxMsg * _inputMsg)
{
	//�ж�������Ϣ������ɶ
	sysIODicMsg *pmsg = dynamic_cast<sysIODicMsg *>(_inputMsg);
	if (NULL != pmsg)
	{
		if (sysIODicMsg::IO_IN == pmsg->m_DIC)
		{
			auto input_data = ReadFd();
			return new ByteMsg(input_data, *pmsg);
		}
		else
		{
			//����ҵ��������
			auto pout = dynamic_cast<ByteMsg *>(_inputMsg);
			if (NULL != pout)
			{
				data_sendout(pout->content);
			}
		}
	}

	return nullptr;
}

ZinxHandler * Ichannel::GetNext(ZinxMsg * _next_input)
{
	auto pbyte = dynamic_cast<ByteMsg *>(_next_input);
	if (NULL!= pbyte)
	{
		return GetInputNextStage(pbyte);
	}
	return nullptr;
}
