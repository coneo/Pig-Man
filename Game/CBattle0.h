/*****************************************************
ս����������ս�ĳ��أ���ս���У�Ҫʵ�����¼��㣺
	1.������ʾ;
	2.��Ч����;
	3.��ɫ��ʾ;
	4.������ʾ;
	5.��ɫ״̬��ʾ��Ѫ��������ֵ;
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



//const int WIN_WIDTH  =  GetSystemMetrics(SM_CXSCREEN)*0.9;    //���ڵĿ��;�ú���Ϊwindows����ĺ�����ȡ����Ӧ����ʾ���ֱ���
//const int WIN_HEIGHT =  GetSystemMetrics(SM_CYSCREEN)*0.9;   //���ڵĸ߶�;
class CBattle0           //ս��������ÿ���ؿ��ľ��峡��;
{
public:
	CBattle0(HGE *_hge);
	~CBattle0();
	void    Init();        //��ս�����г�ʼ��������һЩ������Դ,����ʾ����;
	bool    Run();         //��ʼս��;
    bool    Render();      //�Գ��������������ͽ�ɫ�����пɼ��ģ����л���;
	bool    attack_by_egg();               //С�����ҵ�
	bool    attack_by_impactbird();        //С��������񹥻�
	bool    attack_by_jumpbird();          //С������Ծ�����ҵ�
	bool    attack_by_Bombbird();          //С��ը���񹥻�
	bool    attack_by_animbird();

	void    Release();     //�ͷ���Դ;
	void    settimeflage();
	void    settimeflage_speed();
	void    gettime_speed();
	void    gettime();

	bool    TimerMenege_Update( float &dt);
	bool    TimerMenege_Render( float &dt);
	void    Pigdown();                           //С��ը��֮�󣬻���
	void    DragonFire();
	void    ButterflyRun();



	

private:
	
	HGE             *m_hge;
	hgeSprite       *m_bkspr;   //���ڻ��Ʊ���ͼ;
	HTEXTURE        m_bktex;   //����ͼ������;
	HTEXTURE	    tex;
	HTEXTURE			texbg;
	HTEXTURE            m_fire;
	HEFFECT		    snd;
	hgeSprite      *spt;
	hgeSprite      *m_sprbg ;
	hgeSprite*     m_sptfire;  
    hgeParticleSystem* part[32];
	hgeParticleSystem*   par;

	bool battle00_status; //ģʽ״̬
    
	CEgg           *m_egg[5];

	CYoungPig1     *m_youngpig1;    //����ģʽ�µ�С��
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

