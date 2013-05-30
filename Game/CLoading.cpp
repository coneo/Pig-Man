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
	m_WidthOfLod = 0.0;      //��ʼ���������������Ͻǵ�X����;

	m_bktex = m_hge->Texture_Load("�������.png");      //���ر�����������������;
	m_bk = new hgeSprite(m_bktex, 0, 0, WIN_WIDTH, WIN_HEIGHT);

	m_loadtex = m_hge->Texture_Load("������.png");     //���ؽ�����������;
	m_load = new hgeSprite(m_loadtex, 0, 0, WIN_WIDTH, WIN_HEIGHT);
}

void CLoading::Update()   //���³���;
{
	m_WidthOfLod += 2.0;   //���ƽ�������width������;
	if(m_WidthOfLod >= 900) //����������;
		m_cgame->SetGameState(GAME_MAINMENU);
	m_load->SetTextureRect(0, 0, m_WidthOfLod, 768, true);
}

void CLoading::Render()   //���Ƴ���;
{
	m_bk->Render(0, 0);
	m_load->Render(0, 0);
}