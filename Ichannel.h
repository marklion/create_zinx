#pragma once
#include <string>
#include "AZinxHandler.h"

class Ichannel:public AZinxHandler
{
	bool bDelFlag = false;
public:
	virtual std::string ReadFd() = 0;
	virtual int WriteFd(std::string _output) = 0;
	virtual int GetFd() = 0;
	bool SendOut(std::string _output);
	Ichannel();
	virtual ~Ichannel();
	void SetDelFlag() {
		bDelFlag = true;
	}
	bool NeedDel() {
		return bDelFlag;
	}

	/*待输出数据缓冲*/
	std::string output_buff;

	// 通过 AZinxHandler 继承
	virtual message * internelHandle(message & _input) override;
	virtual AZinxHandler * GetNext(message & _next) override;

	/*获取    处理输入数据对象*/
	virtual AZinxHandler *GetNextInputStage(message & _next) = 0;
};

