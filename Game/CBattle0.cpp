#include "CBattle0.h"
#include "CGlobal.h"
#include <math.h>
class CGame; //��ΪҪʹ��WIN_WIDTH��WIN_HEIGHT;

float _timermenege_update = 0;
CBattle0::CBattle0(HGE *_hge)
{   

	_timer  = 0;
	_timer0 = 0;
	_timer1 = 0;
	_timer2 = 0;
	_timer3 = 0;
	_timer4 = 0;
	_timer5 = 0;
	_timer6 = 0;
	b_dx    = 0.1;
	b_x     = 0;
	b_y     = 0;
	FireX  =  0; 

	N       = 0;
	m_hge = _hge;
	timeflage = false;
	by_bombed = false;
	gamestart = false;

	battle00_status = false;

}




CBattle0::~CBattle0()
{

}

/*************************************************************/
/*********************����Ϸ��Դ������ս��********************************/
/****************************************************************************************/
/*************************************************************************************************/

void CBattle0::Init()
{

	
fnt=new hgeFont("font1.fnt");               //��������;
//********************���ر�������*****************************************
 m_background[0] = new CBackground(m_hge);
 m_background[1] = new CBackground(m_hge);
 m_background[2] = new CBackground(m_hge);
 m_background[3] = new CBackground(m_hge);
 m_background[4] = new CBackground(m_hge);
 m_background[5] = new CBackground(m_hge);
// 
 m_background[0]->LoadTexture("Demo1.png");
 m_background[1]->LoadTexture("Demo2.png");
  m_background[2]->LoadTexture("Demo3.png");
 m_background[3]->LoadTexture("Demo4.png");
 m_background[4]->LoadTexture("Demo5.png");
 m_background[5]->LoadTexture("Demo6.png");
// 
 m_background[0]->SetImage1(0,0,3072, 768); 
 m_background[1]->SetImage1(0,0,3072,768); 
 m_background[2]->SetImage1(0,0,3072,768); 
 m_background[3]->SetImage1(0,0,3072,768); 
 m_background[4]->SetImage1(0,0,3072,768); 
 m_background[5]->SetImage1(0,0,3072,768); 
// 

 m_background[1]->SetPositionX(3070);
 m_background[2]->SetPositionX(6139);
 m_background[3]->SetPositionX(9210);
 m_background[4]->SetPositionX(12281);
 m_background[5]->SetPositionX(15352);

 texbg = m_hge->Texture_Load("����.png");
 m_sprbg = new hgeSprite(texbg,0,0,1300,150);

// 	if (!m_bktex)
// 	{
// 		MessageBox(NULL, L"���ܼ���Bg1.png", L"Error",MB_OK | MB_ICONERROR | MB_APPLMODAL);
// 	}

//******************************************************************************************************



/*************************************************************************************/
/******                    ����С��                                      *************/
/*************************************************************************************/
/****************************�����µ���*************************************/

	for(int k = 0;k<4;k++)                     //������ֻ�����µ���
	{   
		m_eggBird[k] = new CAnimEggBird(m_hge);

		m_eggBird[k]->LoadTexture("�µ���.png");
		m_eggBird[k]->SetImage(4,10,0,0,65,61.8);
        m_eggBird[k]->Play();
		m_eggBird[k]->SetPositionX(1200+400*k);
		m_eggBird[k]->SetPositionY(100);
        m_eggBird[k]->SetSpeedX(3);
		AnimBird[k] = m_eggBird[k];
	}

//*************************************��****************************************/
	for (int k=0; k<4; k++)       
	{
		m_egg[k] = new CEgg(m_hge);                   
		m_egg[k]->LoadTexture("��.png");
		m_egg[k]->SetImage1( 0, 0, 36, 44);
	}

/**********************************************************************************/

/****************************��������****************************************/
	for(int k = 4;k<8; k++)
	{
		runbrid[k-4] = new CAnimEggBird(m_hge);
		runbrid[k-4]->LoadTexture("����.png");
		runbrid[k-4]->SetImage(7,10,0,0,151,122);
		runbrid[k-4]->Play();
		runbrid[k-4]->SetSpeedX(3);
		runbrid[k-4]->SetPositionX(1200 + 600*(k-4));
		runbrid[k-4]->SetPositionY(515);
		AnimBird[k] = runbrid[k-4];
	}

	/*********************************************************************************/

/*****************************�����ƶ���********************************/
	for(int k = 8;k<12; k++)
	{
		runbrid[k-8] = new CAnimEggBird(m_hge);
		runbrid[k-8]->LoadTexture("���湥��(1).png");
		runbrid[k-8]->SetImage(6,10,0,0,107,65);
		runbrid[k-8]->Play();
		runbrid[k-8]->SetSpeedX(2);
		runbrid[k-8]->SetPositionX(1200 + 400*(k-8));
		runbrid[k-8]->SetPositionY(575);
		AnimBird[k] = runbrid[k-8];
	}

/********************************************************************************************/

	/************************����������*************************************/

	for(int k = 12;k<16;k++)
	{
		swoopattrackbird[k-12] = new CAnimSwoopBird(m_hge);
		swoopattrackbird[k-12]->SetPositionX(1300+600*(k-12));
		swoopattrackbird[k-12]->SetSpeedX(3);
		AnimBird[k] = swoopattrackbird[k-12];
	}

	/**********************************************************************************/


	/**********************·����***********************************************************/

	for(int k = 16; k<20; k++)
	{
		movedownbird[k-16] = new CAnimMoveDownBird(m_hge);
		movedownbird[k-16]->SetPositionX(1200);
		movedownbird[k-16]->SetPositionY(-100-(k-16)*400);
		movedownbird[k-16]->SetSpeedY(5);
		movedownbird[k-16]->SetSpeedX(2);
		AnimBird[k] = movedownbird[k-16];
	}


	/********************************��������**************************************************/
	for(int k = 20;k<24;k++)
	{
		dragon[k-20] = new CAnimDragon(m_hge);
		dragon[k-20]->SetPositionX(1200+(k-20)*600);
		dragon[k-20]->SetPositionY(50);
		dragon[k-20]->SetSpeedX(3);
		AnimBird[k] = dragon[k-20];
	}
	

	/**************************����С��**********************************************************/

	m_youngpig1 = new CYoungPig1(m_hge);      //�½�һֻ��;

	/**************************************************************************************************



	/*********************************************************************************************/
	/**************************************����ϵͳʵ�ִ���*********************/
	tex=m_hge->Texture_Load("EntityPic.png");
	spt=new hgeSprite(tex, 998, 797, 48, 48);
	spt->SetBlendMode(BLEND_COLORMUL | BLEND_ALPHAADD | BLEND_NOZWRITE);
	spt->SetHotSpot(16,16);
	par=new hgeParticleSystem("trail.psi",spt);
	par->Fire();

	/****************************************************************************************/
	m_fire  =   m_hge -> Texture_Load("��.png");
	m_sptfire   =   new hgeSprite(m_fire,0,0,110,120);        //����ϵͳ
	m_sptfire   ->  SetBlendMode(BLEND_COLORMUL | BLEND_ALPHAADD | BLEND_NOZWRITE);//����ϵͳ
	m_sptfire   ->  SetHotSpot(50,50);   

	for (int i=0;i<32;i++)
	{
		part[i]  =   new hgeParticleSystem("trail.psi",m_sptfire);  //����ϵͳ
		part[i]  ->  Fire();   //��������ϵͳ
		part[i]  ->  info.nEmission=50;//����ϵͳ 
	}
	/**************************************************************************************************/


	/*******************************************************************************************/
/***************************��������*********************************/

	sndeggbird =m_hge->Effect_Load("bird misc a8.wav");
	sndmovebird=m_hge->Effect_Load("Ѽ��.mp3");
    sndswoopattrackbird=m_hge->Effect_Load("ӥ.mp3");
	sndrunbrid=m_hge->Effect_Load("���.mp3");
    snddragon  =m_hge->Effect_Load("��.mp3");

    sndpigbyattrack    =m_hge->Effect_Load("����.mp3");
//	sndpigrun          = m_hge->Effect_Load("����.mp3");
	sndmovedownbird    = m_hge->Effect_Load("Сȸ.mp3");
	sndeggbreak        =  m_hge->Effect_Load("CreatBullet.WAV");  
	sndhorserun        = m_hge->Effect_Load("������.mp3");
}

/*******************************************/



 


/*********************�߼�����*********************************/
//*******************************************************************************************************

bool CBattle0::Run() //ÿ֡���øú�����ÿ��100֡����;
{
	//���ⲿ��ʵ���߼��жϺ��߼�����,���������ƶ�����ײ���;
	_timer2 = m_hge->Timer_GetDelta();
	par->info.nEmission=(int)((m_youngpig1->getspeedx())*(m_youngpig1->getspeedx())
		+(m_youngpig1->getspeedy())*(m_youngpig1->getspeedy()))*2;
	par->MoveTo(m_youngpig1->GetPositionX()+20,m_youngpig1->GetPositionY()+40);
	par->Update(_timer2);



//*******************��Ϸʱ���ʱ*****************************************


	if(m_youngpig1->GetPositionX()>200)
		gamestart = true;

	if(!gamestart)
	{
		_timer7 = (int)m_hge->Timer_GetTime();
	}

	if(gamestart)
	{
	_timermenege_update += m_hge->Timer_GetDelta();
	_timer6 =(int)m_hge->Timer_GetTime();
	}

	
//************************************************************************************************


//***************************************************************************
//******************����С��ĳ������Σ�����ʱ��***********
//******************************************************************************************

TimerMenege_Update(_timermenege_update);


/*************************�Ƴ�������������************************************************/
if(_timermenege_update>10)
	//status = true;

//if(m_youngpig1->Getlife()<=0)
//	status = true;


if(m_background[5]->GetPositionX()<=-2000&&m_youngpig1->GetPositionX()>800)
	battle00_status = true;
/*****************************************************************************************/
for(int k =0;k<24;k++)
{  if(m_youngpig1->GetPositionX()>300&&m_youngpig1->GetPositionX()<950)
	AnimBird[k]->MoveFollowBgroud();
}


//�������񿴵�С���ǿ������³�Ŀ���
	for(int k = 12;k<16;k++)
	{
		if(swoopattrackbird[k]->GetPositionX()-m_youngpig1->GetPositionX()>200&&
			swoopattrackbird[k]->GetPositionX()-m_youngpig1->GetPositionX()<600)
			swoopattrackbird[k]->SetStase();//���غ�������С�����³�
	}
//�����񿴵�С��ʱ�������µĿ���

	for(int k = 20;k<24;k++)
	{
		if(dragon[k]->GetPositionX()-m_youngpig1->GetPositionX()>300&&
			dragon[k]->GetPositionX()-m_youngpig1->GetPositionX()<600)
		dragon[k]->SetStase();//���غ�������С�����³�
	}

//******************************************��ըС����***************************

	for(int m=0;m<4;m++)
	{
		//m_blackbirds[m]->SetSpeed(-2.0);
		if(m_eggBird[m]->GetPositionX()>m_youngpig1->GetPositionX()
					-30&&m_eggBird[m]->GetPositionX()<m_youngpig1->GetPositionX()-25)
					
		{   
			//m_egg[m]->SetPositionY(-60);
			m_egg[m]->SetPositionX(m_eggBird[m]->GetPositionX());
			m_egg[m]->SetPositionY(m_eggBird[m]->GetPositionY()+30);
			m_egg[m]->SetSpeed(5);
		
			

		}

	}
	//*****************************************************************************************


	/*****************************С��߽�����********************************************/

	for (int j=0; j<24; j++)  //�ж����Ƿ����;
	{
		if (AnimBird[j]->GetPositionX()< -100)
		{
			AnimBird[j]->SetPositionX(1200);
		}
	}
	/******************************************************************************/


	//*****��֤С���ڱ߽緶Χ�ڻ�� ���б߽���;******************************************
	if (m_youngpig1->GetPositionX() < 1)
		m_youngpig1->SetPositionX(1);
	if(m_youngpig1->GetPositionX() > 920)
		m_youngpig1->SetPositionX(920);
	if (m_youngpig1->GetPositionY() <1)
		m_youngpig1->SetPositionY(1);
	if(m_youngpig1->GetPositionY() > 580)
		m_youngpig1->SetPositionY(580);

/***********************************************************************************************/

	if(attack_by_egg())
	{   
		//	_timer4 += m_hge->Timer_GetDelta();                                  //�ָ�ԭ�ٶȵļ�ʱ��
		settimeflage();
		if(!m_youngpig1->getuseweaponstate())
		{
			settimeflage_speed();
			m_youngpig1->setspeed(0.2,0.2);
			m_youngpig1->SetPositionX(m_youngpig1->GetPositionX()-20);
			m_youngpig1->SetPositionY(m_youngpig1->GetPositionY()-50);
			m_youngpig1->setlife(-10);
			m_hge->Effect_PlayEx( sndpigbyattrack,10,12,5);
			by_bombed = true;
		}

	}

//	attack_by_animbird();
	//**************************С��ը�ɺ�ɻ���****************************************
//*******************************************************************************
	if( by_bombed)
	{
       Pigdown();
	//   by_bombed = false;

	}


	if(attack_by_animbird())
	{
		Pigdown();
	}
//*********************************************************************************

//*****�����û�д���С���������߽�֮�󽫵����·Ż������õ�С���λ��****************
	for(int m =0;m<4;m++)
	{

		if(m_egg[m]->GetPositionY()>580)
		{

			_timer3 += m_hge->Timer_GetDelta();
			

			m_egg[m]->SetImage1(36, 0, 40, 44);
		}

		if(_timer3 >0.1)
		{
			m_hge->Effect_PlayEx(sndeggbreak,10,5,0,false);
			m_egg[m]->SetImage1(0, 0, 36, 44);
			m_egg[m]->SetPositionY(m_eggBird[m]->GetPositionY()-800);
			m_egg[m]->SetPositionX(m_eggBird[m]->GetPositionX()-10);
			m_egg[m]->SetSpeed(0);


			if(m_eggBird[m]->GetPositionX()>m_youngpig1->GetPositionX()
				-10&&m_eggBird[m]->GetPositionX()<m_youngpig1->GetPositionX())
			{   
				//m_egg[m]->SetPositionY(-60);
				m_egg[m]->SetPositionX(m_eggBird[m]->GetPositionX());
				m_egg[m]->SetPositionY(m_eggBird[m]->GetPositionY()+30);
				m_egg[m]->SetSpeed(3);

			}

			_timer3 = 0;

		}
	}

	//*********************************************************************************

	//���С��ײ�ˣ���ʼ��ʱ
	gettime();
	gettime_speed();

	if(_timer0 > 0.1)
	{   
		if(!m_youngpig1->getuseweaponstate())
		m_youngpig1->SetImage(3,6, 0, 262, 120, 59);
		m_youngpig1->Play();
		//	m_youngpig1->SetImage( 591, 679, 54, 54);
		timeflage =false;
		_timer0 = 0;
	}

	if(_timer4 > 20)
	{   
		m_youngpig1->setspeed(1.5,3);
		timeflage1 =false;
		_timer4 = 0;
	}

	//ͨ���ô�����С��װ�������ʱ�䳤��
	_timer1 += m_hge->Timer_GetDelta();

	if(_timer1>10)
	{
		int n = m_youngpig1->getchangetime();
		if(n>=1)
		{
		//	m_youngpig1->setlife(-10);
			m_youngpig1->SetImage( 3, 6, 0, 0,67,49);
			m_youngpig1->Play();
			

		}
		m_youngpig1->setuseweaponstate();
		_timer1 = 0;

	}
	//	m_jumpbird->jump();
	//���øú�����С����м��̿���;
	if(m_youngpig1->GetPositionX()>200&&m_youngpig1->GetPositionX()<=920)
	{
		for(int i = 0;i<6;i++)
		{
			if(m_background[5]->GetPositionX()>-2000)
			m_background[i]->control();
		}
	}



	if( m_youngpig1->Update()) 
		battle00_status = true;

	return battle00_status;
}


//****************************************
/***************************����ʵ��************************/
//*************************************************************************************************

bool CBattle0::Render()
{
	//ʵ�ֳ����Ļ��ƣ���������������ȵ�;
	m_hge->Gfx_BeginScene();
	m_hge->Gfx_Clear(0);



	for(int i = 0; i<6;i++)
	m_background[i]->move();     //�����ƶ�����ͼ
		
    par->Render();
	m_youngpig1->Render();


	//*******************�����************************/

 /* for(int i=0;i<4;i++)
	  
  {
	  if(dragon[i]->GetPositionX()<800&&dragon[i]->GetPositionX()>200)
         DragonFire();
  }*/

	

TimerMenege_Render(_timermenege_update);
	

	m_youngpig1->useweapon();
	//bool  flag = false;
	if(m_hge->Input_GetKeyState(HGEK_UP))
	{
		m_youngpig1->SetJump();
			
	}
	
	m_youngpig1->jump();
	

	for(int m=0;m<4;m++)
		m_egg[m]->Show();

	fnt->printf(5, 5, HGETEXT_LEFT, "BLOOD:%d",m_youngpig1->Getlife());

	if(_timer6>_timer7)
	fnt->printf(5,50,HGETEXT_LEFT,"TIMEGO:%d",(_timer6-_timer7) );
	
	m_sprbg->Render(0,628);

	

	m_hge->Gfx_EndScene();
	return false;


}

bool CBattle0::attack_by_egg()
{  
	for(int m =0;m<4;m++)
	{
		float a = m_youngpig1->GetPositionX()-m_egg[m]->GetPositionX();
		float b = m_youngpig1->GetPositionY()-m_egg[m]->GetPositionY();

		if(a>-55&&a<60)
			if(b>-55&&b<60)
			{

				_timer += m_hge->Timer_GetDelta();
				m_egg[m]->SetImage1(36,0,40,44);
				if(m_youngpig1->getuseweaponstate()!=true)                           //���С��û������������С���ҵ���任һ��ͼƬ
				{
					//m_youngpig1->SetImage( 455, 289, 54, 50);
				}

				if(_timer>0.1)
				{   
					m_egg[m]->SetImage1( 0, 0, 36, 44);
					m_egg[m]->SetPositionY(m_eggBird[m]->GetPositionY()-300);
					m_egg[m]->SetPositionX(m_eggBird[m]->GetPositionX()-10);
					m_egg[m]->SetSpeed(0);
					_timer = 0;
				}


				if(m_eggBird[m]->GetPositionX()>m_youngpig1->GetPositionX()
					-10&&m_eggBird[m]->GetPositionX()<m_youngpig1->GetPositionX())
				{   
					//m_egg[m]->SetPositionY(-60);
					m_egg[m]->SetPositionX(m_eggBird[m]->GetPositionX());
					m_egg[m]->SetPositionY(m_eggBird[m]->GetPositionY()+30);
					m_egg[m]->SetSpeed(0.8);

				}
				return true;
			}
		
	}

	return  false;
}
void  CBattle0::settimeflage()
{
	timeflage = true;
}

void CBattle0::settimeflage_speed()
{
	timeflage1 = true;
}
void CBattle0::gettime()
{
	if(timeflage)
	{
		_timer0 += m_hge->Timer_GetDelta();
	}
}

void CBattle0::gettime_speed()
{
	if(timeflage1)
	{
		_timer4 += m_hge->Timer_GetDelta();
	}
}





bool CBattle0::attack_by_animbird()
{   

	for(int i = 0; i<24;i++)
	{

		float pig_cirlex = m_youngpig1->GetPositionX()+20;
		float pig_cirley = m_youngpig1->GetPositionY()+20;

		
		float bird_cirlex = AnimBird[i]->GetPositionX()+(AnimBird[i]->GetWidth())/2;
		float bird_cirley = AnimBird[i]->GetPositionY()+(AnimBird[i]->GetHeight())/2;

		float  a = abs(pig_cirlex-bird_cirlex);
		float  b = abs(pig_cirley-bird_cirley);

		float  c = sqrt((a*a+b*b));

	//	if(a>-(AnimBird[i]->GetWidth()-60)&&a<50)
	//		if(b>-(AnimBird[i]->GetHeight()-40)&&b<50)

		if(c>10&&c<(AnimBird[i]->GetWidth()/4))
			{
				if(m_youngpig1->getuseweaponstate()!=true)                           //���С��û������������С���ҵ���任һ��ͼƬ
				{
					m_youngpig1->SetPositionX(m_youngpig1->GetPositionX()-40);
					m_youngpig1->SetPositionY(m_youngpig1->GetPositionY()-200);
					m_youngpig1->setlife(-20);
					m_youngpig1->SetImage(3,6, 0, 262, 120, 59);
					m_youngpig1->Play();
				    m_hge->Effect_PlayEx( sndpigbyattrack,10,12,5);
					by_bombed = true;

				}

				return true;
			}


	}
	return  false;

}


/**************************************************************************/
//**********************����������Ϸ��ĳ���˳�򣬳���ʱ�䣬��Ϸ�Ľ���ʱ��/
//***********************�����߼�**************************************************/
//*****************************************************************************************/

bool CBattle0::TimerMenege_Update(float &dt)
{
	if(dt>0&&dt<20)
	{
		for(int k = 0;k<4; k++)
		{
			AnimBird[k]->Update();

		//	m_hge->Effect_PlayEx( sndeggbird,10);
		
		}
			//return false;

	}
	if(dt>=20&&dt<=22)
	{
		for(int k = 0;k<4;k++)
		{
			AnimBird[k]->SetPositionX(1200+k*400);
			AnimBird[k]->SetPositionY(30);

		}
		//return false;
	}
	if(dt>22&&dt<52)
	{   
		
		for(int k = 4;k<8; k++)
		{
			AnimBird[k]->Update();
		   // m_hge->Effect_PlayEx( sndrunbrid,10,0,1,false);
			
			
		}
		//return false;
	}
	if(dt>52&&dt<54)
	{
		for(int k = 4;k<8; k++)
		{
			AnimBird[k]->SetPositionX(1200+(k-4)*400);
			AnimBird[k]->SetPositionY(515);

		}
		//return false;
	}


	if(dt>54&&dt<74)
	{
		for(int k = 8;k<12;k++)
		{
			AnimBird[k]->Update();
			//	m_hge->Effect_PlayEx( sndmovebird,5);
			
		}
		//return  false;
	}

	if(dt>74&&dt<76)
	{
		for(int k = 8;k<12;k++)
		{
			AnimBird[k]->SetPositionX(1200+(k-8)*200);
			AnimBird[k]->SetPositionY(575);

		}
		//return  false;
	}

	if(dt>76&&dt<105)
	{
		for(int k = 12;k<16;k++)
		{
			AnimBird[k]->Update();
		   
		//	m_hge->Effect_PlayEx( sndswoopattrackbird,5);
		}
		///return false;
	}

	if(dt>105&&dt<107)
	{
		for(int k = 12;k<16;k++)
		{
			AnimBird[k]->SetPositionX(1200+(k-12)*600);
            AnimBird[k]->SetPositionY(50);
		}
		//return false;
	}

	if(dt>107&&dt<147)
	{
		for(int k = 16;k<20;k++)
		{
			AnimBird[k]->Update();
			
		//	 m_hge->Effect_PlayEx( sndmovedownbird  ,5);
			
		}
		//return false;

	}
	if(dt>147&&dt<149)
	{
		for(int k = 16;k<20;k++)
		{
			AnimBird[k]->SetPositionX(1200);
			AnimBird[k]->SetPositionY(50-(k-16)*400);

		}
		//return false;

	}

	if(dt>149&&dt<180)
	{
		if(m_youngpig1->GetPositionX()<800)
		{
		for(int k = 20;k<24;k++)
		{
			AnimBird[k]->Update();
			m_youngpig1->setspeed(2,0);
		//	m_hge->Effect_PlayEx( snddragon,5);
		}
		}
		//return false;
	}

	if(dt>180&&dt<185)
	{
		for(int k = 20;k<24;k++)
		{
			AnimBird[k]->SetPositionX(1200+(k-20)*600);
			AnimBird[k]->SetPositionY(50);
		}
		//return false;
	}


	if(dt>200)
	{
		dt = 0;
		return true;
	}
}


/**************************************************************************/
//**********************����������Ϸ��ĳ���˳�򣬳���ʱ�䣬��Ϸ�Ľ���ʱ��/
//***********************���ƻ���**************************************************/
//*****************************************************************************************/

bool CBattle0::TimerMenege_Render(float &dt)
{
	if(dt>0&&dt<20)
	{
		for(int k = 0;k<4; k++)
		{
			AnimBird[k]->Render();

			m_hge->Effect_PlayEx( sndeggbird,10);
		
		}
			//return false;

	}
	if(dt>=20&&dt<=22)
	{
		for(int k = 0;k<4;k++)
		{
			AnimBird[k]->SetPositionX(1200+k*400);
			AnimBird[k]->SetPositionY(30);

		}
		//return false;
	}
	if(dt>22&&dt<52)
	{   
		
		for(int k = 4;k<8; k++)
		{
			AnimBird[k]->Render();
		    m_hge->Effect_PlayEx( sndrunbrid,10,0,1,false);
			
			
		}
		//return false;
	}
	if(dt>52&&dt<54)
	{
		for(int k = 4;k<8; k++)
		{
			AnimBird[k]->SetPositionX(1200+(k-4)*400);
			AnimBird[k]->SetPositionY(515);

		}
		//return false;
	}


	if(dt>54&&dt<74)
	{
		for(int k = 8;k<12;k++)
		{
			AnimBird[k]->Render();
				m_hge->Effect_PlayEx( sndmovebird,5);
			
		}
		//return  false;
	}

	if(dt>74&&dt<76)
	{
		for(int k = 8;k<12;k++)
		{
			AnimBird[k]->SetPositionX(1200+(k-8)*200);
			AnimBird[k]->SetPositionY(575);

		}
		//return  false;
	}

	if(dt>76&&dt<105)
	{
		for(int k = 12;k<16;k++)
		{
			AnimBird[k]->Render();
		   
			m_hge->Effect_PlayEx( sndswoopattrackbird,5);
		}
		///return false;
	}

	if(dt>105&&dt<107)
	{
		for(int k = 12;k<16;k++)
		{
			AnimBird[k]->SetPositionX(1200+(k-12)*600);
            AnimBird[k]->SetPositionY(50);
		}
		//return false;
	}

	if(dt>107&&dt<147)
	{
		for(int k = 16;k<20;k++)
		{
			AnimBird[k]->Render();
			
			 m_hge->Effect_PlayEx( sndmovedownbird  ,5);
			
		}
		//return false;

	}
	if(dt>147&&dt<149)
	{
		for(int k = 16;k<20;k++)
		{
			AnimBird[k]->SetPositionX(1200);
			AnimBird[k]->SetPositionY(50-(k-16)*400);

		}
		//return false;

	}

	if(dt>149&&dt<180)
	{

		if(m_youngpig1->GetPositionX()<800)
		{
		for(int k = 20;k<24;k++)
		{
			AnimBird[k]->Render();
			if(AnimBird[k]->GetPositionX()<700&&AnimBird[k]->GetPositionX()>200)
				DragonFire();
			m_hge->Effect_PlayEx( snddragon,5);
		}
		}
		//return false;	
		//return false;
	}

	if(dt>180&&dt<185)
	{
		for(int k = 20;k<24;k++)
		{
			AnimBird[k]->SetPositionX(1200+(k-20)*600);
			AnimBird[k]->SetPositionY(50);
		}
		//return false;
	}


	if(dt>200)
	{
		dt = 0;
		return true;
	}
}


//*******************************С��ը֮����䵽����**************************/
void CBattle0::Pigdown()
{
	_timer5 += m_hge->Timer_GetDelta();    
	m_youngpig1->SetPositionY(m_youngpig1->GetPositionY()+10*_timer5);
	if(m_youngpig1->GetPositionY()>580)
	{
		m_youngpig1->SetPositionY(580);
	    _timer5 = 0;
		by_bombed = false;
	}

}

//*********************************************************************************************



void CBattle0::DragonFire()
{
	float dt       =   m_hge -> Timer_GetDelta();
	float FireY    =   m_hge -> Random_Int(0,768);
	FireX         =   32;

	if ( FireX >= 1024)  FireX =  0;

	for (int i = 0;i < 32;i++)
	{
		part[i]  ->  MoveTo(1+(i+1)* FireX, FireY);
		part[i]  ->  Update(dt);
		part[i]  ->  Render();
	}


}

void CBattle0::Release()
{
	delete    m_bkspr;
	delete    fnt;
	delete    []m_egg;


	delete    []m_eggBird;
	delete    []movedownbird;
	delete    []runbrid;
	delete    []swoopattrackbird;
	delete    []dragon;
	delete    []part;
	delete    m_youngpig1;
	delete    m_sprbg;

	m_hge->Texture_Free(m_bktex);
	m_hge->Target_Free(texbg);
	m_hge->Effect_Free(snd);
	m_hge->Effect_Free(sndeggbird);
	m_hge->Effect_Free(sndmovebird);
    m_hge->Effect_Free(sndswoopattrackbird);
	m_hge->Effect_Free(sndrunbrid);
    m_hge->Effect_Free(snddragon);
    m_hge->Effect_Free(sndpigrun); 
}

