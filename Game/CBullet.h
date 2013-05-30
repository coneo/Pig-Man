
#ifndef CBULLET
#define CBULLET
#include"CObjectState.h"
#include <vector>
using namespace std;


struct Ropes
{
	double              x_position,y_position;                //���ӵ�����
	hgeSprite          *m_ropesprite;  
	hgeSprite          *m_ropespritemid;                     //�����м��һ��

};

class CBullet
{
public:
	CBullet();
	CBullet(HGE *hge);
	~CBullet();   
	void                   SetImage(char* filename, int x_positon,int y_position, int width, int height,
		char* filename1, int x_positon1,int y_position1, int width1, int height1,
		char* filename2,int x_position2,int y_position2,int width2,int height2);	
	void                   Render();												    //��ͼƬ��ʾ����
	void			       Move();														//�����ӵ��ƶ���λ�á�x,yΪ�ӵ��ĳ�ʼλ��
	float                  GetPositionX() const;										//ȡ�õ�X����;
	float                  GetPositionY() const;										//��ȡ��y����
	void                   SetPosition(float _x, float _y);							    //�����ӵ���λ��
	void                   SetSpeed(float Speed,float angle);							//�ӵ��ĳ�ʼ�ٶȣ�����X��ĽǶ�angle
	void                   SetBulletStatemove();
	void                   SetBulletStateInitial();
	void                   SetBulletStatecollsion();
	void                   SetRopeStateInitial();
	void                   SetRopeStateappear();
	void                   SetRopeStatedisappear();
	void                   SetRopePosition();
	void                   SetRopePosition(float x,float y);
	void                   SetRopePosition(float x_bird,float y_bird,float x_wea,float y_wea);
	void                   ClearRope();
	void                   Renderrope();                                                //��Ⱦ����
	ObjectState            GetBulletState();
	ObjectState            GetRopeState();
	float                  GetRopePositionX();
	float                  GetRopePositionY();

private:

	hgeSprite*			   m_spt;  
	hgeParticleSystem*	   part;
	HTEXTURE               m_sprtex;

	HGE                   *m_hge;	
	hgeSprite             *m_spr;
	HTEXTURE               m_tex;
	HTEXTURE               m_ropetex;
	HTEXTURE               m_ropetex1;
	float                  x_speed,y_speed;                                          //ͼ�����Ͻ�x��y�任���ٶ�
	float                  speed;                                                    //�ӵ����ж������е��ٶ�
	float                  m_xposition,m_yposition;                                 
	float                  m_xropeposition,m_yropeposition;
	ObjectState            BulletState;
	ObjectState            RopeState;
	vector<Ropes>          m_Rope;
};
#endif


