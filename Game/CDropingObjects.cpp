#include "CDropingObjects.h"


CDropingObjects::CDropingObjects(void)
{
}


CDropingObjects::~CDropingObjects(void)
{
}

void CDropingObjects::TextureLoad(char *filename)
{
	m_tex = m_hge->Texture_Load(filename);
}

void CDropingObjects::SetTexture(int x_pos, int y_pos, int _width, int _height)
{
	m_spr = new hgeSprite(m_tex, x_pos, y_pos, _width, _height);
// 	if ()      //如果.....那么是物品XX;
// 	{
// 	}
}