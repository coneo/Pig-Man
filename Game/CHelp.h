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
	void	Init();     //初始化;
	void	Update();   //更新;
	void	Render();   //绘制;
private:
	CHelp();
	hgeSprite     *m_bk;       //绘制背景图的精灵;
	HTEXTURE       m_bktex;    //背景图纹理;

	CGUIItem	  *m_battle1_info;  //模式一介绍;
	CGUIItem	  *m_battle2_info;  //模式二介绍;
	CGUIItem      *m_battle3_info;  //模式三介绍;
	CGUIItem      *m_return;       //“返回”菜单;

	CGame         *m_cgame;     //由于要更改游戏状态，故需要一个cgame的指针;
};

#endif