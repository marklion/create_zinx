#pragma once

/*��Ϣ�ࣨ���ݣ�*/
class message {
public:
	virtual ~message() {}
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

