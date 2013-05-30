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
	m_bullet = new CBullet1(_hge);  //�½�һ���ӵ�;
	m_bullet->SetImage("bullet.png", 0, 0, 33, 52);

	m_rocket = new CRocket(_hge);  //�½�һ�����;
	m_rocket->SetImage("Rocket.png",0, 0, 66, 66);

	m_fart = new CFart(_hge);      //�½�һ��ƨ;
	m_fart->SetImage("EntityPic.png",1005,41,43,43);
	m_isFartHaving = false;

	////////////////////////////////////////������Ч//////////////////////////////////
	m_sndfart = m_hge->Effect_Load("ƨ��.mp3");
	m_sndrocket = m_hge->Effect_Load("�������.mp3");
	m_sndrocketBoom = m_hge->Effect_Load("�����ը��.mp3");
	m_sndbullet = m_hge->Effect_Load("�ӵ��������.wav");

	/************************************************************************/
	/*                �����ըЧ����ʼ��                                     */
	/************************************************************************/
	m_rocketboomtex = m_hge->Texture_Load("��ը��ͼ.png");
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

CRocket* CEquipmentManager::GetRocket() const  //���ػ����ָ��;
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
	if (m_bullet->GetPositionY() <= 10 || m_bullet->GetPositionY() > 600)  //�ڸ������£�С����ܷ����ӵ�;
	{
		if (m_hero->IsSharping())
		{//���ŷ����ӵ�����Ч;
			m_hge->Effect_PlayEx(m_sndbullet, 70, 0, 1.0, false);
			m_bullet->SetPositionX(m_hero->GetPositionX() + 20.0);
			m_bullet->SetPositionY(m_hero->GetPositionY());   //���y����;
			XBulletDelta = m_bullet->GetPositionX() + m_hero->GetTraveledLength(); //����һ���������ڸ����ӵ���λ����Ϣ;
			m_bullet->SetSpeed(15.0);
			m_hero->UnSharp();
		}
	} 

	if (m_hero->IsLeftWaitingPoint() || m_hero->IsRightWaitingPoint() )     //�����ӵ�������λ��;
	{
		m_bullet->SetPositionX(XBulletDelta - m_hero->GetTraveledLength());
	}
	else
		XBulletDelta = m_bullet->GetPositionX() + m_hero->GetTraveledLength();

	if (m_bullet->GetPositionY() <= 20)  //�ӵ��ɵ�һ���߶�ʱ.....;
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
	if (m_rocket->GetPositionY() <= 10 || m_rocket->GetPositionY() > 600)   //����ȵ��������֮����ܷ�����һö;
	{
		if (m_hero->IsRocketing())  //�����������;
		{
			//m_hge->Effect_PlayEx(m_sndrocket, 100, 0, 1.0, false);  //���Ż��������Ч;
			m_rocket->SetPositionX(m_hero->GetPositionX() + 70.0);
			m_rocket->SetPositionY(Y_ROCKET);
			XRocketDelta = m_rocket->GetPositionX() + m_hero->GetTraveledLength(); //����һ���������ڸ��Ļ����λ����Ϣ;
			m_rocket->SetSpeed(0.0);
			m_rocket->SetReady();
			m_hero->GetEquipment(0)->ReduceCount();
			m_hero->UnRocket();
		}
	}
	else
		m_hero->UnRocket();

	if (m_hero->IsLeftWaitingPoint() || m_hero->IsRightWaitingPoint())        //���ֻ��������λ��;
	{
		m_rocket->SetPositionX(XRocketDelta - m_hero->GetTraveledLength());
	}
	else
		XRocketDelta = m_rocket->GetPositionX() + m_hero->GetTraveledLength();

	if(m_rocket->GetPositionY() <= 20 )  //���������һ��λ��ʱ����ը������ʼ��������ٶȺ�λ��;
	{  //��ըЧ���������ű�ը��Ч;
		m_hge->Effect_PlayEx(m_sndrocketBoom, 100, 0, 1.0, false);
		//��ըЧ��;
		//m_rocketboom->SetMode(HGEANIM_NOLOOP);  //��ѭ�����Ŷ���;
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
	if ((m_fart->GetPositionX() <= -300) && m_hero->IsFarting()/*&& m_isFartHaving*/)      //��ƨ��ʱ������ã���������Ļ��ֻ����һ��ƨ;
	{
		m_hge->Effect_PlayEx(m_sndfart, 100, 0, 1.0, false);   //����ƨ��;
			m_fart->SetChanging(true);
			m_fart->Setspeed(4);
			m_hero->GetEquipment(1)->ReduceCount();
			if (m_hero->GetDirection() == PRIGHT)   //��С������ʱ... ��֤��ƨ����С��ƨ�ɷų�;
			{
				m_fart->SetPositionX(m_hero->GetPositionX());
				m_fart->SetPositionY(m_hero->GetPositionY());
			}
			else                                   //��С������ʱ..... ��֤��ƨ����С��ƨ�ɷų�;
			{
				m_fart->SetPositionX(m_hero->GetPositionX() + LENGTH_OF_PIG);
				m_fart->SetPositionY(m_hero->GetPositionY());
			}
			XFartDelta = m_fart->GetPositionX() + m_hero->GetTraveledLength(); //����һ���������ڸ���ƨ��λ����Ϣ;
			//m_isFartHaving = false;
			m_hero->UnFart();
	}
	if (m_hero->IsLeftWaitingPoint() || m_hero->IsRightWaitingPoint() )     //�����ӵ�������λ��;
	{
		m_fart->SetPositionX(XFartDelta - m_hero->GetTraveledLength());
	}
	else
		XFartDelta = m_fart->GetPositionX() + m_hero->GetTraveledLength();

	if (m_fart->GetPositionY() < -300)    //��ƨ����Ļ��������ԭ��Ĵ�С����������Ļ���λ��;
	{
		m_fart->SetHscale(1);
		m_fart->SetVscale(1);
		m_fart->SetTexture(1006, 43, 40, 41, true);
		m_fart->SetPositionX(-4000);
		m_fart->SetPositionY(4000);
		m_fart->SetChanging(false);
	}
	m_fart->Chang();                      //ƨ���߼�����;
}

void CEquipmentManager::Update()
{
	UpdateBullet();
	UpdateRocket();
	UpdateFart();
	//m_rocketboom->Update(m_hge->Timer_GetDelta());   //ʱ�̸��»����ը����;
}

void CEquipmentManager::Render()
{
	m_bullet->Show();
	m_rocket->Show();
	m_fart->boom();
	//m_rocketboom->Render(m_rocket->GetPositionX(), 20);
}