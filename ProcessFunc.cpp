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
	//参数中第一个字母是小写字母则转大写输出
	if (_input[0] <= 'z' && _input[0] >= 'a')
	{
		UpperOut(_input);
	}
	else
	{
		//否则原样输出
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
