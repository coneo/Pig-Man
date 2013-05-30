
#ifndef CWEAPON
#define CWEAPON
#include"CObjectState.h"
#include "CStrength.h"
class CWeapon
{
public:
	CWeapon();
	CWeapon(HGE *hge);
	~CWeapon();   
	void             SetImage(char* filename, int x_positon, int y_position, int width, int height);    //设置鸟的头像;

	float			 GetPositionX() const;                                   //获取中心点X坐标
	float            GetPositionY() const;                                   //获取中心点Y坐标
	float            GetPositionShootX()const;								 //获取射击点的X坐标
	float            GetPositionShootY()const;                               //获取射击点的Y坐标
	float            GetWidth()const;
	float            GetHeight()const;
	float            GetAngle()const;
	float            GetStrength()const;
	float            GetWeaponState()const;
	float            GetWeaponPower()const;
	void             SetPosition(float _x, float _y);
	void             SetSpeedxy(float xspeed,float yspeed);                  //分别设置X,Y轴的坐标
	void             SetSpeed(float speed);                                  //设置物体的总速度
	void             SetCenter();                                            //设置图片的中心点，图片旋转时，按此点旋转
	void             SetWeaponStateshoot();
	void             SetWeaponStateadjust();
	void             SetWeaponStateIntial();
	void			 Render(); 
	void             Controle();
	void             setInitState();
private:
	HGE                 *m_hge;	
	hgeSprite           *m_spr;
	hgeQuad              quad;
	HTEXTURE             m_tex;
	int                  x,y;
	float                Power;                                            //拉鸟时的力量值
	float                x_speed,y_speed;                                  //图像左上角x，y变换的速度
	float                m_xposition,m_yposition;                          //Weapon x，y的位置，为图像左上角的坐标
	float                angle;                                            //一张图片的角度，用于顺时针旋转，在fly函数中使用
	float                stength;                                          //射击时的初始力度，决定子弹的初始速度
	ObjectState          WeaponState;
};
#endif


