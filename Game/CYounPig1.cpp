#include"CYoungPig1.h"
#include"CGlobal.h"

CYoungPig1::CYoungPig1()                                                            //初始化小猪对象
{

}

CYoungPig1::CYoungPig1(HGE *_hge)
{
	this->m_hge     = _hge;
	this->m_life    = 100;                                                          //该猪有100滴血
	this->m_xposition  = 10;
	m_yposition      = 580;                                                         //初始化猪的位置;
	nfps            = 10;
	nframe          = 1;
	LoadTexture("猪猪侠.png");
	SetImage(nframe,nfps,0,0,69,51);
	//Play();
	d_timer = 0;
	j_timer =0;
	setspeed(2,3);                                                            //设置小猪的初速度
	changetime         = 0;                                                           //初始变身时间
	isjump = false;                                                               //初始跳跃标记为假
	isuseweapon = false;  //初始使用武器标记为假
	sndpigrun          = m_hge->Effect_Load("猪走.mp3");

	
}
                                                                             

bool CYoungPig1::Update()                                        //该函数为控制函数，控制小猪的移动

{

	float dt = m_hge->Timer_GetDelta();
	float  dx, dy;                         
	dx = d_x;
	dy = d_y;
	if (m_hge->Input_KeyDown( HGEK_ESCAPE))
		return true;

	if (m_hge->Input_KeyDown( HGEK_LEFT))
	{   
		//m_xposition  -= dx*dt*150;
		if(!isuseweapon)
		{
		//SetFrame(3);
		SetImage(3,10,0,51,69,51);
		Play();
		
		}
		else
		{
			//SetFrame(3);
			SetImage(3,10,0,100,69,51);
			Play();

		}
	//	m_hge->Effect_PlayEx(sndpigrun ,5);
	}

		
	if (m_hge->Input_KeyDown( HGEK_RIGHT))
	{
		m_xposition  += 3;
		if(!isuseweapon)
		{
		//SetFrame(3);
		SetImage(3,10,0,0,69,51);
		Play();
		}
		else
		{
			//SetFrame(3);
			SetImage(3,10,0,149,69,51);
			Play();
		}
		m_hge->Effect_PlayEx(sndpigrun ,20);
	}



	
	if(m_hge->Input_GetKeyState(HGEK_DOWN))

{
	d_timer += m_hge->Timer_GetDelta();

	m_yposition +=d_timer*5;
	//m_yposition +=5;
	if(m_yposition>580)
	{
		m_yposition = 580;
	//	d_timer = 0;
	}

	}

		
	return false;
}

//该函数为小猪变换装备的函数
void CYoungPig1:: useweapon()                        
{   
	
	if (m_hge->Input_KeyDown(HGEK_A)) //该位置的代码还存在相当大的问题，需要准确侦测键盘按下的情况
	{    

		                                               //记录小猪运用了武器
		if(changetime<=4)
		{   
			isuseweapon = true;   
			//this->LoadTexture("EntityPic.png");
			this->SetImage( 3, 10, 0,148,69, 51);                                //变身
			this->Play();
			changetime++;
			if(changetime == 4)
 				isuseweapon = false;

		}

	}

	if(m_hge->Input_KeyDown(HGEK_S))


	{
		isuseweapon = false;                                                 //捕捉小猪的武器使用状态
        //this->LoadTexture("EntityPic.png");
		this->SetImage( 3, 10, 0,0,69, 52);
		this->Play();

	}

}

void  CYoungPig1::setspeed(float _dx,float _dy)                                       //设置速度函数
{
	d_x  = _dx;
	d_y  = _dy;
}
void CYoungPig1::setlife(int _lif)
{
	m_life += _lif;
}
int CYoungPig1 ::Getlife()
{
	return m_life;
}

void  CYoungPig1::jump()
{      

		if (isjump)
		{
			float nfps = m_hge->Timer_GetDelta();
			d_y = d_y - nfps*12;
			m_yposition -= d_y;
			if(m_yposition>580)
			{
				isjump = false;
				d_y = 7;
			}
		}

}

void CYoungPig1::SetJump()
{
	isjump = true;
}


int CYoungPig1::getchangetime()
{   
	int n;
	n = changetime;
	return n;
}

int CYoungPig1::getspeedx()
{
	return d_x;
}
int CYoungPig1::getspeedy()
{
	return d_y;
}
void CYoungPig1::setchangetime(int T)
{
	changetime = T;
}


bool CYoungPig1::getuseweaponstate()
{
	return isuseweapon;
}



void CYoungPig1::setuseweaponstate()
{
	isuseweapon = false;
}


void CYoungPig1::Render()
{

float dt = m_hge->Timer_GetDelta();


if(m_hge->Input_GetKeyState(HGEK_RIGHT))
{
    m_xposition += 2;
	m_run->Render(m_xposition,m_yposition);
	m_run->Update(dt);
}
	
if(m_hge->Input_GetKeyState(HGEK_LEFT))
{
m_xposition -= 2.2;
m_run->Render(m_xposition,m_yposition);
m_run->Update(dt);
}


m_run->Render(m_xposition,m_yposition);
m_run->Update(dt);
}


CYoungPig1::~CYoungPig1()
{
	m_hge->Release();
	m_hge->System_Shutdown();
	m_hge->Effect_Free(sndpigrun );
}
