#include "CChooseCard.h"
#include "CGlobal.h"
#include "CGame.h"

CChooseCard::CChooseCard(){};

CChooseCard::CChooseCard(HGE *_hge, CGame *_game)
{
	m_hge = _hge;
	m_cgame = _game;
}


CChooseCard::~CChooseCard()
{
	delete		m_bk;
	delete		m_battle1;
	delete      m_battle2;
	delete		m_battle3;
	delete		m_return;
	m_hge->Texture_Free(m_bktex);
}

const int XItem = 100;
const int YItem = 150;
const int ItemWidth = 215;
const int ItemHeight = 300;
void CChooseCard::Init()
{
	m_bktex = m_hge->Texture_Load("���汳��.png");              //����������غ;���Ĵ���;
	m_bk = new hgeSprite(m_bktex, 0, 0, WIN_WIDTH, WIN_HEIGHT);

	m_battle1 = new CGUIItem(m_hge, "ģʽѡ��.png", 0, 0, ItemWidth, ItemHeight);   //����һ����ģʽһ���˵���;
	m_battle1->SetPositionX(XItem);
	m_battle1->SetPositionY(YItem);

	m_battle2 = new CGUIItem(m_hge, "ģʽѡ��.png", 0, ItemHeight, ItemWidth, ItemHeight);   //����һ����ģʽ�����˵���;
	m_battle2->SetPositionX(XItem+300);
	m_battle2->SetPositionY(YItem);

	m_battle3 = new CGUIItem(m_hge, "ģʽѡ��.png", 0, 2*ItemHeight, ItemWidth, ItemHeight);   //����һ����ģʽ�����˵���;
	m_battle3->SetPositionX(XItem+600);
	m_battle3->SetPositionY(YItem);

	m_return = new CGUIItem(m_hge, "�ص���ҳ.png", 0, 0, 130, 50);     //����һ�������ء��˵�;
	m_return->SetPositionX(WIN_WIDTH - 200);
	m_return->SetPositionY(WIN_HEIGHT - 150);
}

void CChooseCard::Update()
{
	m_battle1->Update();
	m_battle2->Update();
	m_battle3->Update();
	m_return->Update();
	if (m_battle1->IsMouseEnter())
	{
		//m_hge->System_SetState(HGE_HIDEMOUSE, true);
		m_cgame->SetGameState(GAME_BATTLE1_STORY1);
	}
	if (m_battle2->IsMouseEnter())
	{
		//m_hge->System_SetState(HGE_HIDEMOUSE, true);   //����ս�����������;
		m_cgame->SetGameState(GAME_BATTLE2_STORY1);
	}
	if (m_battle3->IsMouseEnter())
	{
		//m_hge->System_SetState(HGE_HIDEMOUSE, true);  //����ģʽ�������������;
		m_cgame->SetGameState(GAME_BATTLE3_STORY1);
	}
	if(m_return->IsMouseEnter())
	{
		m_cgame->SetGameState(GAME_MAINMENU);
	}
}

void CChooseCard::Render()
{
	m_bk->Render(0, 0);
	m_battle1->Render();
	m_battle2->Render();
	m_battle3->Render();
	m_return->Render();
}
