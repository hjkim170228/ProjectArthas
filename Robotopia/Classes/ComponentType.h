﻿/************************************************************************/
/*
	CLASS			: ComponentType
	Author			: 남현욱
	역할				: BaseComponent들의 Type 값 정의 enum 관리.
	최종 수정일자	: 2014-11-1
	최종 수정자		: 남현욱
	최종 수정사유	: 
	Comment			: 
*/
/************************************************************************/

#pragma once
#include "Util.h"

enum ObjectType
{
	OT_START = 1000,
	OT_PLAYER,
	OT_CORPSE,

	OT_MONSTER_START = 1011,
	OT_MONSTER,
	OT_MONSTER_STAND_SHOT,
	OT_MONSTER_RUSH,
	OT_MONSTER_DEVIL,
	OT_MONSTER_BOSS_FIRST,
	OT_MONSTER_END,

	OT_TILE_START = 1101,
	OT_BLOCK,
	OT_BLOCK_MOVING,
	OT_BLOCK_TURRET,
	OT_FLOOR,
	OT_PORTAL,
	OT_TRAP_UNDERGROUND,
	OT_LASER,
	OT_LASER_1,
	OT_LASER_2,
	OT_LASER_3,
	OT_TRAP_ELECTRIC,
	OT_TILE_END,

	OT_MISSILE_START = 1201,
	OT_MISSILE_PLAYER_MELEE,
	OT_MISSILE_PLAYER_LINEAR,
	OT_MISSILE_AIMING,
	OT_MISSILE_PUNCH,
	OT_MISSILE_THUNDER,
	OT_MISSILE_BIND,
	OT_MISSILE_GRENADE,
	OT_MISSILE_BOMB,
	OT_MISSILE_LINEAR,
	OT_MISSILE_BLADE,
	OT_MISSILE_END,

	OT_NPC_START = 1301,
	OT_COMPUTER,
	OT_VENDING_MACHINE,
	OT_LEVER,
	OT_NPC_END,

	OT_ITEM_START = 1401,
	OT_HPKIT,
	OT_ITEM_END,

	OT_END,
};

enum ComponentType
{
	//BaseComponent Type
	CT_NONE = 0,
	CT_COMPONENT_START = 0,
	CT_OBSERVER,
	CT_PHYSICS,
	CT_ANIMATION,
	CT_SPRITE,
	CT_RENDER,
	CT_COMMAND,
	CT_FSM,
	CT_STATE,

// 		//Object Type
// 		OT_START = 1000,
// 		OT_PLAYER,
// 
// 		OT_MONTER_START = 1011,
// 		OT_MONSTER,
// 		OT_MONSTER_STAND_SHOT,
// 		OT_MONSTER_RUSH,
// 		OT_MONSTER_END,
// 
// 		OT_TILE_START = 1101,
// 		OT_BLOCK,
// 		OT_BLOCK_MOVING,
// 		OT_BLOCK_TURRET,
// 		OT_FLOOR,
// 		OT_PORTAL_OPEN,
// 		OT_PORTAL_CLOSED,
// 		OT_TRAP_UNDERGROUND,
// 		OT_TILE_END,
// 
// 		OT_MISSILE_START = 1201,
// 		OT_MISSILE_PLAYER_MELEE,
// 		OT_MISSILE_PLAYER_LINEAR,
// 		OT_MISSILE_AIMING,
// 		OT_MISSILE_END,
// 		
// 		OT_END,

	CT_COMPONENT_END,

};

