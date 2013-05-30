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

//��hge�������ñ�Ҫ״̬�������г�ʼ��;
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
	m_state = GAME_LOADING;                         //��ʼ����Ϸ״̬Ϊ������Ϸ״̬;

	/***************************������Ϸ�ĸ��ֽ���*****************************/

	m_loading = new CLoading(m_hge, this);           //ʵ��������Ϸ���ء�;
	m_loading->Init();
	m_mainMenu = new CMainMenu(m_hge, this);         //ʵ����GUI;
	m_mainMenu->Init();
	m_chooseCard = new CChooseCard(m_hge, this);     //ʵ������ChooseCard��;
	m_chooseCard->Init();
	m_seting = new CSeting(m_hge, this);             //ʵ��������Ϸ���á�;
	m_seting->Init();
	m_help = new CHelp(m_hge, this);                 //ʵ��������Ϸ������;
	m_help->Init();
	m_gameover = new CGameOver(m_hge, this);         //ʵ��������Ϸ������;
	m_gameover->Init();
	m_battlestory = new CBattleStory(m_hge, this);     //ʵ������Ϸ����;
	m_battlestory->Init();
	/**********************************��������ս��*******************************/
	m_battle0 = new CBattle0(m_hge);     //ս��һ;
	m_battle = new CBattle1(m_hge, this);     //ս����;
	m_battle2 = new CBattle2(m_hge);    //ս����;

	m_battle0->Init();
	m_battle->Init();
	m_battle2->Init();

	/***************************������Ч*****************************/
	m_sndbk = m_hge->Effect_Load("����ģʽ��������.mp3");  //������Ч;
	//m_hge->Effect_Play(m_sndbk);                  //������Ч;

	/*****************************************************************/

	return status;
}

//��ʼ��hge���棻
void CGame::Run()
{
	m_hge->System_Start();
}

//������Ϸ��״̬����Ϸ���п��ƣ�
//bool state = false;
bool CGame::GameCtrl() 
{

	//return m_battle->Run();
	switch (m_state)
	{
	case GAME_LOADING:
		m_loading->Update();      //���¡���Ϸ���ء�;
		break;
	case GAME_MAINMENU:
		m_mainMenu->Update();     //���˵����߼�����;
		break;
	case GAME_CHOOSECARD:
		m_chooseCard->Update();   //���¡�ѡ��ؿ���;
		break;
	case GAME_SETING:
		m_seting->Update();       //���¡���Ϸ���á�;
		break;
	case GAME_HELP:
		m_help->Update();         //���¡���Ϸ������;
		break;
	case GAME_BATTLE1_STORY1:      //ս�����¼���;
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
		m_hge->Effect_PlayEx(m_sndbk, 40, 0, 1.0, true);              //������Ч;
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

	if(m_hge->Input_KeyDown(HGEK_ESCAPE))    //�˳��ļ����¼�;
		return true;
	return false;

}

//������Ϸ�е�һ��;
bool CGame::GameRender()
{
	m_hge->Gfx_BeginScene();
	m_hge->Gfx_Clear(0);
	//return m_battle->Render();
	switch (m_state)
	{
	case GAME_LOADING:
		m_loading->Render();               //���ơ���Ϸ���ء�;
		break;
	case GAME_MAINMENU:
		m_mainMenu->Render();              //����"������";
		break;
	case GAME_CHOOSECARD:
		m_chooseCard->Render();            //���ơ�ѡ��ؿ���;
		break;
	case GAME_SETING:
		m_seting->Render();                //���ơ���Ϸ���á�;
		break;
	case GAME_HELP:
		m_help->Render();                  //���ơ���Ϸ������;
		break;
	case GAME_BATTLE1_STORY1:
	case GAME_BATTLE1_STORY2:
	case GAME_BATTLE2_STORY1:
	case GAME_BATTLE2_STORY2:
	case GAME_BATTLE3_STORY1:
	case GAME_BATTLE3_STORY2:
		m_battlestory->Render();
		break;
	case GAME_BATTLE1:                     //����ս��һ;
		m_battle0->Render();
		break;
	case GAME_BATTLE2:                     //����ս����;
		m_battle->Render();            
		break;
	case GAME_BATTLE3:                     //����ս����;
		m_battle2->Render();
		break;
	case GAME_OVER:                        //���ơ���Ϸ����������;
		m_gameover->Render();
		break;
	default:
		break;
	}         
	m_hge->Gfx_EndScene();
	return false;
}

//�ͷ���Ϸ��Դ;
void CGame::Release()
{
	/*m_hge->System_Shutdown();
	m_hge->Release();*/
}

//��ȡ��Ϸ������״̬;
GameState CGame::GetState() const
{
	return m_state;
}

//������Ϸ״̬;
void CGame::SetGameState(GameState _state)
{
	m_state = _state;
}

//��ȡHGEָ�룻
HGE* CGame::GetHGE()
{
	return m_hge;
}