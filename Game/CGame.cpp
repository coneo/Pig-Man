#include "CGame.h"
#include "CGlobal.h"

#include "CLoading.h"
#include "CMainMenu.h"
#include "CChooseCard.h"
#include "CSeting.h"
#include "CHelp.h"
#include "CGameOver.h"
#include "CBattleStory.h"

CGame::CGame()
{
	m_hge  =  NULL;
}

CGame::~CGame()
{
	m_battle->Release();
	m_battle2->Release();
	m_battle0->Release();

	delete	  m_loading;
	delete    m_mainMenu;
	delete    m_chooseCard;
	delete	  m_seting;
	delete	  m_help;
	delete	  m_gameover;
	delete    m_battlestory;

	m_hge->Effect_Free(m_sndbk);
	m_hge->System_Shutdown();
	m_hge->Release();
}

//对hge进行设置必要状态，并进行初始化;
bool CGame::Init( bool (*frameFunc)(), bool (*renderFunc)())
{
	bool status = true;
	m_hge = hgeCreate(HGE_VERSION);
	m_hge->System_SetState(HGE_LOGFILE, "hge_tut06.log");
	m_hge->System_SetState(HGE_FRAMEFUNC, frameFunc);
	m_hge->System_SetState(HGE_RENDERFUNC, renderFunc);
	m_hge->System_SetState(HGE_FPS, 100);
	m_hge->System_SetState(HGE_TITLE, "HGE Tutorial 06 - Creating menus");
	m_hge->System_SetState(HGE_WINDOWED, true);
	m_hge->System_SetState(HGE_HIDEMOUSE, false);
	m_hge->System_SetState(HGE_SHOWSPLASH, false);
	m_hge->System_SetState(HGE_SCREENWIDTH, WIN_WIDTH);
	m_hge->System_SetState(HGE_SCREENHEIGHT, WIN_HEIGHT);
	m_hge->System_SetState(HGE_SCREENBPP, 32);
	m_hge->Random_Seed(0);

	if ( !m_hge->System_Initiate())
	{
		status = false;
	}
	m_state = GAME_LOADING;                         //初始化游戏状态为加载游戏状态;

	/***************************创建游戏的各种界面*****************************/

	m_loading = new CLoading(m_hge, this);           //实例化“游戏加载”;
	m_loading->Init();
	m_mainMenu = new CMainMenu(m_hge, this);         //实例化GUI;
	m_mainMenu->Init();
	m_chooseCard = new CChooseCard(m_hge, this);     //实例化“ChooseCard”;
	m_chooseCard->Init();
	m_seting = new CSeting(m_hge, this);             //实例化“游戏设置”;
	m_seting->Init();
	m_help = new CHelp(m_hge, this);                 //实例化“游戏帮助”;
	m_help->Init();
	m_gameover = new CGameOver(m_hge, this);         //实例化“游戏结束”;
	m_gameover->Init();
	m_battlestory = new CBattleStory(m_hge, this);     //实例化游戏故事;
	m_battlestory->Init();
	/**********************************创建三个战场*******************************/
	m_battle0 = new CBattle0(m_hge);     //战场一;
	m_battle = new CBattle1(m_hge, this);     //战场二;
	m_battle2 = new CBattle2(m_hge);    //战场三;

	m_battle0->Init();
	m_battle->Init();
	m_battle2->Init();

	/***************************加载音效*****************************/
	m_sndbk = m_hge->Effect_Load("保卫模式背景音乐.mp3");  //加载音效;
	//m_hge->Effect_Play(m_sndbk);                  //播放音效;

	/*****************************************************************/

	return status;
}

//开始跑hge引擎；
void CGame::Run()
{
	m_hge->System_Start();
}

//根据游戏的状态对游戏进行控制；
//bool state = false;
bool CGame::GameCtrl() 
{

	//return m_battle->Run();
	switch (m_state)
	{
	case GAME_LOADING:
		m_loading->Update();      //更新“游戏加载”;
		break;
	case GAME_MAINMENU:
		m_mainMenu->Update();     //主菜单的逻辑控制;
		break;
	case GAME_CHOOSECARD:
		m_chooseCard->Update();   //更新“选择关卡”;
		break;
	case GAME_SETING:
		m_seting->Update();       //更新“游戏设置”;
		break;
	case GAME_HELP:
		m_help->Update();         //更新“游戏帮助”;
		break;
	case GAME_BATTLE1_STORY1:      //战场故事加载;
	case GAME_BATTLE1_STORY2:
	case GAME_BATTLE2_STORY1:
	case GAME_BATTLE2_STORY2:
	case GAME_BATTLE3_STORY1:
	case GAME_BATTLE3_STORY2:
		m_battlestory->Update();
		break;
	case GAME_BATTLE1:
		m_battle0->Run();
		break;
	case GAME_BATTLE2:
		m_hge->Effect_PlayEx(m_sndbk, 40, 0, 1.0, true);              //播放音效;
		m_battle->Run();
		break;
	case  GAME_BATTLE3:
		m_battle2->Run();
		break;
	case GAME_OVER:
		m_gameover->Update();
		break;
	case GAME_EXIT:
		return true;
		break;
	default:
		break;
	}

	if(m_hge->Input_KeyDown(HGEK_ESCAPE))    //退出的键盘事件;
		return true;
	return false;

}

//绘制游戏中的一切;
bool CGame::GameRender()
{
	m_hge->Gfx_BeginScene();
	m_hge->Gfx_Clear(0);
	//return m_battle->Render();
	switch (m_state)
	{
	case GAME_LOADING:
		m_loading->Render();               //绘制“游戏加载”;
		break;
	case GAME_MAINMENU:
		m_mainMenu->Render();              //绘制"主界面";
		break;
	case GAME_CHOOSECARD:
		m_chooseCard->Render();            //绘制“选择关卡”;
		break;
	case GAME_SETING:
		m_seting->Render();                //绘制“游戏设置”;
		break;
	case GAME_HELP:
		m_help->Render();                  //绘制“游戏帮助”;
		break;
	case GAME_BATTLE1_STORY1:
	case GAME_BATTLE1_STORY2:
	case GAME_BATTLE2_STORY1:
	case GAME_BATTLE2_STORY2:
	case GAME_BATTLE3_STORY1:
	case GAME_BATTLE3_STORY2:
		m_battlestory->Render();
		break;
	case GAME_BATTLE1:                     //绘制战场一;
		m_battle0->Render();
		break;
	case GAME_BATTLE2:                     //绘制战场二;
		m_battle->Render();            
		break;
	case GAME_BATTLE3:                     //绘制战场三;
		m_battle2->Render();
		break;
	case GAME_OVER:                        //绘制“游戏结束”界面;
		m_gameover->Render();
		break;
	default:
		break;
	}         
	m_hge->Gfx_EndScene();
	return false;
}

//释放游戏资源;
void CGame::Release()
{
	/*m_hge->System_Shutdown();
	m_hge->Release();*/
}

//获取游戏的运行状态;
GameState CGame::GetState() const
{
	return m_state;
}

//设置游戏状态;
void CGame::SetGameState(GameState _state)
{
	m_state = _state;
}

//获取HGE指针；
HGE* CGame::GetHGE()
{
	return m_hge;
}