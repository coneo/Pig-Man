#include "CObjects.h"


CObjects::CObjects()
{
}

CObjects::CObjects(HGE *_hge)
{
	m_hge = _hge;
}

CObjects::~CObjects()
{
	delete m_spr;
	m_hge->Texture_Free(m_tex);
}

void CObjects::LoadTexture(char*filename)
{   
	m_tex = m_hge->Texture_Load(filename );
}
void CObjects::SetImage1( int x_positon, int y_position, int width, int height)
{

	m_spr = new hgeSprite(m_tex, x_positon, y_position, width, height);
}

void CObjects::SetImage(char* filename, int x_positon, int y_position, int width, int height)
{
	m_tex = m_hge->Texture_Load( filename );
	m_spr = new hgeSprite(m_tex, x_positon, y_position, width, height);
}

float CObjects::GetPositionX() const
{
	return m_xposition;
}

float CObjects::GetPositionY() const
{
	return m_yposition;
}

void CObjects::SetPositionX(float _x)
{
	m_xposition = _x;
}

void CObjects::SetPositionY(float _y)
{
	m_yposition = _y;
}

void CObjects::Show()
{
	m_spr->Render(m_xposition, m_yposition);
}