#pragma once
#include <hge.h>
#include "CGUI.h"
#include "CGUIItem.h"

#ifndef C_HELP
#define	C_HELP

class CGame;

class CHelp : public CGUI
{
public:
	CHelp(HGE *_hge, CGame *_game);
	~CHelp();
	void	Init();     //��ʼ��;
	void	Update();   //����;
	void	Render();   //����;
private:
	CHelp();
	hgeSprite     *m_bk;       //���Ʊ���ͼ�ľ���;
	HTEXTURE       m_bktex;    //����ͼ����;

	CGUIItem	  *m_battle1_info;  //ģʽһ����;
	CGUIItem	  *m_battle2_info;  //ģʽ������;
	CGUIItem      *m_battle3_info;  //ģʽ������;
	CGUIItem      *m_return;       //�����ء��˵�;

	CGame         *m_cgame;     //����Ҫ������Ϸ״̬������Ҫһ��cgame��ָ��;
};

#endif