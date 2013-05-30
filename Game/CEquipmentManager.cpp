#include "CEquipmentManager.h"
#include "CGlobal.h"

CEquipmentManager::CEquipmentManager()
{
	delete m_rocket;
}

CEquipmentManager::CEquipmentManager(CYoungPig *_hero, HGE *_hge)
{
	m_hero = _hero;
	m_hge = _hge;
	m_bullet = new CBullet1(_hge);  //新建一颗子弹;
	m_bullet->SetImage("bullet.png", 0, 0, 33, 52);

	m_rocket = new CRocket(_hge);  //新建一个火箭;
	m_rocket->SetImage("Rocket.png",0, 0, 66, 66);

	m_fart = new CFart(_hge);      //新建一个屁;
	m_fart->SetImage("EntityPic.png",1005,41,43,43);
	m_isFartHaving = false;

	////////////////////////////////////////加载音效//////////////////////////////////
	m_sndfart = m_hge->Effect_Load("屁声.mp3");
	m_sndrocket = m_hge->Effect_Load("火箭发射.mp3");
	m_sndrocketBoom = m_hge->Effect_Load("火箭爆炸声.mp3");
	m_sndbullet = m_hge->Effect_Load("子弹射击声音.wav");

	/************************************************************************/
	/*                火箭爆炸效果初始化                                     */
	/************************************************************************/
	m_rocketboomtex = m_hge->Texture_Load("爆炸大图.png");
	m_rocketboom = new hgeAnimation(m_rocketboomtex, 5, 10, 0, 0, 150, 140);
}

CEquipmentManager::~CEquipmentManager()
{
	delete  m_bullet;
	delete  m_rocket;
	delete  m_fart;
	delete  m_rocketboom;

	m_hge->Texture_Free(m_rocketboomtex);
	m_hge->Effect_Free(m_sndfart);
	m_hge->Effect_Free(m_sndrocket);
}

CBullet1* CEquipmentManager::GetBullet() const
{
	return m_bullet;
}

CRocket* CEquipmentManager::GetRocket() const  //返回火箭的指针;
{
	return m_rocket;
}

CFart* CEquipmentManager::GetFart() const
{
	return m_fart;
}

float  XBulletDelta = 0.0;
void CEquipmentManager::UpdateBullet()
{
	if (m_bullet->GetPositionY() <= 10 || m_bullet->GetPositionY() > 600)  //在该条件下，小猪才能发射子弹;
	{
		if (m_hero->IsSharping())
		{//播放发射子弹的音效;
			m_hge->Effect_PlayEx(m_sndbullet, 70, 0, 1.0, false);
			m_bullet->SetPositionX(m_hero->GetPositionX() + 20.0);
			m_bullet->SetPositionY(m_hero->GetPositionY());   //火箭y坐标;
			XBulletDelta = m_bullet->GetPositionX() + m_hero->GetTraveledLength(); //设置一个变量用于更改子弹的位置信息;
			m_bullet->SetSpeed(15.0);
			m_hero->UnSharp();
		}
	} 

	if (m_hero->IsLeftWaitingPoint() || m_hero->IsRightWaitingPoint() )     //保持子弹的世界位置;
	{
		m_bullet->SetPositionX(XBulletDelta - m_hero->GetTraveledLength());
	}
	else
		XBulletDelta = m_bullet->GetPositionX() + m_hero->GetTraveledLength();

	if (m_bullet->GetPositionY() <= 20)  //子弹飞到一定高度时.....;
	{
		m_bullet->SetSpeed(0.0);
		m_bullet->SetPositionX(-1000.0);
		m_bullet->SetPositionY(1000.0);
	}

	m_bullet->Update();
}

float  rocketSpeed = 0;
float  XRocketDelta = 0.0;
void CEquipmentManager::UpdateRocket()
{
	if (m_rocket->GetPositionY() <= 10 || m_rocket->GetPositionY() > 600)   //必须等到火箭升天之后才能发送下一枚;
	{
		if (m_hero->IsRocketing())  //触发火箭发射;
		{
			//m_hge->Effect_PlayEx(m_sndrocket, 100, 0, 1.0, false);  //播放火箭发射音效;
			m_rocket->SetPositionX(m_hero->GetPositionX() + 70.0);
			m_rocket->SetPositionY(Y_ROCKET);
			XRocketDelta = m_rocket->GetPositionX() + m_hero->GetTraveledLength(); //设置一个变量用于更改火箭的位置信息;
			m_rocket->SetSpeed(0.0);
			m_rocket->SetReady();
			m_hero->GetEquipment(0)->ReduceCount();
			m_hero->UnRocket();
		}
	}
	else
		m_hero->UnRocket();

	if (m_hero->IsLeftWaitingPoint() || m_hero->IsRightWaitingPoint())        //保持火箭的世界位置;
	{
		m_rocket->SetPositionX(XRocketDelta - m_hero->GetTraveledLength());
	}
	else
		XRocketDelta = m_rocket->GetPositionX() + m_hero->GetTraveledLength();

	if(m_rocket->GetPositionY() <= 20 )  //当火箭升到一定位置时，爆炸，并初始化火箭的速度和位置;
	{  //爆炸效果，并播放爆炸音效;
		m_hge->Effect_PlayEx(m_sndrocketBoom, 100, 0, 1.0, false);
		//爆炸效果;
		//m_rocketboom->SetMode(HGEANIM_NOLOOP);  //非循环播放动画;
		//m_rocketboom->Play();

		rocketSpeed = 0;
		m_rocket->SetSpeed(rocketSpeed);
		m_rocket->SetPositionX(-1000);
		m_rocket->SetPositionY(1000);
		m_rocket->SetUnReady();
	}

	m_rocket->Update();
}

float  XFartDelta = 0.0;
void CEquipmentManager::UpdateFart()
{
	if ((m_fart->GetPositionX() <= -300) && m_hero->IsFarting()/*&& m_isFartHaving*/)      //有屁的时候才能用，并且在屏幕内只能有一个屁;
	{
		m_hge->Effect_PlayEx(m_sndfart, 100, 0, 1.0, false);   //播放屁声;
			m_fart->SetChanging(true);
			m_fart->Setspeed(4);
			m_hero->GetEquipment(1)->ReduceCount();
			if (m_hero->GetDirection() == PRIGHT)   //当小猪方向朝右时... 保证“屁”从小猪屁股放出;
			{
				m_fart->SetPositionX(m_hero->GetPositionX());
				m_fart->SetPositionY(m_hero->GetPositionY());
			}
			else                                   //当小猪方向朝左时..... 保证“屁”从小猪屁股放出;
			{
				m_fart->SetPositionX(m_hero->GetPositionX() + LENGTH_OF_PIG);
				m_fart->SetPositionY(m_hero->GetPositionY());
			}
			XFartDelta = m_fart->GetPositionX() + m_hero->GetTraveledLength(); //设置一个变量用于更改屁的位置信息;
			//m_isFartHaving = false;
			m_hero->UnFart();
	}
	if (m_hero->IsLeftWaitingPoint() || m_hero->IsRightWaitingPoint() )     //保持子弹的世界位置;
	{
		m_fart->SetPositionX(XFartDelta - m_hero->GetTraveledLength());
	}
	else
		XFartDelta = m_fart->GetPositionX() + m_hero->GetTraveledLength();

	if (m_fart->GetPositionY() < -300)    //当屁出屏幕后，让其变会原理的大小，设置在屏幕外的位置;
	{
		m_fart->SetHscale(1);
		m_fart->SetVscale(1);
		m_fart->SetTexture(1006, 43, 40, 41, true);
		m_fart->SetPositionX(-4000);
		m_fart->SetPositionY(4000);
		m_fart->SetChanging(false);
	}
	m_fart->Chang();                      //屁的逻辑控制;
}

void CEquipmentManager::Update()
{
	UpdateBullet();
	UpdateRocket();
	UpdateFart();
	//m_rocketboom->Update(m_hge->Timer_GetDelta());   //时刻更新火箭爆炸动画;
}

void CEquipmentManager::Render()
{
	m_bullet->Show();
	m_rocket->Show();
	m_fart->boom();
	//m_rocketboom->Render(m_rocket->GetPositionX(), 20);
}