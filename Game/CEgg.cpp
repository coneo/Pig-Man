#include "CEgg.h"


CEgg::CEgg()
{
}

CEgg::CEgg(HGE *_hge)
{
	m_hge = _hge;
	m_xposition = -200;
	m_yposition = -200;
	//m_speed = 0.1;
}

CEgg::~CEgg()
{
}

void CEgg::Show()
{
	m_yposition +=m_speed;
	m_spr->Render(m_xposition, m_yposition);
}

void CEgg::SetSpeed(float _speed)
{
	m_speed = _speed;
}