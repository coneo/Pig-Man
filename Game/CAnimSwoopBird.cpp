#pragma 
#include"CAnimSwoopBird.h"

CAnimSwoopBird::CAnimSwoopBird()
{

}

CAnimSwoopBird::CAnimSwoopBird(HGE *_hge)
{   
	Height = 0;
	Width  = 0;
	isright = false;
	isleft  = false;
	view =false;
	m_hge = _hge;
	m_xposition = 500;
	m_yposition = 50;
	m_frame     = 12;
	m_fps       = 10;
	LoadTexture("¸©³åÄñ.png");
	SetImage(m_frame,m_fps,0,0,130,170);
	Play();
	//SetImage()
	X_speed    = 0;
	X_speed    = 0;
	dt1 = 0;
	dt2 = 0;
	m = 0;
	n= 0;
		sndbomb =m_hge->Effect_Load("±¬Õ¨.mp3");
}


CAnimSwoopBird::~CAnimSwoopBird()
{
	delete m_fly;
	m_hge->Texture_Free(m_tex);

}

void CAnimSwoopBird::Render()
{
	float dt = m_hge->Timer_GetDelta();
	//m_xposition += 1;
	
	m_fly->Render(m_xposition,m_yposition);
	m_fly->Update(dt);

}

void CAnimSwoopBird::Update()

{   
	
	m_xposition -=X_speed;
	if(view)
	{
	dt1 += m_hge->Timer_GetDelta();

		m_yposition  += 3*dt1;
 
		if(m_yposition>150&&m_yposition<465)
		{
			if(n==0){
				SetImage(11,20,0,0,130,170);
m_hge->Effect_PlayEx(sndbomb,10);
				Play();
				n = 1;
			}
			
		}
		if(m_yposition>=465)
		{
			if(m==0)
			{
				SetImage(11,10,0,689,272,171);
			//	m_hge->Effect_PlayEx(sndbomb,10);
				Play();
				m = 1;
			}
			if(m_yposition>475)
			{
				dt2 += m_hge->Timer_GetDelta();
				m_yposition = 475;

				
				if(dt2>0.8)
				{

					m_xposition =  1300;
					m_yposition =  50;
					view = false;
					n = m =0;
					
						SetImage(11,20,0,0,130,170);
						Play();
						dt1 = 0;
						dt2 = 0;
						view  = false;
				}
			}

				
		}

			
	
	}


}

void  CAnimSwoopBird::SetStase()
{
	view =   true;
}

bool CAnimSwoopBird::getStase()
{
	return view;
}

void CAnimSwoopBird::MoveFollowBgroud()
{
	if(m_xposition<1000)
	{
		if(isright)
		{
			X_speed = 4;
		}


		//m_xposition -= speed;
		if (m_hge->Input_GetKeyState( HGEK_RIGHT))
		{
			m_xposition -=X_speed;
			isright = true;
		}
	}
}


int CAnimSwoopBird::GetHeight()
{
	return Height;
}

int CAnimSwoopBird::GetWidth()
{
	return Width;
}