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
	/*1.背景显示;
	2.音效播放;
	3.角色显示;
	4.道具显示;
	5.角色状态显示：血量、经验值;*/

	resourceLoading();	
	butterflyY     = 500;
	butterflyRX    = 1024;
	butterflyLX    = 0;
	butterflyAngle = 0;
	
	//雨滴效果

	m_rain  =   m_hge -> Texture_Load("rain1.png");
	m_spt   =   new hgeSprite(m_rain,0,0,6,20);        //粒子系统
	m_spt   ->  SetBlendMode(BLEND_COLORMUL | BLEND_ALPHAADD | BLEND_NOZWRITE);//粒子系统
	m_spt   ->  SetHotSpot(10,10);   

	for (int i=0;i<64;i++)
	{
		part[i]  =   new hgeParticleSystem("trail.psi",m_spt);  //粒子系统
		part[i]  ->  Fire();   //启动粒子系统
		part[i]  ->  info.nEmission=50;//粒子系统 
	}
}
float RainX  =  0;                                         //移动的偏移量
void CBattle2::Rain(){
	//粒子
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
	//把游戏中需要的资源全部在这里加载
	m_bg1       = m_hge    ->     Texture_Load("bg1.jpg");
	m_sprBg1          =     new hgeSprite(m_bg1,0,0,screenWidth,screenHeight);
	m_tex       = m_hge    ->     Texture_Load( "休闲模式背景.png" );
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
	NewWeapon         ->     SetImage("right.png",1,30,111,62);                                //玩家
	NewBullet         ->     SetImage("Bullet.png",0,0,19,13,"rope1.png",0,0,3,3,
		                               "rope1.png",0,0,3,3);		//加载子弹和绳子	//加载子弹和绳子
	NewStrength       ->     SetImage("bar2.png",60,70,5,5);                           //玩家
	//动画鸟的实现效果
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
	//大雁
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
	//音效加载测试
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
	//将时间和分值绘制到屏幕上去
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
	//设置枪的位置

	//	Time+=m_hge->Timer_GetDelta();
	m_sprStrength->RenderStretch(98,645,240,680);
	NewWeapon           ->          Render();                                      //渲染武器
	NewWeapon           ->          Controle();                                 //控制武器的方向
	NewStrength         ->          Render();  
	//****************设置力度条的长度，当adjust时力度条长度改变，当子弹射出后，力度条恢复到初始长度******//

	//渲染力度条

	//****************************************************************************************************//

	if(NewWeapon       ->    GetWeaponState()==shoot)         //判断武器是否做出射击动作
	{

		NewBullet  ->		SetSpeed(NewWeapon->GetStrength(),NewWeapon->GetAngle());
		NewBullet  ->		SetPosition(NewWeapon->GetPositionShootX(),NewWeapon->GetPositionShootY());
		NewBullet  ->		SetBulletStatemove();
		m_hge      ->       Effect_PlayEx(snd[4]);//子弹音效

		//射击后，力度条变为零
		NewStrength    ->		SetStrengthStateIntial();
		//NewBullet      ->		SetBulletStatemove();          //子弹状态变为move
		NewBullet      ->		SetRopeStateappear();          //绳子状态变为appear
		NewWeapon      ->       SetWeaponStateadjust();        //武器状态改为adjust
		NewBullet      ->       SetSpeed(NewWeapon->GetStrength(),NewWeapon->GetAngle());	//子弹获取初始速度
		NewBullet	   ->       SetPosition(NewWeapon->GetPositionShootX(),NewWeapon->GetPositionShootY());//子弹获取初始位置
		//NewStrength    ->		SetLength(0);                  //射击结束后，将力度条长度恢复为0  
		//*********子弹状态为collision，则子弹遗留在鸟内，进一步判断***********************************//
		//if (NewBullet  ->		GetBulletState()==collision)int r=0;

		//*********给子弹的状态进行初始化，恢复默认状态***********************************************//
		
			
		NewWeapon->SetWeaponStateadjust();
		//*********如果子弹状态为move，则子弹按照重力轨迹，进行移动**********************************//


	}
	else
		NewStrength    ->    SetLength(1.2*NewWeapon->GetStrength()*((NewWeapon->GetStrength()-7)/0.5+1)); 
	    


}
//标志位status作用
bool battle00_status = false;
void CBattle2::timeOver()
{
	//计数器timeCount等于120时游戏结束并且判断分值Score值为多少
	if (timeCount >= 20)
	{
		//把这一部分留作接口，供程序结束时统一调用
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
	//背景绘制注意先后顺序
	m_sprBg1        ->RenderEx(0,0,0,1.3);
	m_sprBackground ->  Render(0,0);
	//大雁的绘制
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
	if (goose_x_positon<=-80)//飞出屏幕
	{
		goose_x_positon = 1024;//归位
		goose_scale     = 1.2;
		goose_change1 = 0;
		goose_change2 = 0;
		goose_change3 = 0;
	}

	m_sprGround     ->  Render(0,730);
	m_sprDirection  ->  Render(700,621);
	m_sprGrass      ->  Render(400,670);  //原基础上下移7个像素
	m_sprGrass      ->  Render(251,670);
	ButterflyRun();
	m_sprFlower     ->  Render(100,671);
	m_sprFlower     ->  Render(120,671);
	m_sprFlower     ->  Render(110,671);
	m_sprFlowerMove ->  Render(120,685);


}
//背景蝴蝶的飞行，需后期完善，用动画效果实现更动态
void CBattle2::ButterflyRun()
{
	float speed    =   0.3;
    //从画面右边飞入
	m_sprButterfly ->  SetFlip(false,false);
	//设置蝴蝶任意角度飞行
	float test     =   rand() % 1000;
	butterflyAngle +=  (test / 50000);
	butterflyAngle +=  m_hge->Random_Float(0,0.001);
	m_sprButterfly ->  RenderEx(butterflyRX -100,butterflyY,butterflyAngle,1);
	m_sprButterfly ->  RenderEx(butterflyRX -300,butterflyY,butterflyAngle,1);
	m_sprButterfly ->  RenderEx(butterflyRX -90,butterflyY,-butterflyAngle,1);
	m_sprButterfly ->  RenderEx(butterflyRX -200,butterflyY,-butterflyAngle,1);
	butterflyRX    -=  speed * cos(butterflyAngle);
	butterflyY     -=  speed * sin(butterflyAngle);
	//画面左边任意点飞入
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
	//*******子弹状态为shoot，绳子状态为appear，子弹移动，绳子随着子弹移动，并渲染绳子，子弹*****//
	if ((NewBullet  ->GetBulletState()==MOVE)&&(NewBullet  ->GetRopeState()  ==appear))
	{
		
		NewBullet  ->	 Move();
		NewBullet  ->	 Render();
		//NewBullet  ->	 Renderrope();
	}
	//******子弹状态为collision，绳子状态为appear，子弹在鸟中，绳子随着鸟移动，渲染绳子*********//
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
	//*********当子弹状态为initial，子弹从屏幕中消失*********************************************//
	if (NewBullet  ->GetBulletState()==Initial)
	{
		NewBullet  ->		SetSpeed(NewWeapon->GetStrength(),NewWeapon->GetAngle());	
		NewBullet  ->		SetPosition(NewWeapon->GetPositionShootX(),NewWeapon->GetPositionShootY());
		//NewBullet  ->		SetBulletStatemove();
		//////////////////
	}
	//*********当绳子状态为initial，绳子vector情况，从屏幕消失**********************************//
	if (NewBullet  ->GetRopeState()==Initial)
	{
		NewBullet  ->ClearRope();
	}

}
//run函数基本没有问题
bool CBattle2::Run()
{
	return battle00_status;
}
//释放资源;
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

