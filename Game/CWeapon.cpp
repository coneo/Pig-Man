#include "CWeapon.h"

CWeapon::CWeapon()
{
	//angle=0;
}

CWeapon::CWeapon(HGE *_hge)
{
	m_tex         =    0;
	m_hge         =    _hge;
	m_xposition   =    m_yposition = 1;
	angle         =    0;
	WeaponState   =    adjust;
	stength       =    7;
	Power         =    200;

}

CWeapon::~CWeapon()
{
	delete m_spr;
	m_hge->Texture_Free(m_tex);
}

void CWeapon::setInitState()
{
	Power   = 0;
	stength = 7;
}
void CWeapon::SetImage(char* filename, int x_positon, int y_position, int width, int height)
{
	m_tex         =    m_hge->Texture_Load( filename );
	m_spr		  =	   new hgeSprite(m_tex, x_positon, y_position, width, height);
	float x       =    m_spr->GetWidth()/2;
	float y		  =    m_spr->GetHeight()/2-10;
	m_spr		  ->   SetHotSpot(x,y);
}

float CWeapon::GetPositionX() const
{
	return m_xposition;
}

float CWeapon::GetPositionY() const
{
	return m_yposition;
}

float CWeapon::GetWidth()const
{
	float x=m_spr->GetWidth();
	return x;
}

float CWeapon::GetHeight()const
{
	float y=m_spr->GetHeight();
	return y;
}

float CWeapon::GetAngle()const
{
	return angle;
}

float CWeapon::GetStrength()const
{
	return stength;
}
float CWeapon::GetWeaponPower()const
{
 	return Power;
}

void CWeapon::SetPosition(float _x, float _y)
{
	m_xposition = _x;
	m_yposition = _y;
	int m=0;
}

void CWeapon::SetSpeedxy(float xspeed,float yspeed)
{
	x_speed=xspeed;
	y_speed=yspeed;
}

void CWeapon::Render()
{
	if(angle<-PI/2)
		angle=-PI/2;
	if(angle>0)
		angle=0;	
	m_spr->RenderEx(m_xposition, m_yposition,angle);
	float i=angle;
}

void CWeapon::Controle()
{
	if (m_hge->Input_GetKeyState(HGEK_SPACE))WeaponState     =shoot;
	if (m_hge->Input_GetKeyState(HGEK_A))    angle           =angle-0.01;
	if (m_hge->Input_GetKeyState(HGEK_D))    angle           =angle+0.01;
	if (m_hge->Input_GetKeyState(HGEK_Q))    stength         =stength+0.1;
    if (m_hge->Input_GetKeyState(HGEK_S)) 
	{
		Power                  =Power-2;
	    if (Power < 0)Power   =0;
	}
	if (m_hge->Input_GetKeyState(HGEK_W))    
	{
		Power                 =Power+2;
		if (Power > 1500)Power = 1500;
	}
	else
	{
		Power                 =Power-0.5;
		if (Power <= 0)Power   =0;
	}
}

void CWeapon::SetWeaponStateshoot()
{
	WeaponState=shoot;
}
void CWeapon::SetWeaponStateadjust()
{
	WeaponState=adjust;
	//stength=7;
}
void CWeapon::SetWeaponStateIntial()
{
	stength=0;
	WeaponState=Initial;
}

float CWeapon::GetWeaponState()const
{
	return WeaponState;
}
float CWeapon::GetPositionShootX()const
{
	// (NewWeapon->GetPositionX()+(NewWeapon->GetWidth()/2)*cos(abs((NewWeapon->GetAngle()))
	return   m_xposition+(m_spr->GetWidth()/2*cos(abs(angle)));
}
float CWeapon::GetPositionShootY()const
{
	// NewWeapon->GetPositionY()-(NewWeapon->GetWidth()/2)*sin(abs((NewWeapon->GetAngle()))))
	return m_yposition-(m_spr->GetHeight()/2)*sin(abs(angle));
}