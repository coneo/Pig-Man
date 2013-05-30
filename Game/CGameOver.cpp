#include "CGameOver.h"
#include "CGame.h"

CGameOver::CGameOver()
{
}

CGameOver::CGameOver(HGE *_hge, CGame *_game)
{
	m_hge = _hge;
	m_cgame = _game;
}

CGameOver::~CGameOver()
{
	delete	  m_bk;
	m_hge->Texture_Free(m_bktex);
}

const int XItem = 420;
const int YItem = 250;
const int ItemWidth = 175;
const int ItemHeight = 40;
const int ItemOffset = 50;   //�˵���֮��ļ��;
void CGameOver::Init()
{
	m_bktex = m_hge->Texture_Load("��Ϸ��������.png");
	m_bk = new hgeSprite(m_bktex, 0, 0, 157, 169);

	m_returnToMainMenu = new CGUIItem(m_hge, "���˵���.png", 0, 3*ItemHeight, ItemWidth, ItemHeight);   //�������˵�;
	m_returnToMainMenu->SetPositionX(XItem+30);
	m_returnToMainMenu->SetPositionY(YItem + ItemHeight + ItemOffset);
}

void CGameOver::Update()
{
	 m_returnToMainMenu->Update();

	 if (m_returnToMainMenu->IsMouseEnter())
	 {
		 m_cgame->SetGameState(GAME_EXIT);  //������Ϸ״̬;
	 }
}

void CGameOver::Render()
{
	m_bk->Render(XItem, YItem);
	m_returnToMainMenu->Render();
}