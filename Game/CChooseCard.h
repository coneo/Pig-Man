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
	void    Init();        //初始化;
	void    Update();      //更新;
	void    Render();      //绘制;
private:
	CChooseCard();
	hgeSprite     *m_bk;       //绘制背景图的精灵;
	HTEXTURE       m_bktex;    //背景图纹理;

	CGUIItem      *m_battle1;    //“模式一”选项;
	CGUIItem      *m_battle2;    //“模式二”选项;
	CGUIItem      *m_battle3;    //“模式三”选项;
	CGUIItem      *m_return;       //“返回”菜单;

	CGame         *m_cgame;     //由于要更改游戏状态，故需要一个cgame的指针;
};

