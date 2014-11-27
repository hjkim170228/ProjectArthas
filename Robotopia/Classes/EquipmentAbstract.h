/************************************************************************/
/*
CLASS			: EquipmentAbstract
Author			: �輺��
����				: ��� ����� �������� �߻� Ŭ���� 
���� ��������		: 2014-11-27
���� ������		:
���� ��������		:
Comment			: 
/************************************************************************/

#pragma once

#include "ItemAbstract.h"

class EquipmentAbstract : public ItemAbstract
{
public:
	OVERRIDE bool				init();
	OVERRIDE void				update(float dTime);
	OVERRIDE void				enter();
	OVERRIDE void				exit();
	OVERRIDE bool				onContactBegin(cocos2d::PhysicsContact& contact);
	OVERRIDE void				onContactSeparate(cocos2d::PhysicsContact& contact);
	ABSTRACT void				initEquipment();

	struct EquipmentInfo
	{
		//EquipmentType m_EquipmentType= EMT_NONE;
		int  m_Level = 0;
		int  m_KWatt = 0;
		bool m_IsLock = false;
		int  m_UpgradePrice = 0;
	};


protected:

	cocos2d::Sprite* m_Front = nullptr;
	cocos2d::Sprite* m_FrontOutLine = nullptr;
	cocos2d::Sprite* m_InGameSprite = nullptr;
	cocos2d::Sprite* m_Icon = nullptr;

};