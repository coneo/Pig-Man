#pragma once
#include <hgesprite.h>
#include "CGUI.h"
#include "CGUIItem.h"

class CGame;

class CSeting : public CGUI
{
public:
	CSeting(HGE *_hge, CGame *_game);
	~CSeting();
	void	Init();         //��ʼ��;
	void	Update();		//����;
	void	Render();		//����;
private:
	CSeting();
	hgeSprite     *m_bk;       //���Ʊ���ͼ�ľ���;
	HTEXTURE       m_bktex;    //����ͼ����;

	CGUIItem      *m_return;       //�����ء��˵�;
	CGUIItem	  *m_seting;       //����;

	CGame         *m_cgame;     //����Ҫ������Ϸ״̬������Ҫһ��cgame��ָ��;
};

