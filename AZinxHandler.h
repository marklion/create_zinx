#pragma once
#include <string>
/*消息类（数据）*/
class message {
public:
	virtual ~message() {}
};

/*定义IO方向类----->被通道类处理*/
class IO_direction :public message {
public:
	enum DIC {
		IN, OUT
	} m_dic;
	IO_direction(DIC _dic):m_dic(_dic) {}
};

/*定义字节消息类---》被功能处理类处理-----》被通道类产生*/
class ByteMsg :public IO_direction {
public:
	ByteMsg(IO_direction &super_dic):IO_direction(super_dic.m_dic) {}
	ByteMsg(IO_direction &super_dic, std::string _data) :IO_direction(super_dic.m_dic),data(_data) {}
	std::string data;
};

/*处理者类（环节）*/
class AZinxHandler
{
public:
	AZinxHandler();
	virtual ~AZinxHandler();
	/*内部处理函数 参数是输入数据，返回值是输出数据*/
	virtual message *internelHandle(message &_input) = 0;

	/*获取下一个环节, 参数是本环节的输出作为判断依据，返回值是环节*/
	virtual AZinxHandler *GetNext(message &_next) = 0;
	/*环节入口 ， 参数是待处理数据*/
	void Handle(message &_input);
};

