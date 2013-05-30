#pragma once
#include "canimation.h"

class CYoungPig;

//蛋的攻击范围；
const int g_egg_attack_distace = 20;
//地面位置的Y坐标
const int g_y_ground = 630;


class CAnimEgg :
	public CAnimation
{
public:
	CAnimEgg(void);

	//加载需要的资源和数据
	CAnimEgg(HGE* _hge,//窗体
		CYoungPig* _pig,  //小猪;
		char* filename,//纹理资源；
		Position _tex_position,//动画纹利的初始坐标；
		int _weidth_tex,int _height_tex,//纹理的宽和高
		int _frame,//动画的帧数；
		int _FPS);//动画的播放速度；

	//这里的target的positon为图片的中心坐标；
	//这里的坐标是猪的坐标；
	//不停地检测蛋与目标的位置关系；
	void Check(Position target,int attacking_frame);

	//蛋的状态（非攻击，撞击地面，攻击目标后）；
	State GetState();

	//检测蛋是否与与目标或者地面是否相撞；
	bool IsHit();

	//这个函数不用；
	bool IsLayegg();
	void AI(Position target, int unattack_frame, int attacking_frame, int attacked_frame);
	

	virtual ~CAnimEgg(void);
protected:
	CYoungPig* m_pig;   //鸡蛋和小猪碰撞时，小猪会受伤，故需要小猪;
	bool m_ishit;//记录蛋时候撞击物体；

	State m_state;//记录蛋的状态
};

