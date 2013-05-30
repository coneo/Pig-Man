
#ifndef CBULLET
#define CBULLET
#include"CObjectState.h"
#include <vector>
using namespace std;


struct Ropes
{
	double              x_position,y_position;                //绳子的坐标
	hgeSprite          *m_ropesprite;  
	hgeSprite          *m_ropespritemid;                     //两点中间的一点

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
	void                   Render();												    //将图片显示出来
	void			       Move();														//设置子弹移动的位置。x,y为子弹的初始位置
	float                  GetPositionX() const;										//取得的X坐标;
	float                  GetPositionY() const;										//获取的y坐标
	void                   SetPosition(float _x, float _y);							    //设置子弹的位置
	void                   SetSpeed(float Speed,float angle);							//子弹的初始速度，和与X轴的角度angle
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
	void                   Renderrope();                                                //渲染绳子
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
	float                  x_speed,y_speed;                                          //图像左上角x，y变换的速度
	float                  speed;                                                    //子弹在行动方向中的速度
	float                  m_xposition,m_yposition;                                 
	float                  m_xropeposition,m_yropeposition;
	ObjectState            BulletState;
	ObjectState            RopeState;
	vector<Ropes>          m_Rope;
};
#endif


