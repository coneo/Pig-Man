#include "CGUIItem.h"


CGUIItem::CGUIItem()
{
}

CGUIItem::CGUIItem(HGE *_hge, char *filename, float _x, float _y, float _width, float _height)
{
	m_hge = _hge;
	m_tex = m_hge->Texture_Load(filename);  //�������;
	m_spr = new hgeSprite(m_tex, _x, _y, _width, _height);
	m_xposition = m_yposition = 0.0;		//��ʼ���˵��������;

	m_x = _x;
	m_y = _y;
	m_width = _width;
	m_height = _height;

	//m_xmouse = m_ymouse = 0.0;            //��ʼ�����λ��;
	m_rect = new hgeRect();                  //��ʼ��m_rect;
	m_isMouseIn = false;                   //��ʼʱ����겻��������;

	m_sndButtonDone = m_hge->Effect_Load("menuSelect1.wav");  //��ť��Ч;
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

void CGUIItem::Update()   //�߼�����,ʵ�ֲ˵���Ķ�̬Ч��;
{
	m_spr->GetBoundingBox(m_xposition, m_yposition, m_rect);   //��ȡ�˵���İ�Χ��;
	m_hge->Input_GetMousePos(&m_xmouse, &m_ymouse);           //���ϻ�ȡ���λ��;
	if (m_rect->TestPoint(m_xmouse, m_ymouse) && (m_isMouseIn == false))      //�������ڲ˵�������;
	{
// 		m_xmouse += 5;
// 		m_yposition -= 5;
		//m_spr->SetColor(ARGB(0, 0, 0));
		m_hge->Effect_Play(m_sndButtonDone);     //���Ű�����Ч;
		m_spr->SetTextureRect(m_width, m_y, m_width, m_height);
		m_isMouseIn = true;
	}
	else if(!m_rect->TestPoint(m_xmouse, m_ymouse) && (m_isMouseIn == true))  //����Ƴ�����;
	{
// 		m_xposition -=5;
// 		m_yposition += 5;
		m_spr->SetTextureRect(m_x, m_y, m_width, m_height);
		m_isMouseIn = false;
	}
		
	//MouseOver();
}

void CGUIItem::Render()   //����;
{
	m_spr->Render(m_xposition, m_yposition);
}

void CGUIItem::MouseOver() //��꾭���˵���;
{
	if (m_isMouseIn)    //�������ڲ˵�������;
	{

	}
	m_xposition += 5;
	m_yposition -= 5;
}

bool CGUIItem::IsMouseEnter()
{
	if (m_rect->TestPoint(m_xmouse, m_ymouse) && m_hge->Input_GetKeyState(HGEK_LBUTTON))   //�������������;
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