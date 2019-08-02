#include "AZinxHandler.h"



AZinxHandler::AZinxHandler()
{
}


AZinxHandler::~AZinxHandler()
{
}

void AZinxHandler::Handle(message & _input)
{
	/*�ڲ�����*/
	auto next = internelHandle(_input);
	/*�������������*/
	if (nullptr != next)
	{
		/*��ȡ��һ������*/
		auto pnext_handler = GetNext(*next);
		if (pnext_handler != nullptr)
		{
			/*�����ݽ�����һ�����ڴ���*/
			pnext_handler->Handle(*next);
		}
		delete next;
	}
}
