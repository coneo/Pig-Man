#pragma once
#include "canimation.h"

class CYoungPig;

//蛋的攻击范围；
const double g_bombegg_attack_distance = 20;
//炸弹的攻击范围；
const double g_bomb_attack_distance = 100;
//地面位置；
const double g_y_round = 570;


class CBombEgg :
	public CAnimation
{
public:
	CBombEgg(void);
	//加载需要的资源和数据
	CBombEgg(HGE* _hge,//窗体
		CYoungPig* _pig, //小猪;
		char* filename,//纹理资源；
		Position _tex_position,//动画纹利的初始坐标；
		int _weidth_tex,int _height_tex,//纹理的宽和高
		int _frame,//动画的帧数；
		int _FPS);//动画的播放速度；

	//这里的target的positon为图片的中心坐标；
	//这里的坐标是猪的坐标；
	//所有的鸟的判断AI都在这里；
	void Check(Position target,int attacking_frame);

	//检测炸弹鸟是否和目标相撞；
	bool IsHit();

	//这个函数不用；
	bool IsLayegg();
	State GetState();
	void AI(Position target, int unattack_frame, int attacking_frame, int attacked_frame);

	virtual ~CBombEgg(void);
protected:
	CYoungPig* m_pig;  //炸蛋与小猪碰撞时，小猪会伤血;
	bool m_ishit; //记录蛋时候撞击物体；
	State m_state;//记录蛋的状态
};

