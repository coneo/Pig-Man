#pragma once
#include "hgeparticle.h"
#include "CObjects.h"

class CRocket:public CObjects
{
public:
	CRocket(HGE *_hge);
	~CRocket();
	void     SetSpeed(float _speed);
	void     SetReady();
	void     SetUnReady();
	void     Update();
	void     Show();
private:
	float      m_speed;         //火箭的移动速度;
	bool       m_isReady;     

	hgeParticleSystem   *m_par;  //粒子系统;
	hgeSprite           *m_pspr;      //粒子精灵指针;
	HTEXTURE             m_partex;  //粒子系统纹理;
};

