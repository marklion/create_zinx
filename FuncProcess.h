#pragma once
#include <string>

class Ichannel;
class FuncProcess
{
public:
	FuncProcess();
	virtual ~FuncProcess();

	/*�洢��������ͨ������ָ��*/
	Ichannel *m_output_channel = NULL;

	/*���ݴ�����*/
	bool DataProc(std::string _data);
};

