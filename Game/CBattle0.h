/*****************************************************
战场，即是作战的场地，在战场中，要实现以下几点：
	1.背景显示;
	2.音效播放;
	3.角色显示;
	4.道具显示;
	5.角色状态显示：血量、经验值;
	***************************************************/
#pragma once
#include "hge.h"
#include "hgegui.h"
#include "CEgg.h"
#include "CYoungPig1.h"
#include"hgefont.h"
#include "CBackground.h"
//#include "CBombbird.h"

#include "hgeparticle.h"
#include "CAnimEggBird.h"
#include "CAnimMoveDownBird.h"
#include "CAnimDragon.h"
#include<stdlib.h>


class  CAnimJumpBird;



//const int WIN_WIDTH  =  GetSystemMetrics(SM_CXSCREEN)*0.9;    //窗口的宽度;该函数为windows下面的函数，取得相应的显示器分辨率
//const int WIN_HEIGHT =  GetSystemMetrics(SM_CYSCREEN)*0.9;   //窗口的高度;
class CBattle0           //战场；即是每个关卡的具体场景;
{
public:
	CBattle0(HGE *_hge);
	~CBattle0();
	void    Init();        //对战场进行初始化，加载一些场景资源,并显示出来;
	bool    Run();         //开始战斗;
    bool    Render();      //对场景（包括背景和角色等所有可见的）进行绘制;
	bool    attack_by_egg();               //小猪被鸟蛋砸到
	bool    attack_by_impactbird();        //小猪被俯冲的鸟攻击
	bool    attack_by_jumpbird();          //小猪被会跳跃的鸟砸到
	bool    attack_by_Bombbird();          //小猪被炸弹鸟攻击
	bool    attack_by_animbird();

	void    Release();     //释放资源;
	void    settimeflage();
	void    settimeflage_speed();
	void    gettime_speed();
	void    gettime();

	bool    TimerMenege_Update( float &dt);
	bool    TimerMenege_Render( float &dt);
	void    Pigdown();                           //小猪被炸飞之后，回落
	void    DragonFire();
	void    ButterflyRun();



	

private:
	
	HGE             *m_hge;
	hgeSprite       *m_bkspr;   //用于绘制背景图;
	HTEXTURE        m_bktex;   //背景图的纹理;
	HTEXTURE	    tex;
	HTEXTURE			texbg;
	HTEXTURE            m_fire;
	HEFFECT		    snd;
	hgeSprite      *spt;
	hgeSprite      *m_sprbg ;
	hgeSprite*     m_sptfire;  
    hgeParticleSystem* part[32];
	hgeParticleSystem*   par;

	bool battle00_status; //模式状态
    
	CEgg           *m_egg[5];

	CYoungPig1     *m_youngpig1;    //求生模式下的小猪
	hgeFont        *fnt;
//	CJumpBird      *m_jumpbird;
	CBackground    *m_background[6];

	CAnimEggBird   *m_eggBird[6];

	CAnimEggBird   *runbrid[6];

	CAnimEggBird   *movebird_first[6];

	CAnimEggBird   *movebird_second[6];

	CAnimSwoopBird *swoopattrackbird[6];
	CAnimMoveDownBird *movedownbird[6];

	CAnimDragon    *dragon[6];


CAnimBird_Run_battle *AnimBird[100];

	float          _timer;
	float          _timer0;
	float          _timer1;
	float          _timer2;
	float          _timer3;
	float          _timer4;
	float          _timer5;
	int           _timer6;

	int           _timer7;
 //   float          _timermenege_update;
//	float          _timermenege_render;
	float           b_dx ;
	float           b_x ;
	float            b_y ;
	float            FireX;
	bool           timeflage;
	bool           timeflage1;
	bool           by_bombed;
	bool           gamestart;
	int           N;
   
	HEFFECT       sndeggbird;
	HEFFECT       sndmovebird;
	HEFFECT       sndswoopattrackbird;
	HEFFECT       sndrunbrid;
	HEFFECT       snddragon;
    HEFFECT       sndpigrun;
	HEFFECT       sndpigbyattrack;  
	HEFFECT        sndmovedownbird; 
	HEFFECT        sndeggbreak; 
	HEFFECT        sndhorserun;

};

