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
	void    Update();          //����С��Ĳ���������װ����;
	void    UpdateBullet();
	void    UpdateRocket();
	void    UpdateFart();
	void    Render();          //����;
private:
	HGE           *m_hge;
	CYoungPig     *m_hero;
	CBullet1       *m_bullet;
	CRocket       *m_rocket;
	CFart         *m_fart;
	//////////////////////////////////////////////��Ч////////////////////////////
	HEFFECT  m_sndfart;        //ƨ��;
	HEFFECT  m_sndrocket;      //�����;
	HEFFECT	 m_sndrocketBoom;  //�����ը��;
	HEFFECT  m_sndbullet;      //�����ӵ���;

	///////////////////////////////��ըЧ��///////////////////////////////////////////
	hgeAnimation	*m_rocketboom;    //�����ը�Ķ���;
	HTEXTURE         m_rocketboomtex;   //�����ը������;

	bool           m_isFartHaving;      //�Ƿ��С�ƨ��װ����ʹ��;
};

