#include"CYoungPig1.h"
#include"CGlobal.h"

CYoungPig1::CYoungPig1()                                                            //��ʼ��С�����
{

}

CYoungPig1::CYoungPig1(HGE *_hge)
{
	this->m_hge     = _hge;
	this->m_life    = 100;                                                          //������100��Ѫ
	this->m_xposition  = 10;
	m_yposition      = 580;                                                         //��ʼ�����λ��;
	nfps            = 10;
	nframe          = 1;
	LoadTexture("������.png");
	SetImage(nframe,nfps,0,0,69,51);
	//Play();
	d_timer = 0;
	j_timer =0;
	setspeed(2,3);                                                            //����С��ĳ��ٶ�
	changetime         = 0;                                                           //��ʼ����ʱ��
	isjump = false;                                                               //��ʼ��Ծ���Ϊ��
	isuseweapon = false;  //��ʼʹ���������Ϊ��
	sndpigrun          = m_hge->Effect_Load("����.mp3");

	
}
                                                                             

bool CYoungPig1::Update()                                        //�ú���Ϊ���ƺ���������С����ƶ�

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

//�ú���ΪС��任װ���ĺ���
void CYoungPig1:: useweapon()                        
{   
	
	if (m_hge->Input_KeyDown(HGEK_A)) //��λ�õĴ��뻹�����൱������⣬��Ҫ׼ȷ�����̰��µ����
	{    

		                                               //��¼С������������
		if(changetime<=4)
		{   
			isuseweapon = true;   
			//this->LoadTexture("EntityPic.png");
			this->SetImage( 3, 10, 0,148,69, 51);                                //����
			this->Play();
			changetime++;
			if(changetime == 4)
 				isuseweapon = false;

		}

	}

	if(m_hge->Input_KeyDown(HGEK_S))


	{
		isuseweapon = false;                                                 //��׽С�������ʹ��״̬
        //this->LoadTexture("EntityPic.png");
		this->SetImage( 3, 10, 0,0,69, 52);
		this->Play();

	}

}

void  CYoungPig1::setspeed(float _dx,float _dy)                                       //�����ٶȺ���
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
