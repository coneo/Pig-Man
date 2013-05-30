#ifndef CBATTLE2
#define CBATTLE2
#include"C1_bird.h"
#include"CWeapon.h"
#include"CBullet.h"
#include"CStrength.h"
#include "hgefont.h"
#include "bigMouseBird.h"
#include <hgeanim.h>

const static int screenWidth   = 1024;
const static int screenHeight  = 768;
class CBattle2
{
public:
	CBattle2(HGE *_hge);
	~CBattle2();
	void    Init();        //对战场进行初始化，加载一些场景资源,并显示出来;
	bool    Run();         //开始战斗;
	bool    Render();
	void    Release();     //释放资源;

private:
	void            ButterflyRun();
	void            paintBg();
	void            timeAndScore();
	void            Shooting();
	void            timeOver();
	void            resourceLoading();
	void            Rain();
    void            RenderBulletandRope();                //绘制绳子和子弹
	HGE             *m_hge;
	hgeSprite       *m_sprBackground;   //用于绘制背景图;
	hgeSprite       *m_sprBg1;
	hgeSprite       *m_sprGround;  //绘制地面
	hgeSprite       *m_sprFlower;
	hgeSprite       *m_sprFlowerMove;
	hgeSprite       *m_sprGrass;
	hgeSprite       *m_sprTree;
	hgeSprite       *m_sprButterfly;
	hgeSprite       *m_sprDirection;
	hgeSprite       *m_sprStrength;
	HTEXTURE        m_direction;
	HTEXTURE        m_butterfly;
	HTEXTURE        m_stone;
	HTEXTURE        m_tree;
	HTEXTURE        m_flower;
	HTEXTURE        m_flowerMove;
	int             flowerFlag;
	HTEXTURE        m_grass;
	HTEXTURE        m_tex;   //背景图的纹理;
	HTEXTURE        m_bg1;
	HTEXTURE        m_ground;  //地面
	HTEXTURE        m_rain;   //雨滴
	HTEXTURE        m_Strength;
	bigMouseBird    *animDragon;
	bigMouseBird    *animBirdBlue;
	CWeapon         *NewWeapon;
	CBullet         *NewBullet;
	CStrength       *NewStrength;
	float timeCount;
	int   score;
	hgeFont				*fnt;
	HEFFECT             snd[5]; //先加载五个声音文件
	float butterflyLX;
	float butterflyRX;
	float butterflyY;
	float butterflyAngle;
	float volume;
	//动画效果的实现
	hgeAnimation* m_goose;//动画；
	HTEXTURE      goose;
	float     goose_x_positon,goose_y_positon,goose_scale;
	//雨滴下落效果
	hgeSprite*			m_spt;  
	hgeParticleSystem*	part[64];
};
#endif