#include "CBattleStory.h"
#include "CGlobal.h"
#include "CGame.h"

CBattleStory::CBattleStory()
{
}

CBattleStory::CBattleStory(HGE *_hge, CGame *_game)
{
	m_hge = _hge;
	m_cgame = _game;
}

CBattleStory::~CBattleStory()
{
	delete  m_battle1_story1;
	delete  m_battle1_story2;
	delete  m_battle2_story1;
	delete  m_battle2_story2;
	delete  m_battle3_story1;
	delete  m_battle3_story2;
}

void CBattleStory::Init()
{
	m_timeDelta = 0; //4 >= 3;

	m_battle1_story1 = new CGUIItem(m_hge, "战场一_故事1.png", 0, 0, WIN_WIDTH, WIN_HEIGHT);
	m_battle1_story2 = new CGUIItem(m_hge, "战场一_故事2.png", 0, 0, WIN_WIDTH, WIN_HEIGHT);
	m_battle2_story1 = new CGUIItem(m_hge, "战场二_故事1.png", 0, 0, WIN_WIDTH, WIN_HEIGHT);
	m_battle2_story2 = new CGUIItem(m_hge, "战场二_故事2.png", 0, 0, WIN_WIDTH, WIN_HEIGHT);
	m_battle3_story1 = new CGUIItem(m_hge, "战场三_故事1.png", 0, 0, WIN_WIDTH, WIN_HEIGHT);
	m_battle3_story2 = new CGUIItem(m_hge, "战场三_故事2.png", 0, 0, WIN_WIDTH, WIN_HEIGHT);
}

void CBattleStory::Update()
{
	m_timeDelta += m_hge->Timer_GetDelta();

// 	if ((m_hge->Input_KeyDown(HGEK_SPACE)) && (m_timeDelta >= 5))   //按下空格键,并且时间间隔超过一定值;
// 	{
		if((m_cgame->GetState() == GAME_BATTLE1_STORY1) && (m_timeDelta >= 4))   //此处的4为页面停顿时间;
		{
			m_cgame->SetGameState(GAME_BATTLE1_STORY2);
			m_timeDelta = 0;
		}
		if((m_cgame->GetState() == GAME_BATTLE1_STORY2) && (m_timeDelta >= 4))
		{
			m_cgame->SetGameState(GAME_BATTLE1);
		}
		if((m_cgame->GetState() == GAME_BATTLE2_STORY1) && (m_timeDelta >= 4))
		{
			m_cgame->SetGameState(GAME_BATTLE2_STORY2);
			m_timeDelta = 0;
		}
		if((m_cgame->GetState() == GAME_BATTLE2_STORY2)  && (m_timeDelta >= 4))
		{
			m_cgame->SetGameState(GAME_BATTLE2);
		}
		if((m_cgame->GetState() == GAME_BATTLE3_STORY1)  && (m_timeDelta >= 4))
		{
			m_cgame->SetGameState(GAME_BATTLE3_STORY2);
			m_timeDelta = 0;
		}
		if((m_cgame->GetState() == GAME_BATTLE3_STORY2)  && (m_timeDelta >= 4))
		{
			m_cgame->SetGameState(GAME_BATTLE3);
		}
	//}
// 	if (m_battle1_story1->IsMouseEnter())  //更改游戏状态,实现界面的跳转;
// 		m_cgame->SetGameState(GAME_BATTLE1_STORY2);
// 	if(m_battle1_story2->IsMouseEnter())
// 		m_cgame->SetGameState(GAME_BATTLE1);
// 	if (m_battle2_story1->IsMouseEnter())
// 		m_cgame->SetGameState(GAME_BATTLE2_STORY2);
// 	if(m_battle2_story2->IsMouseEnter())
// 		m_cgame->SetGameState(GAME_BATTLE2);
// 	if (m_battle3_story1->IsMouseEnter())
// 		m_cgame->SetGameState(GAME_BATTLE3_STORY2);
// 	if(m_battle3_story2->IsMouseEnter())
// 		m_cgame->SetGameState(GAME_BATTLE3);
}

void CBattleStory::Render()
{
	switch(m_cgame->GetState())
	{
	case GAME_BATTLE1_STORY1:
		m_battle1_story1->Render();
		break;
	case GAME_BATTLE1_STORY2:
		m_battle1_story2->Render();
		break;
	case GAME_BATTLE2_STORY1:
		m_battle2_story1->Render();
		break;
	case GAME_BATTLE2_STORY2:
		m_battle2_story2->Render();
		break;
	case GAME_BATTLE3_STORY1:
		m_battle3_story1->Render();
		break;
	case GAME_BATTLE3_STORY2:
		m_battle3_story2->Render();
		break;
	default:
		break;
	}
	
}