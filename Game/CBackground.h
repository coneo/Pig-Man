#include"CObjects.h"



//背景图片类，通过该类实现动态背景
class CBackground :public CObjects
{
public:

	CBackground();
	CBackground(HGE *_hge);
	~CBackground();
	void control();
	void move();
	void setspeed(float a);
	float getspeed();

	bool getisright();
protected:
	float  speed;
	bool   isright;

};


