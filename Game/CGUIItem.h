#pragma once
#include <hge.h>
#include <hgefont.h>
#include <hgesprite.h>

class CGUIItem
{
public:
	CGUIItem(HGE  *_hge, char *filename, float _x, float _y, float _width, float _height);
	~CGUIItem();
	float        GetPositionX() const;      //获取物体的X坐标;
	float        GetPositionY() const;      //获取物体的Y坐标;
	void         SetPositionX(float _x);
	void         SetPositionY(float _y);
	void		 Update();      //更新菜单项;
	void		 Render();      //绘制菜单项;
	void		 MouseOver();   //当鼠标经过该菜单项时;
	bool         IsMouseEnter();   //鼠标左键是否按下;
	bool         TestPointIn(float _x, float _y);    //测试一个点是否在该菜单区域内;
private:
	CGUIItem();            //防止使用零参数的构造函数;
	HGE         *m_hge;

	hgeSprite   *m_spr;   //绘制菜单项的精灵;
	HTEXTURE     m_tex;   //绘制菜单项的纹理;

	hgeRect     *m_rect;        //菜单项的区域;
	bool         m_isMouseIn;   //鼠标是否在菜单区域内;
	float        m_xposition;   //菜单的X坐标;
	float        m_yposition;   //菜单的Y坐标;
	float		 m_x;           //纹理左上角坐标信息;
	float		 m_y;
	float		 m_width;       //纹理的长度和宽度;
	float		 m_height;
	
	float        m_xmouse;      //鼠标的X坐标;
	float        m_ymouse;      //鼠标的Y坐标;

	HEFFECT        m_sndButtonDone;     //按钮被按下的时候的音效;
};

