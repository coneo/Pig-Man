#include "CSeting.h"
#include "CGlobal.h"
#include "CGame.h"

CSeting::CSeting()
{
}

CSeting::CSeting(HGE *_hge, CGame *_game)
{
	m_hge = _hge;
	m_cgame = _game;
}

CSeting::~CSeting()
{
	delete	 m_bk;
	delete	 m_return;
	delete   m_seting;
	m_hge->Texture_Free(m_bktex);
}

void CSeting::Init()
{
	m_bktex = m_hge->Texture_Load("界面背景.png");				 //加载背景纹理，并创建绘制背景的精灵;
	m_bk = new hgeSprite(m_bktex, 0, 0, WIN_WIDTH, WIN_HEIGHT);

	m_return = new CGUIItem(m_hge, "回到首页.png", 0, 0, 130, 50);    //创建一个“返回”菜单;
	m_return->SetPositionX(WIN_WIDTH - 200);
	m_return->SetPositionY(WIN_HEIGHT - 150);

	m_seting = new CGUIItem(m_hge, "游戏设置界面.png", 0, 0, 514, 661);  //创建设置背景;
	m_seting->SetPositionX(200);
	m_seting->SetPositionY(50);
}

void CSeting::Update()
{
	m_return->Update();
	m_seting->Update();

	if (m_return->IsMouseEnter())
	{
		m_cgame->SetGameState(GAME_MAINMENU);
	}
}

void CSeting::Render()
{
	m_bk->Render(0, 0);        //绘制背景;
	m_return->Render();
	m_seting->Render();
}