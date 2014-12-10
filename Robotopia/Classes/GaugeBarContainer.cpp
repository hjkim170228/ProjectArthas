#include "pch.h"
#include "GaugeBarContainer.h"
#include "GameManager.h"
#include "ResourceManager.h"

bool GaugeBarContainer::init()
{
	if(!SpriteComponent::init())
	{
		return false;
	}
	return true;
}

void GaugeBarContainer::update(float dTime)
{

}

void GaugeBarContainer::initBarContainer(BaseComponent* target, SpriteType barContainer, SpriteType bar,
										 cocos2d::Point pos)
{
	initSprite(barContainer, target, pos);
	m_Bar = GET_RESOURCE_MANAGER()->createSprite(bar);
	addChild(m_Bar);
	m_Bar->setAnchorPoint(cocos2d::Point::ZERO);
	m_Bar->setScaleX(m_CurrentPercent);
}

void GaugeBarContainer::setBarPercent(float percent)
{
	m_CurrentPercent = percent;
	m_Bar->setScaleX(m_CurrentPercent);
}



