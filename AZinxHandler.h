#pragma once

/*消息类（数据）*/
class message {
public:
	virtual ~message() {}
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

