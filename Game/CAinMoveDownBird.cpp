#pragma 
#include"CAnimMoveDownBird.h"

CAnimMoveDownBird::CAnimMoveDownBird()
{

}

CAnimMoveDownBird::CAnimMoveDownBird(HGE *_hge)
{   

	Height = 0;
	Width  = 0;
	isright = false;
	isleft  = false;
	flage = true;
	m_hge = _hge;
	m_xposition = 1200;
	m_yposition = 50;
	m_frame     = 4;
	m_fps       = 10;
	LoadTexture("Ð¡Äñ.png");
	SetImage(m_frame,m_fps,0,0,56,43);
	Play();
	//SetImage()
	X_speed    = 0;
	X_speed    = 0;
	dt1 = 0;
	dt2 = 0;
	m = 0;
	n= 0;
}


CAnimMoveDownBird::~CAnimMoveDownBird()
{
	delete m_fly;
	m_hge->Texture_Free(m_tex);

}

void CAnimMoveDownBird::Render()
{
	float dt = m_hge->Timer_GetDelta();
	//m_xposition += 1;

	m_fly->Render(m_xposition,m_yposition);
	m_fly->Update(dt);

}

void CAnimMoveDownBird::Update()

{   

	m_xposition -=X_speed;
	if(flage)
	m_yposition  += Y_speed;

	if(m_yposition >700)
		flage = false;
	if(!flage)
		m_yposition -=5;
	if(m_yposition<=1)
	flage = true;
	

}

void  CAnimMoveDownBird::SetStase()
{
	flage =   true;
}

bool CAnimMoveDownBird::getStase()
{
	return flage;
}

void CAnimMoveDownBird::MoveFollowBgroud()
{

	if(m_xposition<1000)
	{
		if(isright)
		{
			X_speed = 4;
		}
		if (isleft)
		{
			X_speed = 1;
		}

		if (m_hge->Input_GetKeyState( HGEK_RIGHT))
		{


			isright = true;
			m_xposition -=X_speed;
		}
		if (m_hge->Input_GetKeyState( HGEK_LEFT))
		{

			isleft = true;
			m_xposition +=X_speed;

		}
	}
}

int CAnimMoveDownBird::GetHeight()
{
	return Height;
}

int CAnimMoveDownBird::GetWidth()
{
	return Width;
}