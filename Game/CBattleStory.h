#pragma once
#include "CGUI.h"
#include "CGUIItem.h"

class CGame;

class CBattleStory : public CGUI
{
public:
	CBattleStory(HGE *_hge, CGame *_game);
	~CBattleStory();
	void  Init();      //初始化;
	void  Update();    //更新；
	void  Render();    //绘制；
private:
	CBattleStory();
	CGame      *m_cgame;

	CGUIItem   *m_battle1_story1;  //战场一的故事1；
	CGUIItem   *m_battle1_story2;  //战场二的故事2；

	CGUIItem   *m_battle2_story1;  //战场二的故事1；
	CGUIItem   *m_battle2_story2;  //战场二的故事2；

	CGUIItem   *m_battle3_story1;  //战场三的故事1；
	CGUIItem   *m_battle3_story2;  //战场三的故事2；

	float       m_timeDelta;      //时间偏移量，用于保证界面的需两次跳转才进入游戏；
};

