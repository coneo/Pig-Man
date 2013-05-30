#pragma once
#include <hge.h>
#include <hgeanim.h>
#include <cmath>
#include "CGlobal.h"


enum Direction{RIGHT ,LEFTE};
enum State{UNATTACK,ATTACKING,ATTACKED,GROUDN_FIRING};
/*enum Color{RED,GREEN,BLUE};*/ //放到Global中，因为猪也要用到



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

	//取得当前动画精灵的位置;
	Position GetCurrenPosition();

	//设置动画精灵的X位置;
	void  SetPositionX(int _xpos);

	//这里的目标坐标是子弹的坐标；
	bool IsCollision(Position _bullet,int _attack_distance);

	// 设置颜色来决定创建什么颜色的鸟；
	void SetColor(Color _color);

	//取得颜色来进行颜色匹配；
	Color GetColor();

	//纯虚函数；
	virtual void AI(Position target,//目标的中心坐标；
		int unattack_frame,//非攻击状态帧数；
		int attacking_frame,//将要攻击的帧数；
		int attacked_frame) = NULL;//攻击帧数；
	virtual void Check(Position target,int attacking_frame) = NULL;
	virtual bool IsHit() = NULL;
	virtual bool IsLayegg() = NULL;

	virtual ~CAnimation(void);
	
protected: 
	HGE* m_hge;						//窗体；
	hgeAnimation* m_animation;		//动画；
	HTEXTURE m_tex;					//动画的纹理；

	int m_weidth_tex,m_height_tex;	// 动画纹理的大小；
	Position m_tex_position;		//动画第一张精灵在源图片上的坐标左上角的坐标；
	Position m_screen_position;		//动画在屏幕中的坐标（x，y）；

	Direction m_direction;			//用来表示鸟的方向；
	double m_x_speed;				//动画的x方向移动速度；
	double m_y_speed;				//动画的Y方向的移动速度；
	Color m_color;					//记录鸟的颜色；

};

