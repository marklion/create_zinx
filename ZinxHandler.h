#pragma once

class ZinxMsg {
public:
	ZinxMsg() {}
	virtual ~ZinxMsg() {}
};

class ZinxHandler
{
public:
	ZinxHandler();
	virtual ~ZinxHandler();
	void handle(ZinxMsg *_inputMsg);
	virtual ZinxMsg *internel_handle(ZinxMsg *_inputMsg) = 0;
	//_next_inputӦ����internel_handle�ķ���ֵ
	virtual ZinxHandler *GetNext(ZinxMsg *_next_input) = 0;
};

