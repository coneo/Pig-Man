#include "CHelp.h"
#include "CGlobal.h"
#include "CGame.h"

CHelp::CHelp(){}

CHelp::CHelp(HGE *_hge, CGame *_game)
{
	m_hge = _hge;
	m_cgame = _game;
}


CHelp::~CHelp(void)
{
	delete	 m_bk;
	delete	 m_return;
	delete	 m_battle1_info;
	delete	 m_battle2_info;
	delete	 m_battle3_info;
	m_hge->Texture_Free(m_bktex);
}

const int XPO = 100;
const int WIDTH = 670;
const int HEIGHT = 460;
void CHelp::Init()
{
	m_bktex = m_hge->Texture_Load("���汳��.png");				 //���ر����������������Ʊ����ľ���;
	m_bk = new hgeSprite(m_bktex, 0, 0, WIN_WIDTH, WIN_HEIGHT); //�˴���WIN_WIDTHΪCGlobal.h�е�ȫ�ֱ���;

	m_return = new CGUIItem(m_hge, "�ص���ҳ.png", 0, 0, 130, 50);    //����һ�������ء��˵�;
	m_return->SetPositionX(WIN_WIDTH - 200);
	m_return->SetPositionY(WIN_HEIGHT - 150);

	m_battle1_info = new CGUIItem(m_hge, "��������.png", 0, 0, 514, 661);
	m_battle1_info->SetPositionX(200);
	m_battle1_info->SetPositionY(50);

	m_battle2_info = new CGUIItem(m_hge, "battle2_info.png", 0, 0, WIDTH, HEIGHT);
	m_battle2_info->SetPositionX(XPO);
	m_battle2_info->SetPositionY(XPO);

	m_battle3_info = new CGUIItem(m_hge, "battle3_info.png", 0, 0, WIDTH, HEIGHT);
	m_battle3_info->SetPositionX(XPO);
	m_battle3_info->SetPositionY(XPO);
}

void CHelp::Update()
{
	m_return->Update();
	m_battle1_info->Update();
	m_battle2_info->Update();
	m_battle3_info->Update();

	if (m_return->IsMouseEnter())  //�����������ء���ť���򷵻ء����˵���;
	{
		m_cgame->SetGameState(GAME_MAINMENU);
	}
}

void CHelp::Render()
{
	m_bk->Render(0, 0);   //���Ʊ���;
	m_return->Render();
	//m_battle3_info->Render();
	m_battle1_info->Render();
	//m_battle2_info->Render();
}