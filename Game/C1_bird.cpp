#include "C1_bird.h"
#include<math.h>

//把鸟的绘制全部换成动画方式，不要精灵绘制，最后再加上花的效果
C1_bird::C1_bird()
{
	/*1.头像加载
	2.生命值的确定
	3.*/
}

C1_bird::~C1_bird()
{
	
}
float C1_bird::GetPositionX() const
{
	return m_xposition;
}
float C1_bird::GetPositionY() const
{
	return m_yposition;
}
float C1_bird::GetScale() const
{
	return scale;
}
int   C1_bird::getScore()
{
	return birdScore;
}
bool flag = true;
float dt = 0;
float   C1_bird::GetBirdPull()
{
	
	//birdPull与时间t是过原点且位于第一象限(a<0,b>0)的y=ax*x+bx函数，当x=-2a/b时y取最大值，斜率为y'=2ax+b
	//说明鸟的拉力最开始增大得快，然后慢慢增加，最后再通过maxBirdPull来使第二次的斜率值变小即增加变慢
	//每变一次应该让maxBirdPull通过birdEnergy的控制有所减少，使最大值减少
	if (flag)
	{
		dt      +=  m_hge->Timer_GetDelta();	
		if (dt>=1)  flag = false;
	}
	else
	{
		dt       -= m_hge->Timer_GetDelta();
		if(dt<=0)   flag = true;
	}
	//float x1 =  pow(dt,40);
	//float x2 =  pow(dt,20);
	birdPull =  -maxBirdPull * dt*dt +2 * maxBirdPull * dt;
	maxBirdPull -= 10       * m_hge -> Timer_GetDelta(); //每秒减少10
	birdEnergy  -= birdPull * m_hge -> Timer_GetDelta();//鸟每拉一次体能都会有所下降
	if (birdEnergy<=0||maxBirdPull<=0) //鸟拉30次
	{
		birdPull = 0;
	}
	//差一个边界检测函数
	edgeDetection();
	return birdPull;
}
void C1_bird::initialState()
{
	m_xposition = initPositionX;
	m_yposition = initPositionY;
	x_speed     = initSpeedX;
	y_speed     = initSpeedY;
	maxBirdPull = 800;
	birdPull    = 0;
	m_player    ->SetSpeed(6);
	m_player    ->SetFlip(true,false);
	birdEnergy  = 30000;
}
bool C1_bird::edgeDetection()
{
	if (m_xposition < -100||m_xposition > 1024||m_yposition < -height)
	{		
		return true;
	}
	
	//下边界留着表示被抓住
	return false;
}
void C1_bird::SetScale(float Scale)
{
	scale = Scale;
}
void C1_bird::SetPosition(float _x, float _y)
{
	m_xposition = _x;
	m_yposition = _y;
}
void C1_bird::SetSpeed(float xspeed,float yspeed)
{
	initSpeedX = xspeed;
	initSpeedY = yspeed;
	x_speed  =  xspeed;
	y_speed  =  yspeed;
}
void C1_bird::SetSpeed(int weaponPull,float weaponPositionX, float weaponPositionY)
{
	//1,根据枪和鸟的坐标逐渐更改图片的方向
	
	//中间变量x、y、z不用考虑
	float   x =  (m_xposition - weaponPositionX);
	float   y = -(m_yposition - weaponPositionY);
	//float slope = y / x;//tan值
	//angle =  atan(slope);
	float   z = sqrt((x*x+y*y));
	//让鸟的力度方向在第一象限内即角度在0--90度之间
	float   randomBird =  m_hge->Random_Float(0,1.5707963);
	
	int pullBirdX      =  birdPull * cos(randomBird);
	int pullBirdY      =  birdPull * sin(randomBird);
	int pullWeaponX    =  weaponPull*(x/z);//枪沿X方向分力
	int pullWeaponY    =  weaponPull*(y/z);//枪沿Y方向分力
	//2，通过合力的判断鸟加速度方向，暂时忽略鸟的重力
	float ax     =   -(pullWeaponX - pullBirdX) / birdQuality;
	float ay     =    (pullWeaponY - pullBirdY) / birdQuality;
	//3，鸟速度XY轴的改变
	float time   =   0.01;//time后期需要改变
	if (x_speed <=3 &&x_speed>=-3)
	{
		x_speed     +=   ax*time;	
	}
	if (y_speed<=1&&y_speed>=-1)
	{
		y_speed     +=   ay*time;
	}
	m_xposition +=   x_speed;
	m_yposition +=   y_speed;
	
}
void C1_bird::SetBirdPull(int birdpull)
{
	birdPull  =  birdpull;
}
void C1_bird::Fly()
{
// 	//鸟的大小变化的快慢
// 	if (m_xposition <= random)
// 	{
// 		scale -= 0.003; 
// 	} 
// 	else
// 	{
// 		scale += 0.003;
// 	}
	if (initPositionX == 0)
	{
		m_xposition += x_speed;
		m_yposition += y_speed;
	}
	else
	{
		m_xposition -= x_speed;
		m_yposition -= y_speed;
	}
	if(edgeDetection())initialState();
	m_player->Update(0.01f);
	m_player->Render(m_xposition,m_yposition);
	//m_player->RenderEx(m_xposition, m_yposition,0,scale);
	
}

bool C1_bird::isBirdAttacked(float& bulletPositionX,float& bulletPositionY)
{
		bulletPositionX  =  m_xposition + width/2;
		bulletPositionY  =  m_yposition + height/2;

		if(x_speed<0)m_player->SetFlip(false,false);
		else m_player->SetFlip(true,false);
		m_player->Update(0.01f);
		m_player->Render(m_xposition,m_yposition);
		if (m_yposition >= 615-height)
		{
			return true;
		}
		if(rand()%2==1)
		{
			bulletPositionX += rand()%2;
		}
		else
		{
			bulletPositionX -= rand()%2;
		}
	
	return false;
}
float C1_bird::GetBirdWidth()const
{
	return width;
}
float C1_bird::GetBirdHeight()const
{
	return height;
}
//以下为动画效果控制的鸟，其实就是绘制时把精灵换成动画类
void C1_bird::SetPlayMode(int mode)
{
	m_player->SetMode(mode);
	m_player->Play();
}
void C1_bird::SetImage(char* fileName, int x_position, int y_position, int _width, int _height,float& _volume)
{
	filename = fileName;
	width    = _width;
	height   = _height;
	volume   = _volume;
	bird_position_px = x_position;
	bird_position_py = y_position;
	m_tex    = m_hge->Texture_Load(fileName);
	m_player = new hgeAnimation(m_tex,10,10,x_position,y_position,width,height);
	m_player ->SetFlip(true,false);
}