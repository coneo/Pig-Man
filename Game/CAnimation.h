#pragma once
#include <hge.h>
#include <hgeanim.h>
#include <cmath>
#include "CGlobal.h"


enum Direction{RIGHT ,LEFTE};
enum State{UNATTACK,ATTACKING,ATTACKED,GROUDN_FIRING};
/*enum Color{RED,GREEN,BLUE};*/ //�ŵ�Global�У���Ϊ��ҲҪ�õ�



struct Position
{
	Position()
	{
		x = 0;
		y = 0;
	}
	;
	Position(double _x,double _y)
	{
		x = _x;
		y = _y;
	};
	double x;
	double y;

};

class CAnimation
{
public:
	CAnimation(void);
	CAnimation(HGE* _hge,
		char* filename,
		Position _tex_position,
		int _weidth_tex,int _height_tex,
		int _frame,int _FPS);
	void Play(int playmode,
			Position _screen_position,
			double _x_speed,double _y_speed);
	void Fly();
	void Update(float deltatime);

	//ȡ�õ�ǰ���������λ��;
	Position GetCurrenPosition();

	//���ö��������Xλ��;
	void  SetPositionX(int _xpos);

	//�����Ŀ���������ӵ������ꣻ
	bool IsCollision(Position _bullet,int _attack_distance);

	// ������ɫ����������ʲô��ɫ����
	void SetColor(Color _color);

	//ȡ����ɫ��������ɫƥ�䣻
	Color GetColor();

	//���麯����
	virtual void AI(Position target,//Ŀ����������ꣻ
		int unattack_frame,//�ǹ���״̬֡����
		int attacking_frame,//��Ҫ������֡����
		int attacked_frame) = NULL;//����֡����
	virtual void Check(Position target,int attacking_frame) = NULL;
	virtual bool IsHit() = NULL;
	virtual bool IsLayegg() = NULL;

	virtual ~CAnimation(void);
	
protected: 
	HGE* m_hge;						//���壻
	hgeAnimation* m_animation;		//������
	HTEXTURE m_tex;					//����������

	int m_weidth_tex,m_height_tex;	// ��������Ĵ�С��
	Position m_tex_position;		//������һ�ž�����ԴͼƬ�ϵ��������Ͻǵ����ꣻ
	Position m_screen_position;		//��������Ļ�е����꣨x��y����

	Direction m_direction;			//������ʾ��ķ���
	double m_x_speed;				//������x�����ƶ��ٶȣ�
	double m_y_speed;				//������Y������ƶ��ٶȣ�
	Color m_color;					//��¼�����ɫ��

};

