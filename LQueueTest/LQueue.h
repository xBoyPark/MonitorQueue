/*
* Copyright (c) 2011,北京首钢自动化信息技术有限公司
* 保留所有权利
* 文件名称 :LHTRPlus
* 摘    要 :事件监听队列+超时执行事件
*
* 当前版本 : 1.0
* 作    者 : 刘松
* 完成日期 : 2021-11-12
*
* 取代版本 :
* 原 作 者 :
* 完成日期 :
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
	int xID;//监听编号
	int xTimeOut;//超时时间
	int xTimeCur;//当前计时
	int xFlag;//1:超时;0:未超时
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
*_qMonitor示例
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