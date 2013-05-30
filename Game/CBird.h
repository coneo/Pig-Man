/**************************************************************
该类是各种鸟的基类，在该类中，抽象出所有鸟的共性，
包括：鸟的头像设置（SetImage）、鸟的坐标（m_xposition,m_yposition）
     获取鸟的位置（GetPositioin）、设置鸟的位置（SetPosition）
	 鸟的生命值（m_life）

 在鸟的成员中，m_spr是核心，加载鸟的头像需要它，鸟的移动需要它
 ***************************************************************/

#pragma once
#include <hge.h>
#include <hgesprite.h>
#include <string>

class CBird
{
public:
	CBird();
	CBird(HGE *_hge);
	~CBird();             
	                 //x_position，y_position分别表示要加载的图片的左上角位置， width和height表示图片的宽度和高度;
	void    SetImage(char* filename, int x_positon, int y_position, int width, int height);    //设置鸟的头像;
	virtual void    Update() = 0;             //逻辑;
	virtual void    Fly() = 0;                //绘制;
	float   GetPositionX() const;    //取得鸟的X坐标;
	float   GetPositionY() const;
	void    SetPositionX(float _x);
	void    SetPositionY(float _y);
	//virtual void    Attack();
	//virtual void    SetSpeed(float _speed);
protected:
	int               m_life;          //鸟的生命值;
	float             m_xposition;     //鸟的X坐标;
	float             m_yposition;     //鸟的Y坐标;

	HGE              *m_hge;
	hgeSprite        *m_spr;
	HTEXTURE          m_tex;           //头像图片;
};

