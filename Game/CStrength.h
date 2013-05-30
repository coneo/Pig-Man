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
	void    SetImage(char* filename, int x_positon, int y_position, int width, int height);    //�������ͷ��;
	void    Render();//��ͼƬ��ʾ����
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