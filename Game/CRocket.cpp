#include "CRocket.h"


CRocket::CRocket(HGE *_hge)
{
	this->m_xposition = 10000.0;
	this->m_yposition = 10000.0;
	m_speed = 0.0;
	m_isReady = false;
	m_hge = _hge;

	m_partex = m_hge->Texture_Load("particles.png");  //��������������ϵͳ;
	m_pspr = new hgeSprite(m_partex, 96, 64, 30, 30);
	m_pspr->SetBlendMode(BLEND_COLORMUL | BLEND_ALPHAADD | BLEND_NOZWRITE);
	m_pspr->SetHotSpot(16,16);
	m_par = new hgeParticleSystem("trail.psi", m_pspr);    
	m_par->Fire();  
}


CRocket::~CRocket()
{
	delete    m_par;
	delete    m_pspr;
	m_hge->Texture_Free(m_partex);
}

void CRocket::SetSpeed(float _speed)
{
	m_speed = _speed;
}

void CRocket::SetReady()
{
	m_isReady = true;
}

void CRocket::SetUnReady()
{
	m_isReady = false;
}

void CRocket::Update()
{
	if (m_isReady)
	{
		if (m_speed <= 1.5)        //���ƻ�����ٶ�;
			m_speed += 0.05;
		else
			m_speed += 3;
	}

	m_yposition -= m_speed;

		//�����ը������Ч��;
	m_par->info.nEmission = 50;
	m_par->MoveTo(GetPositionX()+33, GetPositionY()+55);
	m_par->Update(m_hge->Timer_GetDelta());
}

void CRocket::Show()
{
	m_spr->Render(m_xposition, m_yposition);
	m_par->Render();                           //��������ϵͳ;

}