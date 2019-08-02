#pragma once
#include <string>

class Ichannel
{
	bool bDelFlag = false;
public:
	virtual std::string ReadFd() = 0;
	virtual int WriteFd(std::string _output) = 0;
	virtual int GetFd() = 0;
	virtual bool Process(std::string _input) = 0;
	bool SendOut(std::string _output);
	Ichannel();
	virtual ~Ichannel();
	void SetDelFlag() {
		bDelFlag = true;
	}
	bool NeedDel() {
		return bDelFlag;
	}

	/*´ýÊä³öÊý¾Ý»º³å*/
	std::string output_buff;
};

