#include "CBullet1.h"

CBullet1::CBullet1(HGE *_hge)
{
	m_hge=_hge;
	m_xposition=-200;
	m_yposition=-200;
	m_speed=0;
	m_hge = _hge;
}

CBullet1::~CBullet1()
{

}

void CBullet1::SetSpeed(float S)
{
	m_speed=S;
}

void CBullet1::Update()
{
	m_yposition -= m_speed;
}

void CBullet1::Show()
{
	m_spr->RenderEx(m_xposition, m_yposition, 0, 0.7, 0.7);
}