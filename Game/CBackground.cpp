#include "CBackground.h"

CBackground::CBackground()
{

}

CBackground::CBackground(HGE* _hge)
{  

	m_hge = _hge;
	m_xposition = 0;
	m_yposition = 0;
	speed = 0.5;
	isright =  true;

}


void CBackground::control()
{   
	if(isright)
	{
		speed = speed;
	}
	else
		speed = - speed;

	m_xposition -= speed;
	if (m_hge->Input_GetKeyState( HGEK_RIGHT))
	{
		
		m_xposition -=4;
		isright = true;
	}
	if (m_hge->Input_GetKeyState( HGEK_LEFT))
	{
		m_xposition +=1;
		isright = false;
	}
}


void CBackground::move()
{
 m_spr->Render(m_xposition,m_yposition);
//m_spr->Render(m_xposition,m_yposition);
}



void CBackground::setspeed(float a)
{
	speed = a;
}

float CBackground::getspeed()
{
	return speed;
}

bool CBackground::getisright()
	{
		return   isright;
	}
CBackground::~CBackground()
{
	m_hge->Release();
	m_hge->System_Shutdown();

}
