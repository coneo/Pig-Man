#include"CBattle2.h"
#include <math.h>

CBattle2::CBattle2(HGE *_hge)
{
	m_hge           =  _hge;
	score           =  0;
	goose_x_positon = 1024;
	goose_y_positon = 250;
	goose_scale     = 1.2;
	volume          = 50;
}

CBattle2::~CBattle2()
{
}

void CBattle2::Init()
{
	/*1.������ʾ;
	2.��Ч����;
	3.��ɫ��ʾ;
	4.������ʾ;
	5.��ɫ״̬��ʾ��Ѫ��������ֵ;*/

	resourceLoading();	
	butterflyY     = 500;
	butterflyRX    = 1024;
	butterflyLX    = 0;
	butterflyAngle = 0;
	
	//���Ч��

	m_rain  =   m_hge -> Texture_Load("rain1.png");
	m_spt   =   new hgeSprite(m_rain,0,0,6,20);        //����ϵͳ
	m_spt   ->  SetBlendMode(BLEND_COLORMUL | BLEND_ALPHAADD | BLEND_NOZWRITE);//����ϵͳ
	m_spt   ->  SetHotSpot(10,10);   

	for (int i=0;i<64;i++)
	{
		part[i]  =   new hgeParticleSystem("trail.psi",m_spt);  //����ϵͳ
		part[i]  ->  Fire();   //��������ϵͳ
		part[i]  ->  info.nEmission=50;//����ϵͳ 
	}
}
float RainX  =  0;                                         //�ƶ���ƫ����
void CBattle2::Rain(){
	//����
	float dt       =   m_hge -> Timer_GetDelta();
	float RainY    =   m_hge -> Random_Float(0,768);
	RainX          =   16;

	if (RainX >= 1024) RainX =  0;

	for (int i = 0;i < 64;i++)
	{

		part[i]  ->  MoveTo(1+(i+1)*RainX, RainY);
		part[i]  ->  Update(dt);
		part[i]  ->  Render();
	}
}
void CBattle2::resourceLoading()
{
	NewWeapon        =      new CWeapon(m_hge);
	NewBullet        =      new CBullet(m_hge);
	NewStrength      =      new CStrength(m_hge);
	//����Ϸ����Ҫ����Դȫ�����������
	m_bg1       = m_hge    ->     Texture_Load("bg1.jpg");
	m_sprBg1          =     new hgeSprite(m_bg1,0,0,screenWidth,screenHeight);
	m_tex       = m_hge    ->     Texture_Load( "����ģʽ����.png" );
	m_sprBackground   =     new hgeSprite(m_tex, 0, 0, screenWidth, screenHeight);
	m_ground    = m_hge    ->     Texture_Load("ground.png");
	m_sprGround       =     new hgeSprite(m_ground,0,0,screenWidth,38);
	m_direction = m_hge    ->     Texture_Load("direction.png");
	m_sprDirection    =     new hgeSprite(m_direction,0,0,65,116);
	m_flower    = m_hge    ->     Texture_Load("flower.png");
	m_sprFlower       =     new hgeSprite(m_flower,0,0,47,66);
	m_tree      = m_hge    ->     Texture_Load("tree.png");
	m_sprTree         =     new hgeSprite(m_tree,0,0,180,281);
	m_grass     = m_hge    ->     Texture_Load("grass.png");
	m_sprGrass        =     new hgeSprite(m_grass,0,0,149,67);
	m_flowerMove= m_hge    ->     Texture_Load("flowerMove.png");
	m_sprFlowerMove   =     new hgeSprite(m_flowerMove,0,0,56,52);
	m_butterfly = m_hge    ->     Texture_Load("buffer.png");
	m_sprButterfly    =     new hgeSprite(m_butterfly,0,0,33,18);
	m_Strength	      =     m_hge->Texture_Load("jindu0.png");
	m_sprStrength     =		new hgeSprite(m_Strength,0,0,125,21);
	NewWeapon         =     new CWeapon(m_hge);
	NewBullet         =     new CBullet(m_hge);
	NewStrength       =     new CStrength(m_hge);
	NewWeapon         ->     SetPosition(50,650); 
	NewWeapon         ->     SetImage("right.png",1,30,111,62);                                //���
	NewBullet         ->     SetImage("Bullet.png",0,0,19,13,"rope1.png",0,0,3,3,
		                               "rope1.png",0,0,3,3);		//�����ӵ�������	//�����ӵ�������
	NewStrength       ->     SetImage("bar2.png",60,70,5,5);                           //���
	//�������ʵ��Ч��
	animDragon         =      new bigMouseBird(m_hge,0,0,20,"dragonFly.mp3","dragonDie.mp3");
	animDragon        ->     SetSpeed(1,0);
	animDragon        ->     SetImage("dragon.png",36,0,280,170,volume);
	animDragon        ->     SetPlayMode(HGEANIM_LOOP);
	animDragon        ->     setFrames(6);
	animBirdBlue      =      new bigMouseBird(m_hge,0,200,30,"smallBird.wav","smallBirdDead.wav");
	animBirdBlue      ->     SetSpeed(2,0);
	animBirdBlue      ->     SetImage("smallBird.png",0,0,65,60,volume);
	animBirdBlue      ->     SetPlayMode(HGEANIM_LOOP);
	animBirdBlue      ->     setFrames(4);
	//����
	goose           =  m_hge ->     Texture_Load("goose.png");
	m_goose         =  new hgeAnimation(goose,10,10,19,76,70,60);
	m_goose         -> SetFlip(true,false);
	m_goose         -> SetMode(HGEANIM_LOOP);
	m_goose         -> Play();

	fnt               =      new hgeFont("font1.fnt");
	snd[0]            =      m_hge->Effect_Load("BgMusic.mp3");
	snd[1]            =      m_hge->Effect_Load("weapon.mp3");
	snd[2]            =      m_hge->Effect_Load("rain.mp3");
	snd[3]            =      m_hge->Effect_Load("BgMusic1.mp3");
	snd[4]            =      m_hge->Effect_Load("bullet.mp3");
}

void CBattle2::timeAndScore()
{
	//��Ч���ز���
	if(m_hge  ->  Input_GetKeyState(HGEK_UP))
	{
		volume += 0.3;
		if(volume >=100)volume = 100;
	}
	if(m_hge  ->  Input_GetKeyState(HGEK_DOWN))
	{
		volume -= 0.3;
		if(volume <= 0)volume = 0;
	}
	if(m_hge  ->  Input_GetKeyState(HGEK_M))
		m_hge     ->  Effect_PlayEx(snd[0],volume);
	if(m_hge  ->  Input_GetKeyState(HGEK_B))
		m_hge     ->  Effect_PlayEx(snd[3],volume);
	if(m_hge  ->  Input_GetKeyState(HGEK_A)||m_hge  ->  Input_GetKeyState(HGEK_D))
		m_hge     ->  Effect_PlayEx(snd[1],volume);
	if (m_hge->Random_Int(0,150)==1)
		m_hge     ->  Effect_PlayEx(snd[2],30);
	//��ʱ��ͷ�ֵ���Ƶ���Ļ��ȥ
	fnt           ->  SetColor(0xFFFFFFFF);
	timeCount     =   m_hge -> Timer_GetTime();
	
	fnt           ->  printf(800, 5, HGETEXT_LEFT, "timeCount:%d",(int)timeCount);
	fnt           ->  printf(800, 65, HGETEXT_LEFT, "scoreCount:%d", score);
	fnt           ->  SetColor(0xFF13612B);
	fnt           ->  SetScale(0.6);
	fnt           ->  Render(670,500,HGETEXT_LEFT,"WeaponPull:");
	fnt           ->  SetScale(1);
	fnt           ->  printf(670, 510, HGETEXT_LEFT,"\n  %dN",(int)NewWeapon->GetWeaponPower());
	fnt           ->  SetColor(0xFFFFFFFF);
}
void CBattle2::Shooting()
{
	//����ǹ��λ��

	//	Time+=m_hge->Timer_GetDelta();
	m_sprStrength->RenderStretch(98,645,240,680);
	NewWeapon           ->          Render();                                      //��Ⱦ����
	NewWeapon           ->          Controle();                                 //���������ķ���
	NewStrength         ->          Render();  
	//****************�����������ĳ��ȣ���adjustʱ���������ȸı䣬���ӵ�������������ָ�����ʼ����******//

	//��Ⱦ������

	//****************************************************************************************************//

	if(NewWeapon       ->    GetWeaponState()==shoot)         //�ж������Ƿ������������
	{

		NewBullet  ->		SetSpeed(NewWeapon->GetStrength(),NewWeapon->GetAngle());
		NewBullet  ->		SetPosition(NewWeapon->GetPositionShootX(),NewWeapon->GetPositionShootY());
		NewBullet  ->		SetBulletStatemove();
		m_hge      ->       Effect_PlayEx(snd[4]);//�ӵ���Ч

		//�������������Ϊ��
		NewStrength    ->		SetStrengthStateIntial();
		//NewBullet      ->		SetBulletStatemove();          //�ӵ�״̬��Ϊmove
		NewBullet      ->		SetRopeStateappear();          //����״̬��Ϊappear
		NewWeapon      ->       SetWeaponStateadjust();        //����״̬��Ϊadjust
		NewBullet      ->       SetSpeed(NewWeapon->GetStrength(),NewWeapon->GetAngle());	//�ӵ���ȡ��ʼ�ٶ�
		NewBullet	   ->       SetPosition(NewWeapon->GetPositionShootX(),NewWeapon->GetPositionShootY());//�ӵ���ȡ��ʼλ��
		//NewStrength    ->		SetLength(0);                  //��������󣬽����������Ȼָ�Ϊ0  
		//*********�ӵ�״̬Ϊcollision�����ӵ����������ڣ���һ���ж�***********************************//
		//if (NewBullet  ->		GetBulletState()==collision)int r=0;

		//*********���ӵ���״̬���г�ʼ�����ָ�Ĭ��״̬***********************************************//
		
			
		NewWeapon->SetWeaponStateadjust();
		//*********����ӵ�״̬Ϊmove�����ӵ����������켣�������ƶ�**********************************//


	}
	else
		NewStrength    ->    SetLength(1.2*NewWeapon->GetStrength()*((NewWeapon->GetStrength()-7)/0.5+1)); 
	    


}
//��־λstatus����
bool battle00_status = false;
void CBattle2::timeOver()
{
	//������timeCount����120ʱ��Ϸ���������жϷ�ֵScoreֵΪ����
	if (timeCount >= 20)
	{
		//����һ���������ӿڣ����������ʱͳһ����
		if (score >= 100)
		{
			battle00_status = true;
		} 
		else
		{
			battle00_status = true;
		}
	}
}
float goose_change1 = 0;
float goose_change2 = 0;
float goose_change3 = 0;
void CBattle2::paintBg()
{
	//��������ע���Ⱥ�˳��
	m_sprBg1        ->RenderEx(0,0,0,1.3);
	m_sprBackground ->  Render(0,0);
	//����Ļ���
	goose_change1 += m_hge->Random_Float(0,0.2);
	goose_change2 += m_hge->Random_Float(0,0.3);
    goose_change3 += m_hge->Random_Float(0,0.4);

	m_goose->Update(0.01);
	m_goose->RenderEx(goose_x_positon,goose_y_positon,0,goose_scale);
	m_goose->RenderEx(goose_x_positon+30,goose_y_positon,0,goose_scale);
	m_goose->RenderEx(goose_x_positon+60,goose_y_positon,0,goose_scale);
	m_goose->RenderEx(goose_x_positon+90-goose_change1,goose_y_positon-20,0,goose_scale);
	m_goose->RenderEx(goose_x_positon+90-goose_change1,goose_y_positon+20,0,goose_scale);
	m_goose->RenderEx(goose_x_positon+120-goose_change2,goose_y_positon-40,0,goose_scale);
	m_goose->RenderEx(goose_x_positon+120-goose_change2,goose_y_positon+40,0,goose_scale);
	m_goose->RenderEx(goose_x_positon+150-goose_change3,goose_y_positon-60,0,goose_scale);
	m_goose->RenderEx(goose_x_positon+150-goose_change3,goose_y_positon+60,0,goose_scale);
	goose_x_positon--;
	goose_scale -= 0.001; 
	if (goose_x_positon<=-80)//�ɳ���Ļ
	{
		goose_x_positon = 1024;//��λ
		goose_scale     = 1.2;
		goose_change1 = 0;
		goose_change2 = 0;
		goose_change3 = 0;
	}

	m_sprGround     ->  Render(0,730);
	m_sprDirection  ->  Render(700,621);
	m_sprGrass      ->  Render(400,670);  //ԭ����������7������
	m_sprGrass      ->  Render(251,670);
	ButterflyRun();
	m_sprFlower     ->  Render(100,671);
	m_sprFlower     ->  Render(120,671);
	m_sprFlower     ->  Render(110,671);
	m_sprFlowerMove ->  Render(120,685);


}
//���������ķ��У���������ƣ��ö���Ч��ʵ�ָ���̬
void CBattle2::ButterflyRun()
{
	float speed    =   0.3;
    //�ӻ����ұ߷���
	m_sprButterfly ->  SetFlip(false,false);
	//���ú�������Ƕȷ���
	float test     =   rand() % 1000;
	butterflyAngle +=  (test / 50000);
	butterflyAngle +=  m_hge->Random_Float(0,0.001);
	m_sprButterfly ->  RenderEx(butterflyRX -100,butterflyY,butterflyAngle,1);
	m_sprButterfly ->  RenderEx(butterflyRX -300,butterflyY,butterflyAngle,1);
	m_sprButterfly ->  RenderEx(butterflyRX -90,butterflyY,-butterflyAngle,1);
	m_sprButterfly ->  RenderEx(butterflyRX -200,butterflyY,-butterflyAngle,1);
	butterflyRX    -=  speed * cos(butterflyAngle);
	butterflyY     -=  speed * sin(butterflyAngle);
	//���������������
	m_sprButterfly ->  SetFlip(true,false);
	m_sprButterfly ->  RenderEx(butterflyLX,butterflyY,0,1);
	m_sprButterfly ->  RenderEx(butterflyLX,butterflyY -(rand()%10 + 30),0,1);
	m_sprButterfly ->  RenderEx(butterflyLX,butterflyY + rand()%10  + 30,0,1);
	butterflyLX    +=  rand() % 3;
	if (rand() % 2 == 0)
	{
		butterflyY -=  rand() % 3;
	} 
	else
	{
		butterflyY +=  rand() % 3;
	}
	if (butterflyRX < 0)
	{
		butterflyRX =  1024;
	}
	if (butterflyLX >1024)
	{
		butterflyLX =  0;
	}
}
bool CBattle2::Render()
{
	paintBg();
	Shooting();
	timeAndScore();
	Rain();
	animDragon     -> judgeState(NewWeapon,NewBullet,score);
	animBirdBlue   -> judgeState(NewWeapon,NewBullet,score);
	RenderBulletandRope();
	m_sprTree      ->  Render(800,456);
	//timeOver();
	return battle00_status;
}
void CBattle2::RenderBulletandRope()
{
	//*******�ӵ�״̬Ϊshoot������״̬Ϊappear���ӵ��ƶ������������ӵ��ƶ�������Ⱦ���ӣ��ӵ�*****//
	if ((NewBullet  ->GetBulletState()==MOVE)&&(NewBullet  ->GetRopeState()  ==appear))
	{
		
		NewBullet  ->	 Move();
		NewBullet  ->	 Render();
		//NewBullet  ->	 Renderrope();
	}
	//******�ӵ�״̬Ϊcollision������״̬Ϊappear���ӵ������У������������ƶ�����Ⱦ����*********//
	if ((NewBullet ->GetBulletState()==collision)&&(NewBullet  ->GetRopeState()  ==appear))
	{
		NewBullet  ->SetRopePosition(NewBullet->GetPositionX(),NewBullet->GetPositionY(),
										NewWeapon->GetPositionShootX(),NewWeapon->GetPositionShootY());
		NewBullet  ->Renderrope();
		/*if (NewPig->GetPigState()==jump)
		{
		NewPig->move();
		}
		NewPig->Render();*/

	}
	//*********���ӵ�״̬Ϊinitial���ӵ�����Ļ����ʧ*********************************************//
	if (NewBullet  ->GetBulletState()==Initial)
	{
		NewBullet  ->		SetSpeed(NewWeapon->GetStrength(),NewWeapon->GetAngle());	
		NewBullet  ->		SetPosition(NewWeapon->GetPositionShootX(),NewWeapon->GetPositionShootY());
		//NewBullet  ->		SetBulletStatemove();
		//////////////////
	}
	//*********������״̬Ϊinitial������vector���������Ļ��ʧ**********************************//
	if (NewBullet  ->GetRopeState()==Initial)
	{
		NewBullet  ->ClearRope();
	}

}
//run��������û������
bool CBattle2::Run()
{
	return battle00_status;
}
//�ͷ���Դ;
void CBattle2::Release()
{
	delete m_hge;
	delete m_sprBackground;
	delete m_sprBg1;
	delete m_sprButterfly;
	delete m_sprDirection;
	delete m_sprFlower;
	delete m_sprFlowerMove;
	delete m_sprGrass;
	delete m_sprGround;
	delete m_sprTree;
	delete animDragon;
	delete animBirdBlue;
	delete m_goose;
	delete fnt;
	delete part;
	delete m_spt;
	m_hge->Texture_Free(goose);
	m_hge->Texture_Free(m_direction);
	m_hge->Texture_Free(m_butterfly);
	m_hge->Texture_Free(m_stone);
	m_hge->Texture_Free(m_tree);
	m_hge->Texture_Free(m_flower);
	m_hge->Texture_Free(m_flowerMove);
	m_hge->Texture_Free(m_grass);
	m_hge->Texture_Free(m_tex);
	m_hge->Texture_Free(m_bg1);
	m_hge->Texture_Free(m_ground);
	m_hge->Texture_Free(m_rain);
	m_hge->Effect_Free(snd[0]);
	m_hge->Effect_Free(snd[1]);
	m_hge->Effect_Free(snd[2]);
	m_hge->Effect_Free(snd[3]);
	m_hge->Effect_Free(snd[4]);
}

