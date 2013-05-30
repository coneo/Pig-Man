#include "CAnimDragon.h"

CAnimDragon::CAnimDragon()
{

}

CAnimDragon::CAnimDragon(HGE *_hge)
{

	Height = 0;
	Width  = 0;
	isright = false;
	isleft  = false;
	view =false;
	m_hge = _hge;
	m_xposition = 1200;
	m_yposition = 50;
	m_frame     = 18;
	m_fps       = 10;
	LoadTexture("Бъ.png");
	SetImage(m_frame,m_fps,0,1,288,173);
	Play();
	//SetImage()
	X_speed    = 0;
	X_speed    = 0;
	dt1 = 0;
	dt2 = 0;
	m = 0;
	n= 0;

}

CAnimDragon::~CAnimDragon()
{
	delete m_fly;
	m_hge->Texture_Free(m_tex);

}

void CAnimDragon::Render()
{
	float dt = m_hge->Timer_GetDelta();
	//m_xposition += 1;

	m_fly->Render(m_xposition,m_yposition);
	m_fly->Update(dt);

}

void CAnimDragon::Update()

{   

	m_xposition -=X_speed;
	if(view)
	{
		dt1 += m_hge->Timer_GetDelta();

		m_yposition  += 3*dt1;

// 		if(m_yposition>150&&m_yposition<580)
// 		{
// 			if(n==0){
// 
// 				SetImage(18,10,0,1,288,173);
// 				Play();
// 				n = 1;
// 
// 
// 			}
//
//		}
		if(m_yposition>=495)
		{

		
				dt2 += m_hge->Timer_GetDelta();
				m_yposition = 495;

				if(dt2>30)
				{

					m_xposition =  1300;
					m_yposition =  50;
					view = false;
					n = m =0;
					SetImage(18,10,0,1,288,173);
					Play();
					dt1 = 0;
					dt2 = 0;
					view  = false;
			}


		}



	}
}

void CAnimDragon::MoveFollowBgroud()
{
	if(m_xposition<1000)
	{
		if(isright)
		{
			X_speed = 4;
		}
		


		if (m_hge->Input_GetKeyState( HGEK_RIGHT))
		{


			isright = true;
			m_xposition -=X_speed;
		}
	
	}
}

int CAnimDragon::GetHeight()
{
	return Height;
}

int CAnimDragon::GetWidth()
{
	return Width;
}