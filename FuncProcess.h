#pragma once
#include <string>
#include "AZinxHandler.h"

class Ichannel;
class FuncProcess:public AZinxHandler
{
public:
	FuncProcess();
	virtual ~FuncProcess();

	/*�洢��������ͨ������ָ��*/
	Ichannel *m_output_channel = NULL;

	/*���ݴ�����*/
	bool DataProc(std::string _data);

	// ͨ�� AZinxHandler �̳�
	virtual message * internelHandle(message & _input) override;
	virtual AZinxHandler * GetNext(message & _next) override;
};

