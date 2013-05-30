#pragma once
#include "canimation.h"

class CYoungPig;

//大嘴鸟的攻击范围和碰撞距离；
const double g_bigbird_attack_distanc = 200.0f;
const double g_bigbird_collision_distance = 50.0f;



class CBigMouseBird :
	public CAnimation
{
public:
	CBigMouseBird(void);
	//加载需要的资源和数据
	CBigMouseBird(HGE* _hge,//窗体
		CYoungPig*  _pig,  //小猪指针;
		char* filename,//纹理资源；
		Color _color,//动画纹利的初始坐标；
		int _weidth_tex,int _height_tex,//纹理的宽和高
		int _frame,//动画的帧数；
		int _FPS);//动画的播放速度；

	//这里的target的positon为图片的中心坐标；
	//所有的鸟的判断AI都在这里；
	//这里的坐标是猪的坐标；
	void AI(Position target,//目标的中心坐标；
		int unattack_frame,//非攻击状态帧数；
		int attacking_frame,//将要攻击的帧数；
		int attacked_frame);//攻击帧数；
	//检测大嘴鸟是否和目标相撞；
	bool IsHit();

	//这个函数不用！
	bool IsLayegg();
	void Check(Position target,int attacking_frame);
	
	virtual ~CBigMouseBird(void);
protected:
/*	bool m_isplaying;*/
	State m_state;//记录大嘴鸟的状态；

	CYoungPig    *m_pig;     //由于当大嘴鸟撞到小猪时，要让小猪减血，故需要小猪;
};

