#include"CStrength.h"

CStrength::CStrength()
{

}
CStrength::CStrength(HGE *hge)
{
	m_hge=hge;
	length=0.001;
	StrengthState=Intial;
}
CStrength:: ~CStrength()
{
}
void CStrength::SetImage(char* filename, int x_positon, int y_position, int width, int height)
{
	m_tex = m_hge->Texture_Load( filename );
	m_spr = new hgeSprite(m_tex, x_positon, y_position, width, height);
}
void CStrength::Render()
{
	if(length>140)length=140;
	m_spr->RenderStretch(100,650,100+length,675);
}
void CStrength::SetLength(float Length)
{
	length=Length;
}
void CStrength::SetStrengthStatechange()
{
	
	StrengthState=change;
}
void CStrength::SetStrengthStateIntial()
{
	length=0;
	StrengthState=Intial;

}
float CStrength::GetStrengthState()
{
	return StrengthState;
}