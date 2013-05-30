#include"CPig.h"
#include"CEgg.h"
#include"math.h"
#include <stdlib.h>   

class CYoungPig1 :public CPig
{
public:

	CYoungPig1();
	CYoungPig1(HGE *_hge);
	~CYoungPig1();
	void Render();
	bool Update();                     //控制小猪左，右，跳动
	void useweapon();                   //小猪使用武器
	void setspeed(float _dx,float _dy);
	int  getspeedx();
	int  getspeedy();
	void setlife(int _life);            //设置小猪生命值
	void   jump();                      //实现小猪跳跃的函数
	void   SetJump();                   //重置小猪跳跃的标记 

	int  Getlife();                     // 取得小猪现在生命值
	int getchangetime();                //获得小猪装备切换的次数
	void setchangetime(int T);          //设置小猪装备切换的次数
	bool  getuseweaponstate();

	void  setuseweaponstate();
	//void setwid_heifuc(int width,int heigt );
	
private:
	HEFFECT    sndpigrun ;  
	float  d_x;                          //通过d_X ,d_y来设置小猪的速度
	float  d_y;
	bool   isjump;                      //控制小猪跳跃的标记
	int   changetime;                   //记录装备被更换了几次
	bool   isuseweapon;
	float  d_timer;
	float j_timer;
	//bool   stase;


};
                                       
