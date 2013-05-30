#include "CBird.h"


CBird::CBird()
{
	/*
	2.生命值的确定
	3.*/
}

CBird::CBird(HGE *_hge)
{
	m_hge  = _hge;
	m_life = 1;      //初始化鸟有1条生命;
	m_xposition = m_yposition = 1;
}

CBird::~CBird()
{
	delete m_spr;
	m_hge->Texture_Free(m_tex);
}

void CBird::SetImage(char* filename, int x_positon, int y_position, int width, int height)
{
	m_tex = m_hge->Texture_Load( filename );
	m_spr = new hgeSprite(m_tex, x_positon, y_position, width, height);
}

float CBird::GetPositionX() const
{
	return m_xposition;
}

float CBird::GetPositionY() const
{
	return m_yposition;
}

void CBird::SetPositionX(float _x)
{
	m_xposition = _x;
}

void CBird::SetPositionY(float _y)
{
	m_yposition = _y;
}