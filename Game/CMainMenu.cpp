#include "CMainMenu.h"
#include "CGame.h"


CMainMenu::CMainMenu(HGE *_hge, CGame *_game)
{
	m_hge = _hge;
	m_cgame = _game;
}


CMainMenu::~CMainMenu()
{
	delete	 m_bk;
	delete	 m_anim;
	delete	 m_gstart;
	delete	 m_gset;
	delete	 m_ghelp;
	delete	 m_exit;

	m_hge->Texture_Free(m_bktex);
	m_hge->Texture_Free(m_animtex);
}

const int XItem = 650;
const int YItem = 344;
const int ItemWidth = 175;
const int ItemHeight = 40;
const int ItemOffset = 50;   //菜单项之间的间隔;
const int LastAnimX = -20;                   //动画猪最后停留的X坐标位置;
const int LastAnimY = WIN_HEIGHT - 454;     //动画猪最后停留的Y坐标位置;
void CMainMenu::Init()   //主菜单中各个纹理的加载和精灵的创建;
{
	m_allowMoving = true;        //初始时，允许小猪移动;

	m_bktex = m_hge->Texture_Load("主菜单.png");               //创建主菜单背景;
	m_bk = new hgeSprite(m_bktex, 0, 0, WIN_WIDTH, WIN_HEIGHT); 

	m_animtex = m_hge->Texture_Load("动画猪.png");            //创建闪入动画;
	m_anim = new hgeSprite(m_animtex, 0, 0, 454, 454);
	m_xanim = -800;									//动画猪初始的X坐标位置;
	m_yanim = LastAnimY;							 //动画猪初始的Y坐标位置;
	m_sndAnim = m_hge->Effect_Load("动画猪.wav");    //加载动画猪的音效;

	m_gstart = new CGUIItem(m_hge, "主菜单字.png", 0, ItemHeight, ItemWidth, ItemHeight);   //创建“开始游戏”;
	m_gstart->SetPositionX(XItem);
	m_gstart->SetPositionY(YItem);

	m_gset = new CGUIItem(m_hge, "主菜单字.png", 0, 0, ItemWidth, ItemHeight);    //创建“游戏设置”;
	m_gset->SetPositionX(XItem);
	m_gset->SetPositionY(YItem + ItemHeight + ItemOffset);

	m_ghelp = new CGUIItem(m_hge, "主菜单字.png", 0, 2*ItemHeight, ItemWidth, ItemHeight);  //创建“游戏帮助”;
	m_ghelp->SetPositionX(XItem+43);
	m_ghelp->SetPositionY(YItem + ItemHeight*2 + ItemOffset*2);

	m_exit = new CGUIItem(m_hge, "主菜单字.png", 0, 3*ItemHeight, ItemWidth, ItemHeight);   //创建“退出”;
	m_exit->SetPositionX(XItem+43);
	m_exit->SetPositionY(YItem + ItemHeight*3 + ItemOffset*3);

}

void CMainMenu::Update()      //主菜单界面的更新;
{
	m_gstart->Update();
	m_gset->Update();
	m_ghelp->Update();
	m_exit->Update();

	UpdateAnim();    //更新动画猪;

	if (m_gstart->IsMouseEnter())             //按下“开始游戏”;
	{
		m_cgame->SetGameState(GAME_CHOOSECARD);
		ResetAnim();
	}
	if (m_gset->IsMouseEnter())               //按下“游戏设置”;
	{
		m_cgame->SetGameState(GAME_SETING);   
		ResetAnim();
	}
	if (m_ghelp->IsMouseEnter())              //按下“游戏帮助”;
	{
		m_cgame->SetGameState(GAME_HELP);
		ResetAnim();
	}
	if (m_exit->IsMouseEnter())               //按下“退出”;
	{
		m_cgame->SetGameState(GAME_EXIT);
	}
}

void CMainMenu::UpdateAnim()
{
	if (m_allowMoving)    //当允许动画猪移动时;
	{
		m_xanim += 8;
	}
	if ((m_xanim >= LastAnimX - 8) && (m_xanim <= LastAnimX))
	{
		m_hge->Effect_PlayEx(m_sndAnim, 100, 0, 1.0, false);  //动画猪到达这个阶段时，播放音效;
	}
	if (m_xanim >= LastAnimX)  //表示动画移动完毕;
	{
		m_allowMoving = false;
	}
}

void CMainMenu::Render()
{
	m_bk->Render(0, 0);
	m_gstart->Render();
	m_gset->Render();
	m_ghelp->Render();
	m_exit->Render();
	m_anim->Render(m_xanim, m_yanim);
}

void CMainMenu::ResetAnim()   //重置动画猪的状态和位置;
{
	m_allowMoving = true;
	m_xanim = -800;
}
