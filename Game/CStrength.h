#ifndef CSTRENGTH
#define CSTRENGTH
#include"CObjectState.h"
#include "CStrength.h"
class CStrength
{
public:
	CStrength();
	CStrength(HGE *hge);
	~CStrength();
	void    SetImage(char* filename, int x_positon, int y_position, int width, int height);    //设置鸟的头像;
	void    Render();//将图片显示出来
	void    SetLength(float Length);
	void    SetStrengthStatechange();
	void    SetStrengthStateIntial();
	float    GetStrengthState();
private:
	HGE *m_hge;	
	hgeSprite *m_spr;
	HTEXTURE m_tex;
	float length;
	ObjectState StrengthState;

};
#endif