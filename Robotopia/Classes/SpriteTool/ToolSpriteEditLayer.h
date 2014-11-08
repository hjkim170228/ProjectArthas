/************************************************************************/
/*
CLASS			: ToolSpriteEditLayer
Author			: �輺��
����				: ���ο� Sprite ���� Edit Box ���� �߰�
���� ��������		: 2014-11-08
���� ������		:
���� ��������		:
Comment			:
*/
/************************************************************************/
#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
#include "Util.h"
#include <vector>

#define  MAXFILE_NAME 50
#define  MAX_CHAR 256
BEGIN_NS_AT

class ToolSpriteEditLayer : public cocos2d::Layer, public cocos2d::extension::EditBoxDelegate
{
public:
	enum InfoOrder
	{
		INFOSTART = 0,
		TYPE = INFOSTART + 1,
		DELAY,
		FRAMENUM,
		FILENAME,
		SAVE,
		AUTOSAVE,
	};
	~ToolSpriteEditLayer();
	OVERRIDE bool init();
	OVERRIDE void update(float dTime);
	void		  initSpriteInfo();
	void		  initAnimationInfo();
	void		  initFileNameBox();
	
	void          ATMenuButtonCallback(cocos2d::Ref* sender);
	void          STMenuButtonCallback(cocos2d::Ref* sender);
	void          ATListShow(cocos2d::Ref* sender);
	void		  STListShow(cocos2d::Ref* sender);

	void		  createMenuButton(ResourceType type, bool isAT);
	void		  createAniNames(AnimationInfo* aniInfo);
	void		  createAllMenuButton();
	void		  createListButton(std::string string, bool isAT);
	std::string	  createButtonTitle(ResourceType type);
	void		  createLabel(std::string title);
	void		  createEditBox(char* boxTitle, int fontSize, int maxLength, InfoOrder tag);
	void		  createEditBox(char* boxTitle, int fontSize, int maxLength, InfoOrder tag, int boxNum);

	void          assignLabels();
	void		  assignMenuButtons();
	void		  assignEditBox();
	void		  assignFileNameBox();
	

	CREATE_FUNC(ToolSpriteEditLayer);
private:
	std::vector<AnimationInfo>						 m_AnimationInfos;
	std::vector<SpriteInfo>							 m_SpriteInfos;
	std::vector<cocos2d::Menu*>						 m_ATMenuButtons;
	std::vector<cocos2d::Menu*>						 m_STMenuButtons;
	std::vector<cocos2d::Label*>                     m_Labels;
	std::vector<cocos2d::extension::EditBox*>		 m_EditBoxs;
	std::vector<cocos2d::extension::EditBox*>		 m_FileNameBoxs;

	int												 m_CurrentATInfoIdx;
	int												 m_CurrentSTInfoIdx;
	bool											 m_IsATState;

	const char*								  m_CurrentType;
	ResourceType							  m_CurrentTypeEnum;
	float									  m_CurrentDelay;
	int										  m_CurrentFrameNum;
	int										  m_PrevFrameNum;
	char									  m_CurrentFileName[MAXFILE_NAME][MAX_CHAR];
	int										  m_CurrentFileNameNum;

	

	//����Ʈ �ڽ� Ŭ���ϸ� ȣ���ϴ� �޼ҵ�
	OVERRIDE void editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox);
	//����Ʈ �ڽ� �Է��� ����Ű�� �Է��ؼ� ������ �� ��µǴ� �޼ҵ�
	OVERRIDE void editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox);
	//����Ʈ �ڽ��� Ŭ���� �� ���ڸ� �Է��� ������ ȣ��Ǵ� �޼ҵ�
	OVERRIDE void editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text);
	//����Ű�� �Է��� �� ��µǴ� �޼ҵ�, �Ϲ������� ����Ű�� �Է��ϸ� editBoxEditingDidEnd()�� ȣ��ǰ�
	//editBoxReturn() �޼ҵ尡 �� �������� ȣ��˴ϴ�.
	OVERRIDE void editBoxReturn(cocos2d::extension::EditBox* editBox);

};

END_NS_AT