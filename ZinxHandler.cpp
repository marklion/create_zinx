#include "ZinxHandler.h"



ZinxHandler::ZinxHandler()
{
}


ZinxHandler::~ZinxHandler()
{
}

void ZinxHandler::handle(ZinxMsg * _inputMsg)
{
	/*1.��ǰ���ڴ���*/
	auto pNextMsg = internel_handle(_inputMsg);
	if (nullptr != pNextMsg)
	{
		/*2.��ȡ��һ������*/
		ZinxHandler *pNextHanler = GetNext(pNextMsg);
		if (nullptr != pNextHanler)
		{
			/*3.��һ�����ڴ���*/
			pNextHanler->handle(pNextMsg);
		}
		delete pNextMsg;
	}

}
