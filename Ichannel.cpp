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
