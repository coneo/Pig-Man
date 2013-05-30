#pragma once
#include "CGUI.h"
#include <hgesprite.h>
#include "CGUIItem.h"

class CGame;

class CChooseCard : public CGUI
{
public:
	CChooseCard(HGE *_hge, CGame *_game);
	~CChooseCard();
	void    Init();        //��ʼ��;
	void    Update();      //����;
	void    Render();      //����;
private:
	CChooseCard();
	hgeSprite     *m_bk;       //���Ʊ���ͼ�ľ���;
	HTEXTURE       m_bktex;    //����ͼ����;

	CGUIItem      *m_battle1;    //��ģʽһ��ѡ��;
	CGUIItem      *m_battle2;    //��ģʽ����ѡ��;
	CGUIItem      *m_battle3;    //��ģʽ����ѡ��;
	CGUIItem      *m_return;       //�����ء��˵�;

	CGame         *m_cgame;     //����Ҫ������Ϸ״̬������Ҫһ��cgame��ָ��;
};

