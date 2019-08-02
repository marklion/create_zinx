#include "FuncProcess.h"
#include <algorithm>
#include "Ichannel.h"
using namespace std;

FuncProcess::FuncProcess()
{
}


FuncProcess::~FuncProcess()
{
}

bool FuncProcess::DataProc(std::string _data)
{
	/*首字母大写则全部大写输出*/
	if (_data[0] <= 'Z' && _data[0] >= 'A')
	{
		transform(_data.begin(), _data.end(), _data.begin(), ::toupper);
	}
	
	return m_output_channel->SendOut(_data);
}
