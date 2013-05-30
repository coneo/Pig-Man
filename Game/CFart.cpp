#include "CFart.h"

CFart::CFart()
{

}

CFart::CFart(HGE *_hge)
{
	m_vscale=1.0;
	m_hscale=1.0;                 //初始化缩放因子;
	m_ischanging=false;
	m_xposition=-400;
	m_yposition=-400;
	m_hge=_hge;
	m_speed =0;
	m_tex=m_hge->Texture_Load("EntityPic.png");
	//_spr=new hgeSprite(m_tex,1534,65,66,63);
	//_spr->SetBlendMode(BLEND_COLORMUL | BLEND_ALPHAADD | BLEND_NOZWRITE);
	//_spr->SetHotSpot(16,16);
	//par=new hgeParticleSystem("trail.psi",_spr);
	//par->info.nEmission=200;
	//par->Fire();
}

CFart::~CFart()
{
	delete par;
}

void CFart::Setspeed(float s)
{
	m_speed=s;
}

void CFart::SetHscale(float H)
{
	m_hscale=H;
}

void CFart::SetVscale(float V)
{
	m_vscale=V;
}

void CFart::SetChanging(bool B)
{
	m_ischanging=B;
}

bool CFart::GetChanging()
{
	return m_ischanging;
}

void CFart::boom()
{
	m_yposition -=m_speed;
	//m_spr->SetHotSpot(,550);
	m_spr->RenderEx(m_xposition,m_yposition,1.0,m_vscale,m_hscale);
	//par->Render();

}

void CFart::Chang()
{


	//par->MoveTo(GetPositionX(),GetPositionY());
	//par->SetScale(0.1);
	//par->Update(m_hge->Timer_GetDelta());
	if (m_ischanging==true)     
	{
		m_hscale=m_hscale+0.02;
		m_vscale=m_vscale+0.02;
		if (m_yposition>=332 && m_yposition <= 337)
		{
			SetPositionX(GetPositionX()+9.5);
			SetPositionY(GetPositionY()-13);
			m_hscale=1.1;
			m_vscale=1.1;
			SetTexture(167,514,118,109,true);
		}
		if (m_yposition>=27 && m_yposition <= 35)
		{
			SetPositionX(GetPositionX()+30);
			SetPositionY(GetPositionY()-60);
			SetTexture(877,1,126,123,true);
		}

	}
}

void CFart::SetTexture(float x,float y,float w,float h,bool t )
{
	m_spr->SetTextureRect( x, y, w, h, t);
}

