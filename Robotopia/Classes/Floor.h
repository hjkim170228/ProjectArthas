/************************************************************************/
/*
	CLASS			: Block
	Author			: 김연우
	역할				: 아래 충돌만 하는 타일 Floor
	최종 수정일자	: 2014-11-09
	최종 수정자		:
	최종 수정사유	:
	Comment			:
*/
/************************************************************************/
#pragma once
#include "Tile.h"
#include "Util.h"

BEGIN_NS_AT

class Floor : public Tile
{
public:
	OVERRIDE bool init();
	OVERRIDE void update(float dTime);
	OVERRIDE void enter();
	OVERRIDE void exit();

	OVERRIDE void initTile(cocos2d::Point origin, cocos2d::Size physicalSize, cocos2d::Size spriteSize);


	CREATE_FUNC(Floor);

private:

};

END_NS_AT