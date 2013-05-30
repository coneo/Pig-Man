#include "CLoading.h"
#include "CGame.h"
#include "CGlobal.h"

CLoading::CLoading()
{
}

CLoading::CLoading(HGE *_hge, CGame *_game)
{
	m_hge = _hge;
	m_cgame = _game;
}

CLoading::~CLoading(void)
{
}

void CLoading::Init()
{
	m_WidthOfLod = 0.0;      //初始化进度条纹理左上角的X坐标;

	m_bktex = m_hge->Texture_Load("载入界面.png");      //加载背景纹理，并创建背景;
	m_bk = new hgeSprite(m_bktex, 0, 0, WIN_WIDTH, WIN_HEIGHT);

	m_loadtex = m_hge->Texture_Load("进度条.png");     //加载进度条的纹理;
	m_load = new hgeSprite(m_loadtex, 0, 0, WIN_WIDTH, WIN_HEIGHT);
}

void CLoading::Update()   //更新场景;
{
	m_WidthOfLod += 2.0;   //绘制进度条的width逐渐增加;
	if(m_WidthOfLod >= 900) //进度条走完;
		m_cgame->SetGameState(GAME_MAINMENU);
	m_load->SetTextureRect(0, 0, m_WidthOfLod, 768, true);
}

void CLoading::Render()   //绘制场景;
{
	m_bk->Render(0, 0);
	m_load->Render(0, 0);
}