#pragma once
#ifndef C_MAINMENU
#define C_MAINMENU

#include <hgesprite.h>
#include <hgefont.h>
#include "CGUI.h"
#include "CGUIItem.h"

class CGame;

class CMainMenu : public CGUI
{
public:
	CMainMenu(HGE* _hge, CGame *_game);
	~CMainMenu();
	//void  LoadTexture(char *filename);         //���ظ�GUI����������;
	void  Init();               //��ʼ������;
	void  Update();             //������߼�����;
	void  Render();             //���ƽ���;
	void  UpdateAnim();         //���¶���;
	void  ResetAnim();          //���ö���;
private:
	hgeSprite     *m_bk;       //���Ʊ���ͼ�ľ���;
	HTEXTURE       m_bktex;    //����ͼ����;

	hgeSprite	  *m_anim;      //��̬ͼ��ľ���;
	HTEXTURE	   m_animtex;  
	float		   m_xanim;     //���ƶ�������ĻX,Y����;
	float		   m_yanim;
	bool		   m_allowMoving;  //�Ƿ����������ƶ�����С���ƶ���֮��Ͳ����ƶ�;
	HEFFECT		   m_sndAnim;   //���������Ч;

	CGUIItem      *m_gstart;    //����ʼ��Ϸ��ѡ��;
	CGUIItem	  *m_gset;      //����Ϸ���á�ѡ��;
	CGUIItem	  *m_ghelp;     //����Ϸ������ѡ��;
	CGUIItem	  *m_exit;      //���˳���ѡ��;

	CGame         *m_cgame;     //����Ҫ������Ϸ״̬������Ҫһ��cgame��ָ��;
};

#endif