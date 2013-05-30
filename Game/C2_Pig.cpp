#include "C2_Pig.h"
#include<math.h>
float g1=40;
float g2=40;
float Speed1=10;                                     //跳跃时速度
float Speed2=1;                                      //静止时速度
float fps2;
float time;                                          //计算总的fps
C2_Pig::C2_Pig()
{
	/*1.头像加载
	2.生命值的确定
	3.*/
}

C2_Pig::C2_Pig(HGE *_hge)
{
	m_tex=0;
	m_hge  = _hge;     
	m_xposition = m_yposition = 600;
	PigState=Static;
}

C2_Pig::~C2_Pig()
{
	delete m_spr;
	m_hge->Texture_Free(m_tex);
	HTEXTURE tex;
}

void C2_Pig::SetImage(char* filename, int x_positon, int y_position, int width, int height)
{
	m_tex = m_hge->Texture_Load( filename );
	m_spr = new hgeSprite(m_tex, x_positon, y_position, width, height);
}
float C2_Pig::GetPositionX() const
{
	return m_xposition;
}

float C2_Pig::GetPositionY() const
{
	return m_yposition;
}
float C2_Pig::GetPigState()const
{
	return PigState;
}
void C2_Pig::SetPigStatejump()
{
	PigState=jump;
	
}
void C2_Pig::SetPigStatestatic()
{
	PigState=Static;
}


void C2_Pig::Render()
{
	m_spr->RenderEx(m_xposition, m_yposition,0);
}

void C2_Pig::move()
{
	fps2=m_hge->Timer_GetDelta();
	time+=fps2;
	if ((Speed1!=0)||(m_yposition!=610))
	{
			Speed1=Speed1-g1*fps2;
			if (m_yposition>700-90) Speed1=(-Speed1)*0.8;
		m_yposition-=Speed1;                                                 //y轴的坐标根据重力加速度不断变化
	}
	if(time>0.05)
	{
		PigState=Static;
		time=0;
		Speed1=10;
	}

}
void C2_Pig::VStatic()
{
	fps2=m_hge->Timer_GetDelta();
	Speed2=Speed2-g2*fps2;
	if (m_yposition>700-90) Speed2=(-Speed2)*0.8;
	m_yposition-=Speed2; 
	
}
