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
	void	Init();         //初始化;
	void	Update();		//更新;
	void	Render();		//绘制;
private:
	CSeting();
	hgeSprite     *m_bk;       //绘制背景图的精灵;
	HTEXTURE       m_bktex;    //背景图纹理;

	CGUIItem      *m_return;       //“返回”菜单;
	CGUIItem	  *m_seting;       //设置;

	CGame         *m_cgame;     //由于要更改游戏状态，故需要一个cgame的指针;
};

