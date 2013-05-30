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
const int ItemOffset = 50;   //菜单项之间的间隔;
void CGameOver::Init()
{
	m_bktex = m_hge->Texture_Load("游戏结束界面.png");
	m_bk = new hgeSprite(m_bktex, 0, 0, 157, 169);

	m_returnToMainMenu = new CGUIItem(m_hge, "主菜单字.png", 0, 3*ItemHeight, ItemWidth, ItemHeight);   //返回主菜单;
	m_returnToMainMenu->SetPositionX(XItem+30);
	m_returnToMainMenu->SetPositionY(YItem + ItemHeight + ItemOffset);
}

void CGameOver::Update()
{
	 m_returnToMainMenu->Update();

	 if (m_returnToMainMenu->IsMouseEnter())
	 {
		 m_cgame->SetGameState(GAME_EXIT);  //设置游戏状态;
	 }
}

void CGameOver::Render()
{
	m_bk->Render(XItem, YItem);
	m_returnToMainMenu->Render();
}