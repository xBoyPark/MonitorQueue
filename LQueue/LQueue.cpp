#include "stdafx.h"
#include "LQueue.h"

xQueue::xQueue()
{
	ptrData = NULL;
	ptrData = (xAnwser*)malloc(_len * sizeof(xAnwser));
	len = 0;
	InitializeCriticalSection(&_qcs);
}

void xQueue::setQueueName(string _name)
{
	name = _name;
}

string xQueue::getQueueName(string)
{
	return name;
}

int xQueue::getQueueSize()
{
	return len;
}

bool xQueue::push(xAnwser _t)
{
	if (_t.xID != 0)
	{
		EnterCriticalSection(&_qcs);
		if (len >= _len)
		{
			ptrData = (xAnwser*)realloc(ptrData, (_len + _capsize) * sizeof(xAnwser));
			if (ptrData == NULL)
			{
				printf("内存分配请求失败\n");
				LeaveCriticalSection(&_qcs);
				return false;
			}
			else
			{
				_len = _len + _capsize;
				ptrData[len] = _t;
				len++;
				LeaveCriticalSection(&_qcs);
				return true;
			}
		}
		else
		{

			ptrData[len] = _t;
			len++;
			LeaveCriticalSection(&_qcs);
			return true;
		}
	}
	printf("元素不允许为空\n");
	return false;

}

bool xQueue::pop()
{
	if (len <= 0)
	{
		return false;
	}
	else
	{
		xAnwser* _xt = &(ptrData[0]);
		ptrData = &(ptrData[1]);
		free(_xt);
		len--;
		_len--;
		return true;
	}
}

void xQueue::removeAt(xAnwser _t)
{
	EnterCriticalSection(&_qcs);
	if (_t.xID != 0 && len>0)
	{
		for (int i = 0; i < len; i++)
		{
			if (ptrData[i].xID == _t.xID)
			{
				MoveMemory(&ptrData[i], &ptrData[i + 1], (_len - i - 1) * sizeof(xAnwser));

				len--;
				_len--;
				if (len >= _len)
					ptrData = (xAnwser*)realloc(ptrData, (_len) * sizeof(xAnwser));

				break;
			}
		}

	}
	LeaveCriticalSection(&_qcs);

}

vector<xAnwser> xQueue::monitor()
{
	vector<xAnwser> rs;
	int mlen = this->len;
	for (int i = 0; i < mlen; i++)
	{
		if (this->ptrData[i].xFlag == 1)
		{
			rs.push_back(this->ptrData[i]);
		}
		else
		{
			this->ptrData[i].xTimeCur += 1000;
			if (this->ptrData[i].xTimeCur - this->ptrData[i].xTimeOut >= 0)
			{
				this->ptrData[i].xFlag = 1;
			}
		}
	}
	for (int i = 0; i < rs.size(); i++)
	{
		this->removeAt(rs[i]);
	}
	return rs;
}

bool xQueue::Start(void(*_qMonitor)(void* p))
{
	_qh = (HANDLE)_beginthread(_qMonitor, 0, this);
	if (_qh == INVALID_HANDLE_VALUE)
	{
		return false;
	}
	else
	{
		return true;
	}
}
