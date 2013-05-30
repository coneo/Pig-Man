#include "CGUIItem.h"


CGUIItem::CGUIItem()
{
}

CGUIItem::CGUIItem(HGE *_hge, char *filename, float _x, float _y, float _width, float _height)
{
	m_hge = _hge;
	m_tex = m_hge->Texture_Load(filename);  //纹理加载;
	m_spr = new hgeSprite(m_tex, _x, _y, _width, _height);
	m_xposition = m_yposition = 0.0;		//初始化菜单项的坐标;

	m_x = _x;
	m_y = _y;
	m_width = _width;
	m_height = _height;

	//m_xmouse = m_ymouse = 0.0;            //初始化鼠标位置;
	m_rect = new hgeRect();                  //初始化m_rect;
	m_isMouseIn = false;                   //初始时，鼠标不在区域内;

	m_sndButtonDone = m_hge->Effect_Load("menuSelect1.wav");  //按钮音效;
}

CGUIItem::~CGUIItem()
{
	delete   m_spr;
	delete   m_rect;
	m_hge->Texture_Free(m_tex);
	m_hge->Effect_Free(m_sndButtonDone);
}

float CGUIItem::GetPositionX() const
{
	return m_xposition;
}

float CGUIItem::GetPositionY() const
{
	return m_yposition;
}

void CGUIItem::SetPositionX(float _x)
{
	m_xposition = _x;
}

void CGUIItem::SetPositionY(float _y)
{
	m_yposition = _y;
}

void CGUIItem::Update()   //逻辑控制,实现菜单项的动态效果;
{
	m_spr->GetBoundingBox(m_xposition, m_yposition, m_rect);   //获取菜单项的包围盒;
	m_hge->Input_GetMousePos(&m_xmouse, &m_ymouse);           //不断获取鼠标位置;
	if (m_rect->TestPoint(m_xmouse, m_ymouse) && (m_isMouseIn == false))      //如果鼠标在菜单区域内;
	{
// 		m_xmouse += 5;
// 		m_yposition -= 5;
		//m_spr->SetColor(ARGB(0, 0, 0));
		m_hge->Effect_Play(m_sndButtonDone);     //播放按键音效;
		m_spr->SetTextureRect(m_width, m_y, m_width, m_height);
		m_isMouseIn = true;
	}
	else if(!m_rect->TestPoint(m_xmouse, m_ymouse) && (m_isMouseIn == true))  //鼠标移出区域;
	{
// 		m_xposition -=5;
// 		m_yposition += 5;
		m_spr->SetTextureRect(m_x, m_y, m_width, m_height);
		m_isMouseIn = false;
	}
		
	//MouseOver();
}

void CGUIItem::Render()   //绘制;
{
	m_spr->Render(m_xposition, m_yposition);
}

void CGUIItem::MouseOver() //鼠标经过菜单项;
{
	if (m_isMouseIn)    //如果鼠标在菜单区域内;
	{

	}
	m_xposition += 5;
	m_yposition -= 5;
}

bool CGUIItem::IsMouseEnter()
{
	if (m_rect->TestPoint(m_xmouse, m_ymouse) && m_hge->Input_GetKeyState(HGEK_LBUTTON))   //检测鼠标左键按下;
		return true;
	else
		return false;
}

bool CGUIItem::TestPointIn(float _x, float _y)
{
// 	if ()
// 	{
// 	}
	return true;
}