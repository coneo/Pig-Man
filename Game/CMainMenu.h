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
	//void  LoadTexture(char *filename);         //加载该GUI的所有纹理;
	void  Init();               //初始化界面;
	void  Update();             //界面的逻辑控制;
	void  Render();             //绘制界面;
	void  UpdateAnim();         //更新动画;
	void  ResetAnim();          //重置动画;
private:
	hgeSprite     *m_bk;       //绘制背景图的精灵;
	HTEXTURE       m_bktex;    //背景图纹理;

	hgeSprite	  *m_anim;      //动态图像的精灵;
	HTEXTURE	   m_animtex;  
	float		   m_xanim;     //绘制动画的屏幕X,Y坐标;
	float		   m_yanim;
	bool		   m_allowMoving;  //是否允许动画猪移动，当小猪移动完之后就不能移动;
	HEFFECT		   m_sndAnim;   //动画猪的音效;

	CGUIItem      *m_gstart;    //“开始游戏”选项;
	CGUIItem	  *m_gset;      //“游戏设置”选项;
	CGUIItem	  *m_ghelp;     //“游戏帮助”选项;
	CGUIItem	  *m_exit;      //“退出”选项;

	CGame         *m_cgame;     //由于要更改游戏状态，故需要一个cgame的指针;
};

#endif