#include "ProcessFunc.h"
#include <algorithm>

using namespace std;

ProcessFunc::ProcessFunc()
{
}


ProcessFunc::~ProcessFunc()
{
}

void ProcessFunc::DataProcess(std::string _input)
{
	//�����е�һ����ĸ��Сд��ĸ��ת��д���
	if (_input[0] <= 'z' && _input[0] >= 'a')
	{
		UpperOut(_input);
	}
	else
	{
		//����ԭ�����
		OrigOut(_input);
	}

}

void ProcessFunc::UpperOut(std::string _input)
{
	transform(_input.begin(), _input.end(), _input.begin(), ::toupper);
	m_out->data_sendout(_input);
}

void ProcessFunc::OrigOut(std::string _input)
{
	m_out->data_sendout(_input);
}
