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
	bool Update();                     //����С�����ң�����
	void useweapon();                   //С��ʹ������
	void setspeed(float _dx,float _dy);
	int  getspeedx();
	int  getspeedy();
	void setlife(int _life);            //����С������ֵ
	void   jump();                      //ʵ��С����Ծ�ĺ���
	void   SetJump();                   //����С����Ծ�ı�� 

	int  Getlife();                     // ȡ��С����������ֵ
	int getchangetime();                //���С��װ���л��Ĵ���
	void setchangetime(int T);          //����С��װ���л��Ĵ���
	bool  getuseweaponstate();

	void  setuseweaponstate();
	//void setwid_heifuc(int width,int heigt );
	
private:
	HEFFECT    sndpigrun ;  
	float  d_x;                          //ͨ��d_X ,d_y������С����ٶ�
	float  d_y;
	bool   isjump;                      //����С����Ծ�ı��
	int   changetime;                   //��¼װ���������˼���
	bool   isuseweapon;
	float  d_timer;
	float j_timer;
	//bool   stase;


};
                                       
