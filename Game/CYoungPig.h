#pragma once
#include "CPig.h"
#include "CEquipment.h"
#include "hgefont.h"
#include "CGlobal.h"

enum PDirection {PLEFT, PRIGHT};   //小猪的方向;

class CYoungPig : public CPig
{
public:
	CYoungPig();
	CYoungPig(HGE *_hge);
	~CYoungPig();
	void	Reset();             //小猪的初始化，该函数的存在是为了游戏重置； 
	bool    Update();            //逻辑;
	void    UpdateEquipmentXpo(float _battle_bk_xoffset);  //更新掉下装备的X坐标，保证其X坐标;
	void    Render();     //根据战场的背景偏移量绘制;
	void    SetSpeed(float _speed);      //设置速度;
	int     GetLife() const;             //获取生命值;
	void    GainLife();      //获得一条生命;
	void    SetLife(int _numlife);   //设置生命值;
	void    Hurt();       //小猪受伤，掉血;
	void    Jump();          //跳跳;
	bool    Contrl();        //接受玩家的控制;
	void    CheckBoundingCollision(); //检查是否超出边界;
	void    ChangeStatus();  //更换小猪的状态;

	bool    IsLeftWaitingPoint();      //是否在左面的等待点;
	bool    IsRightWaitingPoint();     //是否在右面的等待点;
// 	void    OutLeftWaitingPoint();     //离开左边的等待点;
// 	void    OutRightWaitingPoint();    //离开右边的等待点;
	int     GetTraveledLength() const;

	void    SetColor(Color _color);      //设置小猪颜色；
	Color   GetColor();

	PDirection GetDirection() const;   //获取小猪方向;

	void    Sharp();         //针刺;
	void    Rocket();        //发射火箭;
	void    Fart();          //放屁;
	void    Quicken();       //急速;
	void    Ignore();        //无视;

	void    UnSharp();         //使用完 针刺;
	void    UnRocket();        //使用完 发射火箭;
	void    UnFart();          //使用完 放屁;

	//void    UnQuicken();       //使用完 急速;
	//void    UnIgnore();        //使用完 无视;

	void    CheckQuicking();      //检查是否使用完 “急速”;
	void    CheckIgnoring();      //检查是否使用完 “无视”;

	bool    IsIgnoring();
	bool    IsSharping();        //判断是否使用针刺;
	bool    IsRocketing();       //判断是否发射了火箭;
	bool    IsFarting();         //判断是否放屁;

	//void Move();
	void    RandomDown(float x,float y);   //随机掉落哪个装备。传人位置信息
	void    ShowCount();

	CEquipment *GetEquipment(int i);

private:
	Color     m_color;              //对应三种颜色(R,G,B)，用于和鸟匹配;
	PDirection m_direction;        //小猪的方向;

	float   m_speed;              //速度;
	float   m_timeDeltaOfQuicken;   //加速的时间增量;
	float   m_timeDeltaOfIgnore;

	bool    m_isInRightWaitingPoint;  //是否在右面等待点集之内(即是否场景会向左移动);
	bool    m_isInLeftWaitingPoint;

	bool    m_isRocketing;        //是否正在发射火箭;
	bool    m_isSharping;         //是否正在使用针刺;
	bool    m_isFarting;          //是否正在使用屁;
	bool    m_isIgnoring;         //是否正在使用“无视”;
	bool    m_isquicking;

	int     m_lengthOfTravled;    //小猪已经跑了多少距离;
	bool    m_isJumping;          //小猪是否在跳;

	CEquipment     *m_showequipment[6];    //用于显示6个物品，火箭,屁，极速，无视，血量和鸟通过公个数;
	CEquipment     *m_equipment[5];        //用于创建掉下的物品
	hgeFont		   *m_fnt;
	bool            m_israndom;

	////////////////////////////////////////////音效//////////////////////////////
	HEFFECT		m_sndgaimequ;    //吃装备的声音;
};

