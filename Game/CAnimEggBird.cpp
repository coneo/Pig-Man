#include "CAnimEggBird.h"

CAnimEggBird::CAnimEggBird()
{

}

CAnimEggBird::CAnimEggBird(HGE *_hge)
{

	Height = 0;
	Width  = 0;
	isright = false;
	isleft  = false;
	m_hge = _hge;
    m_xposition = 1200;
	m_yposition = 20;
	X_speed = 0;
	Y_speed = 0;
    m_fps   = 0;
	m_frame = 0;
}

void CAnimEggBird::Render()
{

float dt = m_hge->Timer_GetDelta();

m_fly->Render(m_xposition, m_yposition);

m_fly->Update(dt);

}

void  CAnimEggBird::Update() 
{
    m_xposition -= X_speed;

	
}

void CAnimEggBird::MoveFollowBgroud()
{
	if(m_xposition<1000)
	{
		if(isright)
		{
			X_speed = 4;
		}
// 		if (isleft)
// 		{
// 			X_speed = 1;
// 		}


		//m_xposition -= speed;
		if (m_hge->Input_GetKeyState( HGEK_RIGHT))
		{

			m_xposition -=X_speed;
			isright = true;
		}
// 		if (m_hge->Input_GetKeyState( HGEK_LEFT))
// 		{
// 			m_xposition +=X_speed;
// 			isleft = true;
// 		}
	}
}

int CAnimEggBird::GetHeight()
{
	return  Height;
}

int CAnimEggBird::GetWidth()
{
	return Width;
}