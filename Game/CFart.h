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
	float     m_hscale;       //ƨ��ˮƽ��������;
	float     m_vscale;       //ƨ�Ĵ�ֱ��������;
	bool      m_ischanging;   //�����Ƿ��������;

};