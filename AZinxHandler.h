#pragma once
#include <string>
/*��Ϣ�ࣨ���ݣ�*/
class message {
public:
	virtual ~message() {}
};

/*����IO������----->��ͨ���ദ��*/
class IO_direction :public message {
public:
	enum DIC {
		IN, OUT
	} m_dic;
	IO_direction(DIC _dic):m_dic(_dic) {}
};

/*�����ֽ���Ϣ��---�������ܴ����ദ��-----����ͨ�������*/
class ByteMsg :public IO_direction {
public:
	ByteMsg(IO_direction &super_dic):IO_direction(super_dic.m_dic) {}
	ByteMsg(IO_direction &super_dic, std::string _data) :IO_direction(super_dic.m_dic),data(_data) {}
	std::string data;
};

/*�������ࣨ���ڣ�*/
class AZinxHandler
{
public:
	AZinxHandler();
	virtual ~AZinxHandler();
	/*�ڲ������� �������������ݣ�����ֵ���������*/
	virtual message *internelHandle(message &_input) = 0;

	/*��ȡ��һ������, �����Ǳ����ڵ������Ϊ�ж����ݣ�����ֵ�ǻ���*/
	virtual AZinxHandler *GetNext(message &_next) = 0;
	/*������� �� �����Ǵ���������*/
	void Handle(message &_input);
};

