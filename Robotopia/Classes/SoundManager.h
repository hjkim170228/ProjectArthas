﻿/************************************************************************/
/*
CLASS			: EffectManager
Author			: 김성연
역할				: Sound 요청시 생성후 전달
최종 수정일자		: 2014-12-17
최종 수정자		:
최종 수정사유		:
Comment			: 
*/
/************************************************************************/

#pragma once
#include "Util.h"
#include "SimpleAudioEngine.h"

class SoundManager
{
public:
	enum BGMType
	{
		BGM_START = 0,
		BGM_2,
		BGM_EXOTIC_BATTLE,
		BGM_CALLTOADVANTURE,
		BGM_SPLITINSYNAPSE,
		BGM_FIVEARMIES,
		BGM_CLOCK_BOSS_ENTRANCE,
		BGM_END,
	};

	enum PlayerSound
	{
		PLAYER_SOUND_START = 0,

		//기타
		COLLISION_PLAYER_MONSTER,
		GETMONEY,
		MENU,
		STEAM_GET,
		CORPSE_GET,
		CORPSE_LAST_GET,
		PLAYER_DEAD,

		//일반 행동
		CHANGEGEAR,
		JUMP,

		//근거리 상태
		PUNCHMISSILE,
		BLADEMISSILE,
		SUPERARMOR,
		UNBEATABLE,

		//원거리 상태
		LINEARMISSILE,
		BINDINGMISSILE,
		GREANADE_EXPLOSION,

		//나는 상태
		FLYING,
		AIRSKILLMULTIMISSILE,
		AIRSKILLNORMALMISSILE,

		//일반 스킬
		DASH,

		PLAYER_SOUND_END,

	};

	enum NormalMonsterSound
	{
		NORMAL_MONSTER_SOUND_START = 0,
		
		//몬스터 공통
		MONSTERHIT,

		//돼지
		PIG,

		//데빌몬스터
		THUNDER,

		//고등어
		STANDMONSTERSHOT,
		AIMINGMISSIE_COLLISION,

		NORMAL_MONSTER_SOUND_END,
	};

	enum ETCSound
	{
		ETC_SOUND_START = 0,
		//어셈블리 창
		EQUIPCLICK,
		EQUIPDOUBLECLICK,
		UPGRADE,
		WRONGCLICK,
	
		//컴퓨터
		CHARGEGAGE,
	
		//전기트랩
		ELECTRICTRAP,

		//Laser 트랩
		LASERTRAP,
		
		ETC_SOUND_END,
	};

	enum BossSound
	{
		BOSS_SOUND_START = 0,

		//태엽보스
		CLOCK_BOSS_LASER,
		CLOCK_BOSS_MOVE,

		BOSS_SOUND_END,
	};

	SoundManager();
	~SoundManager();

	bool	init();
	void	createBGM(BGMType bgmType, bool isRepeated);

	int	    createSound(ETCSound soundType, bool isRepeated);
	int		createSound(PlayerSound playerSoundType, bool isRepeated);
	int     createSound(NormalMonsterSound nMonsterType, bool isRepeated);
	int     createSound(BossSound bossType, bool isRepeated);

	int		createSound(ETCSound soundType, bool isRepeated, cocos2d::Point pos);
	int		createSound(PlayerSound soundType, bool isRepeated, cocos2d::Point pos);
	int		createSound(NormalMonsterSound soundType, bool isRepeated, cocos2d::Point pos);
	int		createSound(BossSound soundType, bool isRepeated, cocos2d::Point pos);
	void	pauseSound(int soundId);

	//이펙트랑 배경음악 다끔
	void	allStopSound();
	bool	isBackGroundMusicPlaying();


private:


};


