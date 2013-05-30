
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
	void             SetImage(char* filename, int x_positon, int y_position, int width, int height);    //�������ͷ��;

	float			 GetPositionX() const;                                   //��ȡ���ĵ�X����
	float            GetPositionY() const;                                   //��ȡ���ĵ�Y����
	float            GetPositionShootX()const;								 //��ȡ������X����
	float            GetPositionShootY()const;                               //��ȡ������Y����
	float            GetWidth()const;
	float            GetHeight()const;
	float            GetAngle()const;
	float            GetStrength()const;
	float            GetWeaponState()const;
	float            GetWeaponPower()const;
	void             SetPosition(float _x, float _y);
	void             SetSpeedxy(float xspeed,float yspeed);                  //�ֱ�����X,Y�������
	void             SetSpeed(float speed);                                  //������������ٶ�
	void             SetCenter();                                            //����ͼƬ�����ĵ㣬ͼƬ��תʱ�����˵���ת
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
	float                Power;                                            //����ʱ������ֵ
	float                x_speed,y_speed;                                  //ͼ�����Ͻ�x��y�任���ٶ�
	float                m_xposition,m_yposition;                          //Weapon x��y��λ�ã�Ϊͼ�����Ͻǵ�����
	float                angle;                                            //һ��ͼƬ�ĽǶȣ�����˳ʱ����ת����fly������ʹ��
	float                stength;                                          //���ʱ�ĳ�ʼ���ȣ������ӵ��ĳ�ʼ�ٶ�
	ObjectState          WeaponState;
};
#endif


