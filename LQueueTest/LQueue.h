/*
* Copyright (c) 2011,�����׸��Զ�����Ϣ�������޹�˾
* ��������Ȩ��
* �ļ����� :LHTRPlus
* ժ    Ҫ :�¼���������+��ʱִ���¼�
*
* ��ǰ�汾 : 1.0
* ��    �� : ����
* ������� : 2021-11-12
*
* ȡ���汾 :
* ԭ �� �� :
* ������� :
*/
#pragma once

#include<windows.h>
#include <process.h>
#include <iostream>
#include <vector>
using namespace std;

class xAnwser {

public:

	template<class F>
	void xSetFun(F vf)
	{
		xPtr = vf;
	}
	template<class F>
	F xGetFun()
	{
		return (F)xPtr;
	}
	int xID;//�������
	int xTimeOut;//��ʱʱ��
	int xTimeCur;//��ǰ��ʱ
	int xFlag;//1:��ʱ;0:δ��ʱ
	void* xPtr;
};

class xQueue {

public:
	xQueue();
	void setQueueName(string);
	string getQueueName(string);
	int getQueueSize();
	bool push(xAnwser);
	bool pop();
	void removeAt(xAnwser _t);
	vector<xAnwser> monitor();
	bool Start(void(*_qMonitor)(void* p));

private:
	CRITICAL_SECTION _qcs;
	string name;
	xAnwser* ptrData;
	int len;
	int _len = 10;
	int _capsize = 5;
	HANDLE _qh;
};
/* 
*_qMonitorʾ��
*
void _qMonitor(void* p)
{
	xQueue xq = *(xQueue*)p;
	while (1)
	{
		vector<xAnwser> xa = xq.monitor();
		if (xa.size() > 0)
		{
			for (int i = 0; i < xa.size(); i++)
			{
				if (xa[i].xID == 1)
				{
				a = xa[i].xGetFun<FADD>()(2, 3);
				printf("a=%d\n", a);
				}
				else if (xa[i].xID == 2)
				{
				xa[i].xGetFun<Print>()("hello Boy");
				}
				else if (xa[i].xID == 3)
				{
				xa[i].xGetFun<Print>()("hello Girl");
				}
			}
		}
	Sleep(500);
	}
}
*/