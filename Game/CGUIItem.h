#pragma once
#include <hge.h>
#include <hgefont.h>
#include <hgesprite.h>

class CGUIItem
{
public:
	CGUIItem(HGE  *_hge, char *filename, float _x, float _y, float _width, float _height);
	~CGUIItem();
	float        GetPositionX() const;      //��ȡ�����X����;
	float        GetPositionY() const;      //��ȡ�����Y����;
	void         SetPositionX(float _x);
	void         SetPositionY(float _y);
	void		 Update();      //���²˵���;
	void		 Render();      //���Ʋ˵���;
	void		 MouseOver();   //����꾭���ò˵���ʱ;
	bool         IsMouseEnter();   //�������Ƿ���;
	bool         TestPointIn(float _x, float _y);    //����һ�����Ƿ��ڸò˵�������;
private:
	CGUIItem();            //��ֹʹ��������Ĺ��캯��;
	HGE         *m_hge;

	hgeSprite   *m_spr;   //���Ʋ˵���ľ���;
	HTEXTURE     m_tex;   //���Ʋ˵��������;

	hgeRect     *m_rect;        //�˵��������;
	bool         m_isMouseIn;   //����Ƿ��ڲ˵�������;
	float        m_xposition;   //�˵���X����;
	float        m_yposition;   //�˵���Y����;
	float		 m_x;           //�������Ͻ�������Ϣ;
	float		 m_y;
	float		 m_width;       //����ĳ��ȺͿ��;
	float		 m_height;
	
	float        m_xmouse;      //����X����;
	float        m_ymouse;      //����Y����;

	HEFFECT        m_sndButtonDone;     //��ť�����µ�ʱ�����Ч;
};

