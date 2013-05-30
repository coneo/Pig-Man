#include "CBullet.h"
float fps;

float   g0    = 5;                                        //定义重0加速度
float   gRope = 0.5;                                      //绳子重力常量
float   Time  = 0;                                        //计算绳子摆动是用到
CBullet::CBullet()
{
	//angle=0;
}

CBullet::CBullet(HGE *_hge)
{
	m_tex           = 0;
	m_hge           = _hge;
	m_xposition     = 1024;
	m_yposition     = 768;

	int p           = 0;
	BulletState     = Initial;
	RopeState       = disappear;

	

	m_sprtex        =   m_hge -> Texture_Load("skill.png");
	m_spt           =   new hgeSprite(m_sprtex,0,0,3,3);        //粒子系统
	m_spt           ->  SetBlendMode(BLEND_COLORMUL | BLEND_ALPHAADD | BLEND_NOZWRITE);//粒子系统
	m_spt           ->  SetHotSpot(0,0);   
	part			=   new hgeParticleSystem("trail.psi",m_spt);  //粒子系统
	part			->  Fire();   //启动粒子系统
	


}

CBullet::~CBullet()
{
	delete m_spr;
	m_hge->Texture_Free(m_tex);
	m_hge->Target_Free(m_ropetex);

}

void CBullet:: SetImage(char* filename, int x_positon,int y_position, int width, int height,
	char* filename1, int x_positon1,int y_position1, int width1, int height1,
	char* filename2,int x_position2,int y_position2,int width2,int height2)
{
	m_tex					=	m_hge->Texture_Load(filename);
	m_spr					=	new hgeSprite(m_tex, x_positon, y_position, width, height);
	m_ropetex				=	m_hge->Texture_Load(filename1);
	m_ropetex1				=   m_hge->Texture_Load(filename2);
	Ropes   rope;
	rope.m_ropesprite       =	new hgeSprite(m_ropetex,x_positon1,y_position1,width1,height1);
	rope.m_ropespritemid    =	new hgeSprite(m_ropetex1,x_position2,y_position2,width2,height2);
	rope.x_position			=   0;
	rope.y_position			=   0;
	m_Rope.push_back(rope);
	//m_Rope.m_ropesprite=new hgeSprite(m_ropetex,x_positon1,y_position1,width1,height1);
	m_spr->SetHotSpot(10,7);
}

float CBullet::GetPositionX() const
{
	return m_xposition;
}

float CBullet::GetPositionY() const
{
	return m_yposition;
}

void CBullet::SetPosition(float _x, float _y)
{
	m_xposition = _x;
	m_yposition = _y;
	int p=0;
	//	BulletState=move;
}

void CBullet::SetSpeed(float Speed,float angle)
{
	float m=Speed;
	if(Speed>=9)
		Speed=9;           
	x_speed=Speed*cos(abs(angle));
	y_speed=Speed*sin(abs(angle));
	//	BulletState=move;
}
void CBullet::Render()
{	
	part			->  info.nEmission=1000;//粒子系统 
	float dt       =   m_hge -> Timer_GetDelta();
	m_spr	       ->  Render(m_xposition, m_yposition);	
	part           ->  MoveTo(m_xposition, m_yposition);
	part           ->  Render();
	part		   ->  Update(dt*1.5);
}
void CBullet::Move()
{
	fps=m_hge->Timer_GetDelta();
	y_speed=y_speed-g0*fps;/*******************************/       
	m_xposition+=x_speed;
	m_yposition-=y_speed;//y轴的坐标根据重力加速度不断变化
}
void CBullet::SetRopePosition()
{
	vector<Ropes>::reverse_iterator  riter=m_Rope.rbegin();
	if ((riter->x_position!=m_xposition)&&(riter->y_position!=m_yposition))
	{
		Ropes rope;
		rope.x_position        =   m_xposition;
		rope.y_position        =   m_yposition;
		rope.m_ropesprite      =   m_Rope[0].m_ropesprite;
		rope.m_ropespritemid   =   m_Rope[0].m_ropesprite;
		m_Rope.push_back(rope);
	}

}
void CBullet::SetRopePosition(float x,float y)
{
	Ropes rope;
	rope.x_position				=   x;
	rope.y_position				=   y;
	rope.m_ropesprite			=   m_Rope[0].m_ropesprite;
	rope.m_ropespritemid		=   m_Rope[0].m_ropesprite;
	m_Rope.push_back(rope);
}
void CBullet::SetRopePosition(float x_bird,float y_bird,float x_wea,float y_wea)
{

	//******************清空vector中的元素********************//
	while(m_Rope.size()>2)
	{
		m_Rope.pop_back();
	} 
	//********************************************************//
	float a=abs(x_bird-x_wea);                     //椭圆x轴方向的长轴
	float b=abs(y_bird-y_wea);                     //椭圆y轴方向的长轴

	Ropes rope;

	//***********************计算绳子坐标*********************//
	if (x_bird>x_wea)
	{
		if(a<=b)
		{
			for(int i=2;i<b+2;i++)
			{
				rope.y_position			         =  y_wea-i+2;
				rope.x_position			         =	a*sqrt(1-(b-i+2)*(b-i+2)/(b*b))+x_wea;
				rope.m_ropesprite		         =	m_Rope[0].m_ropesprite;
				rope.m_ropespritemid	         =	m_Rope[0].m_ropespritemid;
				m_Rope.push_back(rope);
			}
		}
		else
		{
			for (int i=2;i<a+2;i++)
			{
				rope.x_position			         =  x_wea+i+2;
				rope.y_position			         =	b*sqrt(1-(i-2)*(i-2)/(a*a))+y_bird;
				rope.m_ropesprite		         =	m_Rope[0].m_ropesprite;
				rope.m_ropespritemid	         =	m_Rope[0].m_ropespritemid;
				m_Rope.push_back(rope);
			}
		}
	}

	else
	{
		if(a>=b)
		{
			for (int i=2;i<a+2;i++)
			{
				rope.x_position			         =  x_wea-i+2;
				rope.y_position			         =	b*sqrt(1-(i-2)*(i-2)/(a*a))+y_bird;
				rope.m_ropesprite		         =	m_Rope[0].m_ropesprite;
				rope.m_ropespritemid	         =	m_Rope[0].m_ropespritemid;
				m_Rope.push_back(rope);
			}
		}
		else
		{
			for (int i=2;i<b+2;i++)
			{
				rope.y_position			         =  y_wea-i+2;
				rope.x_position			         =	x_wea-a*sqrt(1-(b-i+2)*(b-i+2)/(b*b));
				rope.m_ropesprite		         =	m_Rope[0].m_ropesprite;
				rope.m_ropespritemid	         =	m_Rope[0].m_ropespritemid;
				m_Rope.push_back(rope);
			}
		}
	}
}
void CBullet::ClearRope()
{
	while(m_Rope.size()>2)
	{
		m_Rope.pop_back();
	} 
}
void CBullet::Renderrope()                                                    
{
	//vector<Ropes>::iterator itRope;                                           //定义一个rope的迭代器
	if(m_Rope.size()==2)
		m_Rope[0].m_ropesprite->Render(m_Rope[0].x_position,m_Rope[0].y_position);
	else
	{
		for (int i=1;i<m_Rope.size();i++)
		{	
			int m=m_Rope.size();
			m_Rope[i].m_ropesprite    ->Render(m_Rope[i].x_position,m_Rope[i].y_position);
			float x    =   (m_Rope[i].x_position+m_Rope[i-1].x_position)/2;
			float y    =   (m_Rope[i].y_position+m_Rope[i-1].y_position)/2;
			m_Rope[i].m_ropespritemid ->Render(x,y);

		}
	}
}
void CBullet::SetBulletStateInitial()
{
	BulletState		=	Initial;
}
void CBullet::SetBulletStatemove()
{
	BulletState= MOVE;
}
void CBullet::SetBulletStatecollsion()
{

	BulletState=collision;
}
void CBullet::SetRopeStateappear()
{
	RopeState=appear;
}
void CBullet::SetRopeStatedisappear()
{
	RopeState=disappear;
}
void CBullet::SetRopeStateInitial()
{
	RopeState=Initial;

}
ObjectState CBullet::GetBulletState()
{
	return BulletState;
}
ObjectState CBullet::GetRopeState()
{
	return RopeState;

}
