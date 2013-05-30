/**************************************************************
�����Ǹ�����Ļ��࣬�ڸ����У������������Ĺ��ԣ�
���������ͷ�����ã�SetImage����������꣨m_xposition,m_yposition��
     ��ȡ���λ�ã�GetPositioin�����������λ�ã�SetPosition��
	 �������ֵ��m_life��

 ����ĳ�Ա�У�m_spr�Ǻ��ģ��������ͷ����Ҫ��������ƶ���Ҫ��
 ***************************************************************/

#pragma once
#include <hge.h>
#include <hgesprite.h>
#include <string>

class CBird
{
public:
	CBird();
	CBird(HGE *_hge);
	~CBird();             
	                 //x_position��y_position�ֱ��ʾҪ���ص�ͼƬ�����Ͻ�λ�ã� width��height��ʾͼƬ�Ŀ�Ⱥ͸߶�;
	void    SetImage(char* filename, int x_positon, int y_position, int width, int height);    //�������ͷ��;
	virtual void    Update() = 0;             //�߼�;
	virtual void    Fly() = 0;                //����;
	float   GetPositionX() const;    //ȡ�����X����;
	float   GetPositionY() const;
	void    SetPositionX(float _x);
	void    SetPositionY(float _y);
	//virtual void    Attack();
	//virtual void    SetSpeed(float _speed);
protected:
	int               m_life;          //�������ֵ;
	float             m_xposition;     //���X����;
	float             m_yposition;     //���Y����;

	HGE              *m_hge;
	hgeSprite        *m_spr;
	HTEXTURE          m_tex;           //ͷ��ͼƬ;
};

