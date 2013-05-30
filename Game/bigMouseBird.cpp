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
	birdEnergy    =  30000;//体能最大值
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
	heroPig            =  new hgeAnimation(pig_tex,10,10,0,1,69,50);//猪的图片获取
	heroPig            -> SetMode(HGEANIM_LOOP);
	heroPig            -> SetFrames(3);
	heroPig            -> Play();

	m_change   =   m_hge -> Texture_Load("change.jpg");
	m_spts     =   new hgeSprite(m_change,10,0,4,60);        //粒子系统
	m_spts     ->  SetBlendMode(BLEND_COLORMUL | BLEND_ALPHAADD | BLEND_NOZWRITE);//粒子系统
	m_spts     ->  SetHotSpot(10,10);   

	for (int i=0;i<12;i++)
	{
		parts[i]  =   new hgeParticleSystem("trail.psi",m_spts);  //粒子系统
		parts[i]  ->  Fire();   //启动粒子系统
		parts[i]  ->  info.nEmission=100;//粒子系统 
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
	//让鸟的速度x、y方向立即为零
	//y_speed = 0;
	//x_speed = 0.01;
	//额外画上一张图片提供猪来拖鸟的动作效果
    //一、猪在下面路上睡觉
	//二、当鸟掉落后额外画上一张图片(与鸟的图片一样)提供猪来拖鸟的动作效果	 
	//鸟的状态设为初始值
	initialState();
	state = FLY;
	pigstate = APPEAR;
}

float changeX;
bool  flagChange = true;
void bigMouseBird::pigCacthBird()
{
	//实现猪抓鸟的效果
	heroPig->Update(0.01);
	heroPig->Render(pigPositionX, pigPositionY);
	m_sprBirdDead->SetFlip(false,true);
	pigPositionX++;
	//粒子实现变身效果
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
		//猪跳上去，到上面的路并且改变方向加上装备
		//变身
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
	//当猪把鸟拖出屏幕后state设置为SISAPPEAR
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
	//与forceescaped一样效果
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
	//与slip一样效果
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
		if(m_hge->Random_Int(0,200)==1)m_hge->Effect_PlayEx(sndBird[0],volume);//控制声音的播放
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

//鸟被绳抓住的算法判断，对应FLY状态
void bigMouseBird::catchBirdWithWeapon(CWeapon* NewWeapon,CBullet* NewBullet)
{

	bulletPositionX  =  NewBullet->GetPositionX();
	bulletPositionY  =  NewBullet->GetPositionY();
	//检测是否在鸟的检测区域内,若不在则执行else语句表示没被击中继续飞行
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

		//下面是判断鸟是否逃脱算法

		//情况一、鸟被抓
		if (isBirdAttacked(bulletPositionX,bulletPositionY))
		{
			//鸟被打落下的情况、鸟落到草地上，
			
			//子弹位置归位
			NewBullet -> SetBulletStateInitial();
			NewBullet -> SetRopeStateInitial();
			//枪的力度、归位
			NewWeapon -> setInitState();
			state = BECATCHED;
		}
		SetSpeed(weaponPull,weaponPositionX,weaponPositionY);	

		//情况二、溜走
 		if ((bulletPositionX < m_xposition+width/2-20)||(bulletPositionX > m_xposition+width/2+20)||
 			(bulletPositionY < m_yposition+height/2-20)||(bulletPositionY > m_yposition+height/2+20))
 		{
 			//子弹位置归位
 			NewBullet -> SetBulletStateInitial();
 			//枪的力度、归位
 			NewWeapon -> setInitState();
 			state = SLIP;
 		}
		 
		//情况三、强制逃跑
 		if ((weaponPull-birdPull) > maxLinePull)
 		{
 			//子弹位置归位
 			NewBullet -> SetBulletStateInitial();
 			//枪的力度、归位
 			NewWeapon -> setInitState();
 			state = FORCEESCAPED;
 		}

		NewBullet -> SetPosition(bulletPositionX,bulletPositionY);

		//超出边界就把所有信息归位
		if (edgeDetection())
		{
			//子弹位置归位
			NewBullet -> SetBulletStateInitial();
			NewBullet -> SetRopeStateInitial();
			//枪的力度、归位
			NewWeapon -> setInitState();
			initialState();
		}
	}
	else
	{
		Fly();
	}
}