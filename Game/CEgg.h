#pragma once
#include "CObjects.h"

class CEgg : public CObjects
{
public:
	CEgg();
	CEgg(HGE *_hge);
	~CEgg();
	void     Show();       //显示鸡蛋;
	void     SetSpeed(float _speed);   //设置速度;
	//float    GetHeight() const;  //取得鸡蛋图片的高;  后面再考虑要不要;
private:
	float          m_speed;         //鸡蛋的竖直下落速度;
};

