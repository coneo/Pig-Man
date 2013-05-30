/******************************************
该类是各种物体的基类，
比如：子弹、石头、鸡蛋、白云、以及其他的一些武器等
*******************************************/

#pragma once
#include <hge.h>
#include <hgesprite.h>

class CObjects
{
public:
	CObjects();
	CObjects(HGE *_hge);
	~CObjects();
	void		 LoadTexture(char*filename);
	void		 SetImage1( int x_positon, int y_position, int width, int height);
	void         SetImage(char* filename, int x_positon, int y_position, int width, int height);                //设置物体的图标;
	float        GetPositionX() const;      //获取物体的X坐标;
	float        GetPositionY() const;      //获取物体的Y坐标;
	void         SetPositionX(float _x);
	void         SetPositionY(float _y);
	void         Show();
protected:
	float        m_xposition;     //物体的X坐标;
	float        m_yposition;     //物体的Y坐标;

	HGE           *m_hge;
	hgeSprite     *m_spr;
	HTEXTURE       m_tex;          //头像图片;
};

