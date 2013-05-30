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
const int ItemOffset = 50;   //�˵���֮��ļ��;
const int LastAnimX = -20;                   //���������ͣ����X����λ��;
const int LastAnimY = WIN_HEIGHT - 454;     //���������ͣ����Y����λ��;
void CMainMenu::Init()   //���˵��и�������ļ��غ;���Ĵ���;
{
	m_allowMoving = true;        //��ʼʱ������С���ƶ�;

	m_bktex = m_hge->Texture_Load("���˵�.png");               //�������˵�����;
	m_bk = new hgeSprite(m_bktex, 0, 0, WIN_WIDTH, WIN_HEIGHT); 

	m_animtex = m_hge->Texture_Load("������.png");            //�������붯��;
	m_anim = new hgeSprite(m_animtex, 0, 0, 454, 454);
	m_xanim = -800;									//�������ʼ��X����λ��;
	m_yanim = LastAnimY;							 //�������ʼ��Y����λ��;
	m_sndAnim = m_hge->Effect_Load("������.wav");    //���ض��������Ч;

	m_gstart = new CGUIItem(m_hge, "���˵���.png", 0, ItemHeight, ItemWidth, ItemHeight);   //��������ʼ��Ϸ��;
	m_gstart->SetPositionX(XItem);
	m_gstart->SetPositionY(YItem);

	m_gset = new CGUIItem(m_hge, "���˵���.png", 0, 0, ItemWidth, ItemHeight);    //��������Ϸ���á�;
	m_gset->SetPositionX(XItem);
	m_gset->SetPositionY(YItem + ItemHeight + ItemOffset);

	m_ghelp = new CGUIItem(m_hge, "���˵���.png", 0, 2*ItemHeight, ItemWidth, ItemHeight);  //��������Ϸ������;
	m_ghelp->SetPositionX(XItem+43);
	m_ghelp->SetPositionY(YItem + ItemHeight*2 + ItemOffset*2);

	m_exit = new CGUIItem(m_hge, "���˵���.png", 0, 3*ItemHeight, ItemWidth, ItemHeight);   //�������˳���;
	m_exit->SetPositionX(XItem+43);
	m_exit->SetPositionY(YItem + ItemHeight*3 + ItemOffset*3);

}

void CMainMenu::Update()      //���˵�����ĸ���;
{
	m_gstart->Update();
	m_gset->Update();
	m_ghelp->Update();
	m_exit->Update();

	UpdateAnim();    //���¶�����;

	if (m_gstart->IsMouseEnter())             //���¡���ʼ��Ϸ��;
	{
		m_cgame->SetGameState(GAME_CHOOSECARD);
		ResetAnim();
	}
	if (m_gset->IsMouseEnter())               //���¡���Ϸ���á�;
	{
		m_cgame->SetGameState(GAME_SETING);   
		ResetAnim();
	}
	if (m_ghelp->IsMouseEnter())              //���¡���Ϸ������;
	{
		m_cgame->SetGameState(GAME_HELP);
		ResetAnim();
	}
	if (m_exit->IsMouseEnter())               //���¡��˳���;
	{
		m_cgame->SetGameState(GAME_EXIT);
	}
}

void CMainMenu::UpdateAnim()
{
	if (m_allowMoving)    //�����������ƶ�ʱ;
	{
		m_xanim += 8;
	}
	if ((m_xanim >= LastAnimX - 8) && (m_xanim <= LastAnimX))
	{
		m_hge->Effect_PlayEx(m_sndAnim, 100, 0, 1.0, false);  //������������׶�ʱ��������Ч;
	}
	if (m_xanim >= LastAnimX)  //��ʾ�����ƶ����;
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

void CMainMenu::ResetAnim()   //���ö������״̬��λ��;
{
	m_allowMoving = true;
	m_xanim = -800;
}
