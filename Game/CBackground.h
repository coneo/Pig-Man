#include"CObjects.h"



//����ͼƬ�࣬ͨ������ʵ�ֶ�̬����
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


