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
	void	Init();        //初始化;
	void	Update();      //更新;
	void	Render();      //绘制;
private:
	CLoading();
	HGE		   *m_hge;

	hgeSprite  *m_bk;        //绘制背景图的精灵;
	HTEXTURE	m_bktex;     //绘制背景图的纹理;

	hgeSprite  *m_load;   //绘制进度条的精灵;
	HTEXTURE    m_loadtex;   //绘制进度条的纹理;

	float	    m_WidthOfLod;     //进度条的X坐标;
	CGame	   *m_cgame;       //需要更新游戏的状态，故需要此CGame;
};

#endif