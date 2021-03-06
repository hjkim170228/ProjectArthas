#include "pch.h"
#include "EquipmentEngine.h"
#include "IconLayer.h"

bool EquipmentEngine::init()
{
	if (!EquipmentAbstract::init())
	{
		return false;
	}
	m_Icon = IconLayer::create();
	this->addChild(m_Icon);
	return true;
}

void EquipmentEngine::update(float dTime)
{
	if (m_Icon != nullptr)
	{
		m_Icon->update(dTime);
	}
}

void EquipmentEngine::enter()
{
}

 void EquipmentEngine::exit()
{
}

bool EquipmentEngine::onContactBegin(cocos2d::PhysicsContact& contact)
{
	return true;
}

void EquipmentEngine::onContactSeparate(cocos2d::PhysicsContact& contact)
{
}

void EquipmentEngine::setEquipment(EngineInfo engineInfo)
{
	setEquipment(engineInfo.m_EquipmentType, static_cast<EngineList>(engineInfo.m_Type),
				 engineInfo.m_Level, engineInfo.m_KWatt,
				 engineInfo.m_UpgradePrice, engineInfo.m_IsLock,
				 engineInfo.m_ElectronicPower, engineInfo.m_SteamEffectiveness,
				 engineInfo.m_FrontSprite, engineInfo.m_FrontOutline, engineInfo.m_IconSprite);
	setEquipmentSprite(engineInfo.m_FrontSprite, engineInfo.m_FrontOutline, engineInfo.m_IconSprite);
}

void EquipmentEngine::setEquipment(EquipmentType equipmentType, EngineList engineType, 
								   int level, int kWatt, int upgradePrice, bool isLock, 
								   float electronicPower, float steamEffectiveness, 
								   SpriteType front, SpriteType outLine, SpriteType icon)
{
	m_EngineInfo.m_EquipmentType = equipmentType;
	m_EngineInfo.m_Type = engineType;
	m_EngineInfo.m_Level = level;
	m_EngineInfo.m_KWatt = kWatt;
	m_EngineInfo.m_UpgradePrice = upgradePrice;
	m_EngineInfo.m_IsLock = isLock;
	m_EngineInfo.m_ElectronicPower = electronicPower;
	m_EngineInfo.m_SteamEffectiveness = steamEffectiveness;
	m_EngineInfo.m_FrontSprite = front;
	m_EngineInfo.m_FrontOutline = outLine;
	m_EngineInfo.m_IconSprite = icon;

	if (m_EngineInfo.m_IsLock)
	{
		m_Icon->changeIconState(ICON_LOCKED);
	}
	else
	{
		m_Icon->changeIconState(ICON_DEFAULT);
	}
}

EngineInfo EquipmentEngine::getEquipmentInfo()
{
	return m_EngineInfo;
}


EngineInfo* EngineInfo::clone()
{
	return new EngineInfo(*this);
}

EngineInfo::EngineInfo()
{

}

EngineInfo::EngineInfo(const EngineInfo& other) : EquipmentInfo(other)
{
	m_ElectronicPower = other.m_ElectronicPower;
	m_SteamEffectiveness = other.m_SteamEffectiveness;
}
