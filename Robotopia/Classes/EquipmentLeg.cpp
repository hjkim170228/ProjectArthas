#include "pch.h"
#include "EquipmentLeg.h"
#include "IconLayer.h"

bool EquipmentLeg::init()
{
	if (!EquipmentAbstract::init())
	{
		return false;
	}
	m_Icon = IconLayer::create();
	this->addChild(m_Icon);
	return true;
}

void EquipmentLeg::update(float dTime)
{
	if (m_Icon != nullptr)
	{
		m_Icon->update(dTime);
	}
}

void EquipmentLeg::enter()
{
}

void EquipmentLeg::exit()
{
}

bool EquipmentLeg::onContactBegin(cocos2d::PhysicsContact& contact)
{
	return true;
}

void EquipmentLeg::onContactSeparate(cocos2d::PhysicsContact& contact)
{
}

void EquipmentLeg::setEquipment(EquipmentType equipmentType, LegList legType, int level, int kWatt,
								int upgradePrice, bool isLock, float moveSpeed, float jumpPower,
								SpriteType front, SpriteType outLine, SpriteType icon)
{
	m_LegInfo.m_EquipmentType = equipmentType;
	m_LegInfo.m_Type = legType;
	m_LegInfo.m_Level = level;
	m_LegInfo.m_KWatt = kWatt;
	m_LegInfo.m_UpgradePrice = upgradePrice;
	m_LegInfo.m_IsLock = isLock;
	m_LegInfo.m_MoveSpeed = moveSpeed;
	m_LegInfo.m_jumpPower = jumpPower;
	m_LegInfo.m_Front = front;
	m_LegInfo.m_OutLine = outLine;
	m_LegInfo.m_Icon = icon;

	if (m_LegInfo.m_IsLock)
	{
		m_Icon->changeIconState(ICON_LOCKED);
	}
	else
	{
		m_Icon->changeIconState(ICON_DEFAULT);
	}
}

void EquipmentLeg::setEquipment(LegInfo legInfo)
{
	setEquipment(legInfo.m_EquipmentType, static_cast<LegList>(legInfo.m_Type),
				 legInfo.m_Level, legInfo.m_KWatt,
				 legInfo.m_UpgradePrice, legInfo.m_IsLock,
				 legInfo.m_MoveSpeed, legInfo.m_jumpPower,
				 legInfo.m_Front, legInfo.m_OutLine, legInfo.m_Icon);
}

LegInfo EquipmentLeg::getEquipmentInfo()
{
	return m_LegInfo;
}
