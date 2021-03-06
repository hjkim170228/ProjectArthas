/************************************************************************/
/*
CLASS			: EquipmentMelee
Author			: 김성연
역할				: Melee 장비 클래스
최종 수정일자		: 2014-11-28
최종 수정자		:
최종 수정사유		:
Comment			:
/************************************************************************/

#pragma once
#include "Util.h"
#include "EquipmentAbstract.h"

struct MeleeInfo : public EquipmentInfo
{
	virtual MeleeInfo* clone();
	MeleeInfo();
	MeleeInfo(const MeleeInfo& other);

	float	  m_AttackDamage = 0.f;
	float	  m_AttackSpeed = 0.f;
};

class EquipmentMelee : public EquipmentAbstract
{
public:
	OVERRIDE bool				init();
	OVERRIDE void				update(float dTime);
	OVERRIDE void				enter();
	OVERRIDE void				exit();
	OVERRIDE bool				onContactBegin(cocos2d::PhysicsContact& contact);
	OVERRIDE void				onContactSeparate(cocos2d::PhysicsContact& contact);
	
	CREATE_FUNC(EquipmentMelee);
	
	void						setEquipment(MeleeInfo meleeInfo);
	void						setEquipment(EquipmentType equipmentType, MeleeList meleeType, int level, int kWatt,
											 int upgradePrice, bool isLock, float attackDamage, float attackSpeed,
											 SpriteType front = ST_START, SpriteType outLine = ST_START, 
											 SpriteType icon = ST_START);

	MeleeInfo					getEquipmentInfo();


private:
	MeleeInfo m_MeleeInfo;

};
