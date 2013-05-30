#pragma once
#include "canimation.h"

//下蛋鸟的攻击范围；
const double g_eggbird_attack = 20.0f;


class CEggBird :
	public CAnimation
{
public:
	CEggBird(void);
	//加载需要的资源和数据
	CEggBird(HGE* _hge,//窗体
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
		int attacking_frame,//攻击状态帧数；
		int attacked_frame = 0);

	//判断是否下蛋；作为蛋类的借口用；
	bool IsLayegg();
	//这个函数不用！
	bool IsHit();
	void Check(Position target,int attacking_frame);
	virtual ~CEggBird(void);
protected:
	State m_state;//记录下蛋鸟的状态；
};

