#pragma once
#include <hgesprite.h>
#include "CGUI.h"
#include "CGUIItem.h"

class CGame;

class CGameOver : public CGUI
{
public:
	CGameOver(HGE *_hge, CGame* _game);
	~CGameOver();
	void	Init();		  //��ʼ��;
	void	Update();     //����;
	void	Render();     //����;
private:
	CGameOver();
	CGame    *m_cgame;    //����Ҫ������Ϸ״̬������Ҫһ��cgame��ָ��;

	hgeSprite     *m_bk;       //���Ʊ���ͼ�ľ���;
	HTEXTURE       m_bktex;    //����ͼ����;

	CGUIItem	  *m_returnToMainMenu;  //�������˵�;
};

