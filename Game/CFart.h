#pragma once
#include "CObjects.h"
#include "hgeparticle.h"

class CFart : public CObjects
{
public:
	CFart();
	CFart(HGE *_hge);
	~CFart();
	void boom();
	void Setspeed(float s);
	void Chang();
	void SetChanging(bool B);
	bool GetChanging();
	void SetHscale(float H);
	void SetVscale(float V);
	void         SetTexture(float x,float y,float w,float h,bool t);
private:
	float m_speed;
	hgeParticleSystem*	par;
	hgeSprite    *_spr;
	float     m_hscale;       //屁的水平缩放因子;
	float     m_vscale;       //屁的垂直缩放因子;
	bool      m_ischanging;   //决定是否进行缩放;

};