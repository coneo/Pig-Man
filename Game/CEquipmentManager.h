#pragma once
#include "CYoungPig.h"
#include "CRocket.h"
#include "CBullet1.h"
#include "CFart.h"

class CEquipmentManager
{
public:
	CEquipmentManager();
	CEquipmentManager(CYoungPig  *_hero, HGE *_hge);
	~CEquipmentManager();
	CBullet1*   GetBullet() const;
	CRocket*	GetRocket() const;
	CFart*      GetFart() const;
	void    Update();          //根据小猪的操作来控制装备库;
	void    UpdateBullet();
	void    UpdateRocket();
	void    UpdateFart();
	void    Render();          //绘制;
private:
	HGE           *m_hge;
	CYoungPig     *m_hero;
	CBullet1       *m_bullet;
	CRocket       *m_rocket;
	CFart         *m_fart;
	//////////////////////////////////////////////音效////////////////////////////
	HEFFECT  m_sndfart;        //屁声;
	HEFFECT  m_sndrocket;      //火箭声;
	HEFFECT	 m_sndrocketBoom;  //火箭爆炸声;
	HEFFECT  m_sndbullet;      //发射子弹声;

	///////////////////////////////爆炸效果///////////////////////////////////////////
	hgeAnimation	*m_rocketboom;    //火箭爆炸的动画;
	HTEXTURE         m_rocketboomtex;   //火箭爆炸的纹理;

	bool           m_isFartHaving;      //是否有“屁”装备可使用;
};

