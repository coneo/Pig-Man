#pragma once
#ifndef C_LOADING
#define C_LOADING
#include <hge.h>
#include <hgesprite.h>

class CGame;

class CLoading
{
public:
	CLoading(HGE *_hge, CGame *_game);
	~CLoading();
	void	Init();        //��ʼ��;
	void	Update();      //����;
	void	Render();      //����;
private:
	CLoading();
	HGE		   *m_hge;

	hgeSprite  *m_bk;        //���Ʊ���ͼ�ľ���;
	HTEXTURE	m_bktex;     //���Ʊ���ͼ������;

	hgeSprite  *m_load;   //���ƽ������ľ���;
	HTEXTURE    m_loadtex;   //���ƽ�����������;

	float	    m_WidthOfLod;     //��������X����;
	CGame	   *m_cgame;       //��Ҫ������Ϸ��״̬������Ҫ��CGame;
};

#endif