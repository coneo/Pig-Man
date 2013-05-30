/******************************************
�����Ǹ�������Ļ��࣬
���磺�ӵ���ʯͷ�����������ơ��Լ�������һЩ������
*******************************************/

#pragma once
#include <hge.h>
#include <hgesprite.h>

class CObjects
{
public:
	CObjects();
	CObjects(HGE *_hge);
	~CObjects();
	void		 LoadTexture(char*filename);
	void		 SetImage1( int x_positon, int y_position, int width, int height);
	void         SetImage(char* filename, int x_positon, int y_position, int width, int height);                //���������ͼ��;
	float        GetPositionX() const;      //��ȡ�����X����;
	float        GetPositionY() const;      //��ȡ�����Y����;
	void         SetPositionX(float _x);
	void         SetPositionY(float _y);
	void         Show();
protected:
	float        m_xposition;     //�����X����;
	float        m_yposition;     //�����Y����;

	HGE           *m_hge;
	hgeSprite     *m_spr;
	HTEXTURE       m_tex;          //ͷ��ͼƬ;
};

