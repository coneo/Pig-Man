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
	float      m_speed;         //������ƶ��ٶ�;
	bool       m_isReady;     

	hgeParticleSystem   *m_par;  //����ϵͳ;
	hgeSprite           *m_pspr;      //���Ӿ���ָ��;
	HTEXTURE             m_partex;  //����ϵͳ����;
};

