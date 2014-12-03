/************************************************************************/
/*
CLASS			: EquipmentStatusLayer
Author			: �輺��
����				: Equipment�� status�� �����ִ� ���̾�
���� ��������		: 2014-12-01
���� ������		: �輺��
���� ��������		: �ű�
Comment			: 
*/
/************************************************************************/

#pragma once
#include "Util.h"
#include "AssemblyUILayer.h"
#include "EquipmentAbstract.h"


struct AllStatus
{
	//head
	float		m_CoolDown = 0.f;
	float		m_Mainmemory = 0.f;
	//engine
	float		m_ElectronicPower = 0.f;
	float       m_SteamEffectiveness = 0.f;
	//armor
	float       m_DefensivePower = 0.f;
	float		m_Resistance = 0.f;
	//steamcontainer
	float       m_MaxSteam = 0.f;
	float		m_AbsorbEffectiveness = 0.f;
	//melee
	float		m_MeleeDamage = 0.f;
	float       m_MeleeAttackSpeed = 0.f;
	//range
	float       m_RangeDamage = 0.f;
	float		m_RangeAttackSpeed = 0.f;
	float		m_AttackRange = 0.f;
	//leg
	float		m_Speed = 0.f;
	float		m_Jump = 0.f;

};

enum AllstatusEnum
{
	STATUS_ENUM_START = 0,
	COOLDOWN = STATUS_ENUM_START,
	MAINMEMORY,
	POWER,
	STEAM_EFF,
	ARMOR,
	RESISTANCE,
	MELEE_DAMAGE,
	MELEE_ATTACK_SPEED,
	RANGE_DAMAGE,
	RANGE_ATTACK_SPEED,
	RANGE_ATTACK_RANGE,
	MAX_STEAM,
	ABSORB_EFF,
	SPEED,
	JUMP,
	STATUS_ENUM_END,

};

class ButtonLayer;

class EquipmentStatusLayer : public AssemblyUILayer
{
public:

	enum BasicStatus
	{
		BASISSTAUTSSTART = -1,
		LEVEL = 0,
		KWATT,
		UPGRADEPRICE,
		BASISSTATUSEND,
	};

	/*struct CurEquipmentesInfo
	{
	HeadInfo		   m_HeadInfo;
	LegInfo			   m_LegInfo;
	ArmorInfo		   m_ArmorInfo;
	SteamContainerInfo m_SteamContainerInfo;
	MeleeInfo		   m_MeleeInfo;
	RangeInfo		   m_RangeInfo;
	EngineInfo		   m_EngineInfo;
	};*/

	OVERRIDE bool			init();
	OVERRIDE void			update(float dTime);


	CREATE_FUNC(EquipmentStatusLayer);

	void					setButtons();
	void					setBasicLabels();
	void					setAllStatusDescLabels();
	void					setAllStatusValueLabels();
	void					setAllStatusChangeValueLabels();
	void					makeArrowLabels();

	//�� ��ġ
	void					setPosBasicDescLabel();
	void					setPosBasicValueLabel();
	void					setPosAllStatusDescLabel();
	void					setPosAllStatusValueLabel();
	void					setPosAllStatusChangeValueLabel();

	//update�� ���� ���׵�
	void					upgradeButtonClick();
	
	void					clickedSomeEquipment();
	void					changeBasicItemValue(const EquipmentInfo* equipmentInfo);
	void					calculateChangeValue(const EquipmentInfo* equipInfo, EquipmentType equipType);
	void					updateChangeValueLabel(EquipmentType equipType);

	//��ư Ŭ���̺�Ʈ


	//�׿�
	void					setCurClickedItem(ClickedItem clickedItem);




private:
	AllStatus							m_CurBeInstalledEquipment;
	AllStatus							m_ChangeValue;

	EquipmentType						m_CurBeChosenEquipType = EMT_START;
	ButtonLayer*						m_UpgradeButton = nullptr;
	ButtonLayer*						m_EquipButton = nullptr;
	ClickedItem							m_PrevClickedItem;
	ClickedItem							m_CurClickedItem;
	AllStatus							m_CurAllStatus;

	std::string			   				m_StautsString[20];
	std::vector<cocos2d::Label*>		m_BasicStatusDesc;
	std::vector<cocos2d::Label*>		m_BasicStatusValue;
	std::vector<cocos2d::Label*>		m_AllStatusDesc;
	std::vector<cocos2d::Label*>		m_AllStatusValue;
	std::vector<cocos2d::Label*>		m_ArrowLabels;	

	std::map<AllstatusEnum, cocos2d::Label*> m_AllStatusChangeValue;

};