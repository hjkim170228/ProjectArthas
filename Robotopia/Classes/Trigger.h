/************************************************************************/
/*
CLASS			: Trigger
Author			: �迬��
����				: ���º��� Ʈ���� �߻�Ŭ����
���� ��������	: 2014-10-29
���� ������		:
���� ��������	:
Comment			:
*/
/************************************************************************/
#pragma once
#include "Util.h"

BEGIN_NS_AT

class Trigger
{
public:
	int getType();
	virtual bool operator ==( Trigger& trigger ) = 0;
protected:
	int m_Type;
};

END_NS_AT