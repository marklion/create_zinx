#include "AZinxHandler.h"



AZinxHandler::AZinxHandler()
{
}


AZinxHandler::~AZinxHandler()
{
}

void AZinxHandler::Handle(message & _input)
{
	/*内部处理*/
	auto next = internelHandle(_input);
	/*产生了输出数据*/
	if (nullptr != next)
	{
		/*获取下一个环节*/
		auto pnext_handler = GetNext(*next);
		if (pnext_handler != nullptr)
		{
			/*将数据交给下一个环节处理*/
			pnext_handler->Handle(*next);
		}
		delete next;
	}
}
