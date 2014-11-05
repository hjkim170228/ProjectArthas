#pragma once
#include "cocos2d.h"
#include "Util.h"
#include "DataType.h"

BEGIN_NS_AT
class Player;
class GameScene;
class StageManager
{
public:
	StageManager();
	~StageManager();

	bool			init();
	void			initStage(int stageNum);
	const Player*	getPlayer();
private:
	StageData		m_StageData;
	GameScene*		m_GameScene;

};

END_NS_AT