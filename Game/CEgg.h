#pragma once
#include "CObjects.h"

class CEgg : public CObjects
{
public:
	CEgg();
	CEgg(HGE *_hge);
	~CEgg();
	void     Show();       //��ʾ����;
	void     SetSpeed(float _speed);   //�����ٶ�;
	//float    GetHeight() const;  //ȡ�ü���ͼƬ�ĸ�;  �����ٿ���Ҫ��Ҫ;
private:
	float          m_speed;         //��������ֱ�����ٶ�;
};

