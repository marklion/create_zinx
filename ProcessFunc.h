#pragma once
#include <string>
#include "Ichannel.h"

class ProcessFunc
{
public:
	Ichannel *m_out = NULL;
	ProcessFunc();
	virtual ~ProcessFunc();
	void DataProcess(std::string _input);
	void UpperOut(std::string _input);
	void OrigOut(std::string _input);
};

