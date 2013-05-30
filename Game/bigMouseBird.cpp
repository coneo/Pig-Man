#include "bigMouseBird.h"
#include <hge.h>
bigMouseBird::bigMouseBird()
{

}
bigMouseBird::bigMouseBird(HGE* hge,float initX, float initY, int score,char* musicFly,char* musicDead)
{
	m_tex         =  0;
	scale         =  1;
	m_hge         =  hge;
	angle         =  0;
	birdPull      =  0;
	birdEnergy    =  30000;//�������ֵ
	birdQuality   =  400;
	maxBirdPull   =  800;
	initPositionX =  initX;
	initPositionY =  initY;
	m_xposition   =  initPositionX;
	m_yposition   =  initPositionY;
	birdScore     =  score;
	birdPull        =  0;
	weaponPull      =  0;
	maxLinePull     =  1000;
	bulletPositionX =  0;
	bulletPositionY =  0;
	weaponPositionX =  0;
	weaponPositionY =  0;
	pigPositionX    =  -70;
	pigPositionY    =  687;
	sndBird[0]      = m_hge->Effect_Load(musicFly);
	sndBird[1]      = m_hge->Effect_Load(musicDead);
	sndPig          = m_hge->Effect_Load("pig.wav");
	birdPullFnt     = new hgeFont("font1.fnt");
	birdPullFnt     ->SetColor(0xFF13612B);
	state           =  FLY;
	pigstate        =  DISAPPEAR;
	initPig();
}
bigMouseBird::~bigMouseBird()
{
	delete m_player;
	delete heroPig;
	delete m_sprBirdDead;
	delete m_sprPigAppear;
	delete m_sprPigDisappear;
	delete m_spts;
	delete parts;
	delete birdPullFnt;
	m_hge -> Texture_Free(m_tex);
	m_hge -> Texture_Free(pig_tex);
	m_hge -> Texture_Free(bird_tex);
	m_hge -> Texture_Free(m_PigDisappear);
	m_hge -> Texture_Free(m_PigAppear);
	m_hge -> Texture_Free(m_birdDead);
	m_hge -> Texture_Free(m_change);
	m_hge -> Effect_Free(sndBird[0]);
	m_hge -> Effect_Free(sndBird[1]);
	m_hge -> Effect_Free(sndPig);
}

void bigMouseBird::initPig()
{
	pig_tex            =  m_hge->Texture_Load("pig.png");
	m_PigAppear        =  m_hge->Texture_Load("EntityPic.png");
	m_sprPigAppear     =  new hgeSprite(m_PigAppear, 168,400, 117,113);
	m_PigDisappear     =  m_hge->Texture_Load("EntityPic.png");
	m_sprPigDisappear  =  new hgeSprite(m_PigAppear, 168,279, 127,121);
	heroPig            =  new hgeAnimation(pig_tex,10,10,0,1,69,50);//���ͼƬ��ȡ
	heroPig            -> SetMode(HGEANIM_LOOP);
	heroPig            -> SetFrames(3);
	heroPig            -> Play();

	m_change   =   m_hge -> Texture_Load("change.jpg");
	m_spts     =   new hgeSprite(m_change,10,0,4,60);        //����ϵͳ
	m_spts     ->  SetBlendMode(BLEND_COLORMUL | BLEND_ALPHAADD | BLEND_NOZWRITE);//����ϵͳ
	m_spts     ->  SetHotSpot(10,10);   

	for (int i=0;i<12;i++)
	{
		parts[i]  =   new hgeParticleSystem("trail.psi",m_spts);  //����ϵͳ
		parts[i]  ->  Fire();   //��������ϵͳ
		parts[i]  ->  info.nEmission=100;//����ϵͳ 
	}
}

void bigMouseBird::setFrames(int frames)
{
	m_player->SetFrames(frames);
	m_birdDead      =  m_hge->Texture_Load(filename);
	m_sprBirdDead   =  new hgeSprite(m_birdDead,bird_position_px+width,bird_position_py,width,height);
}
void bigMouseBird::beCatched()
{
	//������ٶ�x��y��������Ϊ��
	//y_speed = 0;
	//x_speed = 0.01;
	//���⻭��һ��ͼƬ�ṩ��������Ķ���Ч��
    //һ����������·��˯��
	//��������������⻭��һ��ͼƬ(�����ͼƬһ��)�ṩ��������Ķ���Ч��	 
	//���״̬��Ϊ��ʼֵ
	initialState();
	state = FLY;
	pigstate = APPEAR;
}

float changeX;
bool  flagChange = true;
void bigMouseBird::pigCacthBird()
{
	//ʵ����ץ���Ч��
	heroPig->Update(0.01);
	heroPig->Render(pigPositionX, pigPositionY);
	m_sprBirdDead->SetFlip(false,true);
	pigPositionX++;
	//����ʵ�ֱ���Ч��
	if (pigPositionX >=birdDiePositionX +width-200)
	{
		float dt         =   m_hge -> Timer_GetDelta();
		float changeY    =   m_hge -> Random_Int(530,768);
		float changeY1    =   m_hge -> Random_Int(680,730);
		changeX          =   birdDiePositionX + width;
		for (int i = 0;i < 12;i++)
		{
			parts[i]  ->  MoveTo(changeX+5*i, changeY);
			parts[i]  ->  Update(dt);
			parts[i]  ->  Render();
		}		
	}
	
	if (pigPositionX >= (birdDiePositionX + width))
	{
		//������ȥ���������·���Ҹı䷽�����װ��
		//����
		heroPig->SetTextureRect(0,100,69,50);
		pigPositionY  = 575;
		
	}
	if (pigPositionY == 575)
	{
		m_sprBirdDead->Render(pigPositionX-width/2,630-height);
		pigPositionX -=  2;
	}
	else
	{
		m_sprBirdDead->Render(birdDiePositionX,630-height);
	}
	//��������ϳ���Ļ��state����ΪSISAPPEAR
	if (pigPositionX == -72)
	{
		pigstate = DISAPPEAR;
		pigPositionX =  -70;
		pigPositionY =  687;
		heroPig->SetTextureRect(0,1,69,50);
	}
}

float bird_scale =1;
void bigMouseBird::slip()
{
	//��forceescapedһ��Ч��
	m_player->Update(0.01);
	m_player->RenderEx(m_xposition,m_yposition,0,bird_scale);
	m_xposition  +=x_speed;
	m_yposition  +=y_speed;
	bird_scale -= 0.0005;
	if(edgeDetection()||bird_scale<=0)
	{
		initialState();
		state = FLY;
	}
}
void bigMouseBird::forceEscaped()
{
	//��slipһ��Ч��
	m_player->Update(0.01);
	m_player->RenderEx(m_xposition,m_yposition,0,bird_scale);
	m_xposition  +=x_speed;
	bird_scale -= 0.0005;
	if(edgeDetection()||bird_scale<=0)
	{
		initialState();
		state = FLY;
	}
}
void bigMouseBird::judgePigState()
{
	switch(pigstate)
	{
	case APPEAR:
		if(m_hge->Random_Int(0,200)==1)m_hge->Effect_PlayEx(sndPig,volume);
		pigCacthBird();
		break;

	case DISAPPEAR:
		break;

	default:
		break;
	}
}
void bigMouseBird::judgeState(CWeapon* NewWeapon,CBullet* NewBullet,int& score)
{
	switch(state)
	{
	case FLY:
		if(m_hge->Random_Int(0,200)==1)m_hge->Effect_PlayEx(sndBird[0],volume);//���������Ĳ���
		judgePigState();
		catchBirdWithWeapon(NewWeapon, NewBullet);
		break;

	case BECATCHED:
		m_hge->Effect_PlayEx(sndBird[1],volume);
		score += getScore();
		birdDiePositionX = m_xposition;
		beCatched();
		break;

	case SLIP:
		judgePigState();
		slip();
		break;

	case FORCEESCAPED:
		judgePigState();
		forceEscaped();
		break;

	default:
		break;
	}
}

//����ץס���㷨�жϣ���ӦFLY״̬
void bigMouseBird::catchBirdWithWeapon(CWeapon* NewWeapon,CBullet* NewBullet)
{

	bulletPositionX  =  NewBullet->GetPositionX();
	bulletPositionY  =  NewBullet->GetPositionY();
	//����Ƿ�����ļ��������,��������ִ��else����ʾû�����м�������
	if ((bulletPositionX >= m_xposition)&&(bulletPositionX <= m_xposition+width)&&
		(bulletPositionY >= m_yposition)&&(bulletPositionY <=m_yposition +height))   
	{
		m_player         -> SetSpeed(m_hge->Random_Int(20,50));
		NewBullet        -> SetBulletStatecollsion();
		NewBullet        -> SetRopeStateappear();
		weaponPull       =  NewWeapon -> GetWeaponPower();
		birdPull         =  GetBirdPull();
		birdPullFnt      -> SetScale(0.6);
		birdPullFnt      -> Render(210,534,HGETEXT_LEFT,"BirdPull:");
		birdPullFnt      -> SetScale(1);
		birdPullFnt      -> printf(210, 534, HGETEXT_LEFT,"\n  %dN",(int)birdPull);
		weaponPositionX  =  NewWeapon -> GetPositionShootX();
		weaponPositionY  =  NewWeapon -> GetPositionShootY();

		//�������ж����Ƿ������㷨

		//���һ����ץ
		if (isBirdAttacked(bulletPositionX,bulletPositionY))
		{
			//�񱻴����µ���������䵽�ݵ��ϣ�
			
			//�ӵ�λ�ù�λ
			NewBullet -> SetBulletStateInitial();
			NewBullet -> SetRopeStateInitial();
			//ǹ�����ȡ���λ
			NewWeapon -> setInitState();
			state = BECATCHED;
		}
		SetSpeed(weaponPull,weaponPositionX,weaponPositionY);	

		//�����������
 		if ((bulletPositionX < m_xposition+width/2-20)||(bulletPositionX > m_xposition+width/2+20)||
 			(bulletPositionY < m_yposition+height/2-20)||(bulletPositionY > m_yposition+height/2+20))
 		{
 			//�ӵ�λ�ù�λ
 			NewBullet -> SetBulletStateInitial();
 			//ǹ�����ȡ���λ
 			NewWeapon -> setInitState();
 			state = SLIP;
 		}
		 
		//�������ǿ������
 		if ((weaponPull-birdPull) > maxLinePull)
 		{
 			//�ӵ�λ�ù�λ
 			NewBullet -> SetBulletStateInitial();
 			//ǹ�����ȡ���λ
 			NewWeapon -> setInitState();
 			state = FORCEESCAPED;
 		}

		NewBullet -> SetPosition(bulletPositionX,bulletPositionY);

		//�����߽�Ͱ�������Ϣ��λ
		if (edgeDetection())
		{
			//�ӵ�λ�ù�λ
			NewBullet -> SetBulletStateInitial();
			NewBullet -> SetRopeStateInitial();
			//ǹ�����ȡ���λ
			NewWeapon -> setInitState();
			initialState();
		}
	}
	else
	{
		Fly();
	}
}