#pragma once
#include "canimation.h"

class CYoungPig;

const double g_light_attack_speed = 6;
const double g_light_attack_distanc = 40;

class CLightBird :
	public CAnimation
{
public:
	CLightBird(void);

	//加载需要的资源和数据；
	CLightBird(HGE* _hge,                 //窗体
		CYoungPig* _pig,                 //小猪;
		char* filename,                  //纹理资源；
		Color _color,          //动画纹利的初始坐标；
		int _weidth_tex,int _height_tex,//纹理的宽和高
		int _frame,                     //动画的帧数；
		int _FPS);                     //动画的播放速度；

	//这里的target的positon为图片的中心坐标；
	//这里的坐标是猪的坐标；
	//所有的鸟的判断AI都在这里；
	void AI(Position target,          //目标的中心坐标
		int unattack_frame,           //非攻击状态帧数；
		int attacking_frame,           //攻击帧数；
		int attacked_frame = 0);

	//检测闪电鸟是否和目标相撞；
	bool IsHit();
	//这个函数不用！
	bool IsLayegg();
	void Check(Position target,int attacking_frame);

	virtual ~CLightBird(void);
protected:
	CYoungPig	*m_pig;             //当闪电鸟撞上猪时，猪会受伤，故需要猪;
	State m_state;					//记录闪电鸟的状态；
	int m_attack_spot;				//记录初始化时的一个随机的攻击位置；
	int m_speed;					//记录闪电鸟的速度为后面的跟踪算法服务；
	bool m_ishit;                   //记录闪电鸟是否撞击到目标；
};

