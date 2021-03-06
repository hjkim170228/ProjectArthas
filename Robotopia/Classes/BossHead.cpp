#include "pch.h"
#include "BossHead.h"
#include "GameManager.h"
#include "StageManager.h"
#include "ComponentManager.h"
#include "EffectManager.h"
#include "SoundManager.h"
#include "MissileManager.h"
#include "AnimationComponent.h"
#include "AimingMissile.h"
#include "Corpse.h"
#include "Effect.h"
#include "Lever.h"

bool BossHead::init()
{
	if(!BaseComponent::init())
	{
		return false;
	}
	auto meterial = cocos2d::PhysicsMaterial(0, 0, 0);
	m_Body = cocos2d::PhysicsBody::createCircle(HEAD_RADIUS, meterial);
	m_Body->setContactTestBitmask(PHYC_BLOCK | PHYC_PLAYER | PHYC_MISSILE);
	m_Body->setCategoryBitmask(PHYC_MONSTER);
	m_Body->setCollisionBitmask(PHYC_BLOCK | PHYC_FLOOR | PHYC_MISSILE);
	m_Body->setMass(10);
	m_Body->setRotationEnable(false);
	m_Body->setVelocityLimit(1000);
	m_Body->setVelocity(cocos2d::Vec2(0, 0));
	m_Body->setDynamic(false);
	m_Body->retain();
	setPhysicsBody(m_Body);

	initFSM(1);
	m_States[0] = STAT_IDLE;

	m_FSMs[0].resize(STAT_NUM);
	m_FSMs[0][STAT_IDLE] = nullptr;
	m_FSMs[0][STAT_MOVE] = FSM_CALLBACK(BossHead::move, this);
	m_FSMs[0][STAT_ATTACK] = FSM_CALLBACK(BossHead::attack, this);


	m_Transitions[0].resize(STAT_NUM);
	m_Transitions[0][STAT_IDLE] = FSM_CALLBACK(BossHead::idleTransition, this);
	m_Transitions[0][STAT_MOVE] = FSM_CALLBACK(BossHead::moveTransition, this);
	m_Transitions[0][STAT_ATTACK] = FSM_CALLBACK(BossHead::attackTransition, this);


	m_Renders[0].resize(STAT_NUM);
	m_Renders[0][STAT_IDLE] = NULL;
	m_Renders[0][STAT_MOVE] = NULL;
	m_Renders[0][STAT_ATTACK] = NULL;

	m_ModeRender[MODE_WIDTH] = GET_COMPONENT_MANAGER()->createComponent<SpriteComponent>();
	m_ModeRender[MODE_WIDTH]->initSprite(ST_BOSS_MODE_WIDTH, this);
	m_ModeRender[MODE_HEIGHT] = GET_COMPONENT_MANAGER()->createComponent<SpriteComponent>();
	m_ModeRender[MODE_HEIGHT]->initSprite(ST_BOSS_MODE_HEIGHT, this);
	m_ModeRender[MODE_MISSLE] = GET_COMPONENT_MANAGER()->createComponent<SpriteComponent>();
	m_ModeRender[MODE_MISSLE]->initSprite(ST_BOSS_MODE_MISSILE, this);
	for(unsigned int i = 0; i < MODE_NUM; i++)
	{
		addComponent(m_ModeRender[i]);
	}
	m_ModeRender[MODE_WIDTH]->enter();

	initInfo();

	return true;
}

void BossHead::initInfo()
{
	int level = GET_STAGE_MANAGER()->getStageNum();
	m_Type = OT_MONSTER_BOSS_FIRST;
	m_PreDelay = PRE_DELAY;
	m_PostDelay = POST_DELAY;
	m_Info.m_MaxHp = MAX_HP * level;
	m_Info.m_CurrentHp = MAX_HP * level;
	m_Info.m_AttackRange = ATTACK_RANGE;
	m_Info.m_MeleeDamage = BULLET_DAMAGE * level;
	m_Info.m_RangeDamage = LASER_DAMAGE * level;
	m_LastCorpseNum = MAX_CORPSE_NUM;
	m_HpUnit = m_Info.m_MaxHp / MAX_CORPSE_NUM;
}


void BossHead::update(float dTime)
{
	Creature::update(dTime);
	makeSmoke();
}

void BossHead::initPosition(cocos2d::Point position)
{
	setPosition(position);
	m_Origin = getParent()->getPosition();
	m_Distance = position.getDistance(m_Origin);
}

void BossHead::enter()
{
	resume();
}

void BossHead::exit()
{
	stopAllActions();
	for(int i = 0; i < m_FSMs.size(); ++i)
	{
		setState(i, STAT_IDLE);
	}
}

cocos2d::Point BossHead::getPosition()
{
	if(m_Origin == cocos2d::Point::ZERO)
	{
		m_Origin = getParent()->getPosition();
	}

	float rotation = getParent()->getRotation() - 90.f;
	int cicle = static_cast<int>( rotation  / 180.f );
	float radian = MATH_PIOVER2 * rotation / 90.f;
	cocos2d::Point pos;
	pos.x = m_Distance * cos(radian);
	pos.y = -m_Distance * sin(radian);
	return pos + m_Origin;
}

bool BossHead::onContactBegin(cocos2d::PhysicsContact& contact)
{
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();
	auto componentA = (BaseComponent*) bodyA->getNode();
	auto componentB = (BaseComponent*) bodyB->getNode();
	BaseComponent* enemyComponent;
	bool isComponentA = true;

	if(componentA->getType() == getType())
	{
		enemyComponent = componentB;
		isComponentA = true;
	}
	else
	{
		enemyComponent = componentA;
		isComponentA = false;
	}

	//�̻����̶� �浹 ó��
	if(enemyComponent->getPhysicsBody()->getCategoryBitmask() == PHYC_MISSILE)
	{
		Missile* missile = static_cast<Missile*>( enemyComponent );

		//����ź�� �� �� ����
		if(missile->getType() == OT_MISSILE_GRENADE)
		{
			return false;
		}

		//���� �� �� �� ����.
		if(!missile->isPlayerMissile())
		{
			return false;
		}

		float damage = missile->getDamage();

		m_Info.m_CurrentHp -= damage * 100.f / ( 100.f + m_Info.m_DefensivePower );

		if(m_Info.m_CurrentHp / m_HpUnit < m_LastCorpseNum)
		{
			makeCorpse();
		}

		//���
		if(m_Info.m_CurrentHp <= 0 && !m_IsDead)
		{
			m_IsDead = true;
		}
	}
	return true;
}

void BossHead::onContactSeparate(cocos2d::PhysicsContact& contact)
{

}

void BossHead::setAttacking(bool isAttack) 
{
	m_IsAttacking = isAttack;
}

void BossHead::setMoving(bool isMoving)
{
	m_IsMoving = isMoving;
}

const AllStatus& BossHead::getInfo() const
{
	return m_Info;
}

void BossHead::move(Creature* target, double dTime, int idx)
{
	timeval time = GET_GAME_MANAGER()->getTime();
	int checkValue = (time.tv_sec) % MODE_NUM;
	if(m_CurrentMode != checkValue)
	{
		m_ModeRender[m_CurrentMode]->exit();
		m_CurrentMode = checkValue;
		m_ModeRender[m_CurrentMode]->enter();
	}
}

void BossHead::enterMove()
{
	auto rotating = cocos2d::RotateBy::create( 1.f , 40 );
	auto repeat = cocos2d::RepeatForever::create( rotating );
	runAction( repeat );
	m_SoundId = GET_SOUND_MANAGER()->createSound(SoundManager::CLOCK_BOSS_MOVE, true);
}

void BossHead::exitMove()
{
	GET_SOUND_MANAGER()->pauseSound(m_SoundId);
	m_IsMoving = false;
	stopAllActions();
}

void BossHead::attack(Creature* target, double dTime, int idx)
{

}

void BossHead::enterAttack()
{
	auto delay = cocos2d::DelayTime::create( m_PreDelay );
	auto launch = cocos2d::CallFuncN::create( CC_CALLBACK_1( BossHead::launch , this ) );
	auto postDelay = cocos2d::DelayTime::create( m_PostDelay );
	auto seizeFire = cocos2d::CallFuncN::create( CC_CALLBACK_1( BossHead::seizeFire , this ) );
	auto sequence = cocos2d::Sequence::create( delay , launch , postDelay, seizeFire, nullptr);
	runAction( sequence );
}

void BossHead::exitAttack()
{

}

void BossHead::idleTransition(Creature* target, double dTime, int idx)
{
	if(m_IsMoving)
	{
		enterMove();
		setState(0, STAT_MOVE);
	}
}

void BossHead::moveTransition(Creature* target, double dTime, int idx)
{
	if(m_IsAttacking)
	{
		exitMove();
		enterAttack();
		setState(0, STAT_ATTACK);
	}
}

void BossHead::attackTransition(Creature* target, double dTime, int idx)
{
	if(!m_IsAttacking)
	{
		exitAttack();
		setState(0, STAT_IDLE);
	}
}

void BossHead::launch( cocos2d::Node* ref )
{
	cocos2d::Point globalPosition = getPosition() ;
	switch( m_CurrentMode )
	{
		case MODE_WIDTH:
			GET_MISSILE_MANAGER()->launchMissile( OT_MISSILE_LINEAR , globalPosition , DIR_UP,
												 cocos2d::Size::ZERO, m_Info.m_RangeDamage);
			break;
		case MODE_HEIGHT:
			GET_MISSILE_MANAGER()->launchMissile(OT_MISSILE_LINEAR, globalPosition, DIR_RIGHT,
												 cocos2d::Size::ZERO, m_Info.m_RangeDamage);
			break;
		case MODE_MISSLE:
			radiateAttack();
			break;
		default:
			break;
	}
}

void BossHead::seizeFire( cocos2d::Node* ref )
{
	m_IsAttacking = false;
}

void BossHead::makeRadiateMissile( cocos2d::Node* ref , float startDegree )
{
	for( int degree = startDegree; degree <= 360 + startDegree; degree += 30 )
	{
		auto missile = GET_MISSILE_MANAGER()->launchMissile(OT_MISSILE_AIMING, getPosition(), DIR_NONE,
															cocos2d::Size(HEAD_RADIUS, HEAD_RADIUS), m_Info.m_MeleeDamage);
		static_cast< AimingMissile* >( missile )->setPlayerMissile( false );
		static_cast< AimingMissile* >( missile )->setDegree( static_cast<float>(degree) );
		static_cast< AimingMissile* >( missile )->setMaxDistance( m_Info.m_AttackRange );
	}
}

void BossHead::radiateAttack()
{
	cocos2d::Vector<cocos2d::FiniteTimeAction*> attackQueue;
	for( int i = 0; i < 10; ++i )
	{
		auto radiate = cocos2d::CallFuncN::create( CC_CALLBACK_1( BossHead::makeRadiateMissile , this , i * 10) );
		auto delay = cocos2d::DelayTime::create( 0.2f );
		attackQueue.pushBack( radiate );
		attackQueue.pushBack( delay );
	}
	auto sequence = cocos2d::Sequence::create( attackQueue );
	runAction( sequence );
}

void BossHead::dead()
{
	GET_SOUND_MANAGER()->createSound(SoundManager::PLAYER_DEAD, true);
	auto effect = GET_EFFECT_MANAGER()->createEffect(ET_EXPLOSION, getPosition());
	effect->setScale(BOSS_SCALE);
	effect->enter();

	auto lever = GET_COMPONENT_MANAGER()->createComponent<Lever>();
	GET_STAGE_MANAGER()->addObject(lever, GET_STAGE_MANAGER()->getRoomNum(), m_Origin, LAND_OBJECT);

	stopAllActions();
	setEnabled(false);
	setVisible(false);
	
	auto delay = cocos2d::DelayTime::create(10.f);
	auto callBack = cocos2d::CallFuncN::create(CC_CALLBACK_1(BossHead::endBoss, this));
	auto sequence = cocos2d::Sequence::create(delay, callBack, nullptr);
	runAction(sequence);
}

void BossHead::endBoss(cocos2d::Node* ref)
{
// 	auto startButton = cocos2d::MenuItemFont::create("Restart", CC_CALLBACK_1(BossHead::restart, this));
// 	auto endButton = cocos2d::MenuItemFont::create("End", CC_CALLBACK_1(BossHead::quit, this));
// 	auto menu = cocos2d::Menu::create(startButton, endButton, NULL);
// 	auto gameScene = GET_STAGE_MANAGER()->getGameScene();
// 	menu->alignItemsVertically();
// 	gameScene->addChild(menu);
}


void BossHead::makeCorpse()
{
	int vX = rand() % CORPSE_VELOCITY - CORPSE_VELOCITY/2;
	int vY = rand() % CORPSE_VELOCITY - CORPSE_VELOCITY/2;
	auto corpse = GET_COMPONENT_MANAGER()->createComponent<Corpse>();
	int roomNum = GET_STAGE_MANAGER()->getRoomNum();
	GET_STAGE_MANAGER()->addObject(corpse, roomNum, getPosition(), RoomZOrder::GAME_OBJECT);
	corpse->getPhysicsBody()->setVelocity(cocos2d::Vec2(vX, vY));
	makeSmoke();
	--m_LastCorpseNum;
}

void BossHead::makeSmoke()
{
	int posX = 0;
	int posY = 0;
	cocos2d::Point pos;
	cocos2d::Point curPos = getPosition();
	int iterNum = (MAX_CORPSE_NUM - m_LastCorpseNum) / 2;
	for(int i = 0; i < iterNum; ++i)
	{
		posX = rand() % HEAD_RADIUS - HEAD_RADIUS / 2;
		posY = rand() % HEAD_RADIUS - HEAD_RADIUS / 2;
		pos.x = static_cast<float>( posX );
		pos.y = static_cast<float>( posY );
		auto smoke = GET_EFFECT_MANAGER()->createEffect(ET_SMOKE, pos + curPos);
		smoke->enter();
	}
}

void BossHead::restart(cocos2d::Ref* ref)
{
	GET_GAME_MANAGER()->changeScene(ASSEMBLY_SCENE);
}

void BossHead::quit(cocos2d::Ref* ref)
{
	cocos2d::Director::getInstance()->end();
}
