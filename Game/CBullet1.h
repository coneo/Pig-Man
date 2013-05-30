#pragma once
#include "CObjects.h"

class CBullet1:public CObjects
{
public:
	CBullet1(HGE *_hge);
	~CBullet1();
	void   Show();
	void   Update();
	void   SetSpeed(float S);
	void   SetReady();
	void   SetUnReady();
private:
	float      m_speed;
	bool       m_isReady;

};