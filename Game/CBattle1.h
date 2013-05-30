/*****************************************************
战场，即是作战的场地，在战场中，要实现以下几点：
	1.背景显示;
	2.音效播放;
	3.角色显示;
	4.道具显示;
	5.角色状态显示：血量、经验值;
	***************************************************/
#pragma once

//系统自带头文件；
#include <list>
#include "hge.h"
#include "hgefont.h"
#include "hgegui.h"
#include "hgeparticle.h"

//猪猪侠和装备头文件；
#include "CYoungPig.h"
#include "CEquipmentManager.h"


//鸟和蛋的头文件；
#include "CAnimation.h"
#include "CAnimEgg.h"
#include "CBigMouseBird.h"
#include "CBombEgg.h"
#include "CEggBird.h"
#include "CLightBird.h"

class CGame;       //在battle中要更改游戏状态，故需要CGame;

//波数的全局变量；
enum WAVE {FIRST, SECOND, THIRD};
//大嘴鸟的全局变量；
const float g_b2_bigbird_y = 570;
const float g_b2_bigbird_x_speed = 2.0f;
const float g_b2_bigbird_y_speed = 0.0f;
//下蛋鸟的全局变量；
const float g_b2_eggbird_y = 50;//鸟的高度；
const float g_b2_eggbird_x_speed = 2.0f;
const float g_b2_eggbird_y_speed = 0.0f;
//下蛋鸟的全局变量：
const float g_b2_bombbird_y = 100;
const float g_b2_bombbird_x_speed = 2.0f;
const float g_b2_bombbird_y_speed = 0.0f;
//闪电鸟
const float g_b2_lightbird_y = 0;//鸟的高度；
const float g_b2_lightbird_x_speed = 2.0f;
const float g_b2_lightbird_y_speed = 0.0f;
//蛋的全局变量；
const float g_b2_egg_x_speed = 0.0f;
const float g_b2_egg_y_speed = 1.0f;
//炸弹的速度；
const float g_b2_bomb_x_speed = 0.0f;
const float g_b2_bomb_y_seepd = 1.0f;
//猪的纹理宽度和高度；
const Position g_pig_wh = Position(69,51);

//子弹攻击范围；
const float g_bullet_attck_distace = 60;
const Position g_bullet_wh =Position(33,52);

//火箭攻击范围;
const float g_rocket_attck_distace = 200;
const Position g_rocket_wh = Position(66,66);

//屁的攻击范围;
const float g_fart_attck_distace = 500;
const Position g_fart_wh = Position(100,50);


class CBattle1
{
public:
	CBattle1(HGE *_hge, CGame *_game);
	~CBattle1();
	void    Init();					//对战场进行初始化，加载一些场景资源,并显示出来;
	
	bool    Run();					//开始战斗，在这部分实现逻辑判断和逻辑控制；
    
	bool    Render();				//对场景（包括背景和角色等所有可见的）进行绘制;
	
	void    UpdateBk();				//更新背景图,保证世界坐标;
	//void    UpdateBirds();		//更新鸟的坐标，同时保证世界坐标;
	//void    CheckCollision();		//检测鸟与针刺，鸟与火箭，鸟与屁的碰撞, 并做出相应反应;
	
	void    SetScore(int _score);   //设置分数;
	int     GetScore() const;       //获取分数;
	
	void    GenerateBirdsByWave();	//根据“波数”来创建鸟;

	void    JumpCard();             //跳转关数；
	
	void	Reset();                
	void    Release();				//释放资源;
private:
	HGE            *m_hge;          //窗体
	CGame          *m_cgame;        //游戏类;

	hgeFont		   *m_fnt;          
	hgeSprite      *m_bkspr;		//用于绘制背景图;
	HTEXTURE        m_bktex;		//背景图的纹理;
	float		    m_preX;      //前一帧背景图左上角的X坐标，由于背景图的Y坐标不变（都是0），故不考虑背景图的Y坐标;
	float			m_currentX;	   //当前帧的背景图的左上角X坐标，由于背景图的Y坐标不变（都是0），故不考虑背景图的Y坐标;
	float			m_Xoffset;   //背景图的前一帧和后一帧的差值;

	int             m_score;		//游戏的得分;

	CYoungPig      *hero;					// 猪的对象；
	CEquipmentManager   *m_equipManager;	//装备管理器;
	WAVE            m_wave;					//记录战争的波数；
	//如果为零则失败；
	int             m_max_birds;            //每一关最多漏鸟数；
	bool            m_card_state;           //每一波的状态量；

	///////////////////////////////////音效/////////////////////////////////////
	HEFFECT  m_snd_bigmouse_fly;    //大嘴鸟飞翔和受伤的声音;
	HEFFECT  m_snd_bigmouse_hurt;  
	HEFFECT  m_snd_eggbird_fly;     //蛋鸟飞翔和受伤的音效;
	HEFFECT  m_snd_eggbird_hurt;  
	HEFFECT  m_snd_lightbird_fly;   //闪电鸟飞翔和受伤的音效;
	HEFFECT  m_snd_lightbird_hurt;
	HEFFECT  m_snd_bombbird_fly;    //炸弹鸟飞翔和受伤的音效;
	HEFFECT  m_snd_bombbird_hurt;
	HEFFECT  m_snd_pig_hurt;       //小猪受伤音效;

	//装所有鸟的链表容器；
	std::list<CBigMouseBird*> m_b2_bigbirds;
	std::list<CEggBird*> m_b2_eggbirds;
	std::list<CLightBird*> m_b2_lightbirds;
	std::list<CEggBird*>m_b2_bombbirds;
	//装所有蛋的链表容器；
	std::list<CAnimEgg*> m_b2_eggs;
	std::list<CBombEgg*> m_b2_bombs;

	//鸟的迭代器；
	std::list<CBigMouseBird*>::iterator bigbird_ite;
	std::list<CEggBird*>::iterator eggbird_ite;
	std::list<CLightBird*>::iterator lightbird_ite;
	std::list<CEggBird*>::iterator bombbird_ite;

	//蛋的迭代器；
	std::list<CAnimEgg*>::iterator egg_ite;
	std::list<CBombEgg*>::iterator bomb_ite;


	

};

