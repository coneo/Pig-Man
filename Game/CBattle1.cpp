#include "CBattle1.h"
#include "CGlobal.h"
#include "CGame.h"

class CGame; //��ΪҪʹ��WIN_WIDTH��WIN_HEIGHT;



CBattle1::CBattle1(HGE *_hge, CGame *_game)
{
	m_hge = _hge;
	m_cgame = _game;
	m_max_birds = 2;   //��ʼ�������©����������;
}

CBattle1::~CBattle1()
{

}

void CBattle1::Init()
{
	/*1.������ʾ;
	2.��Ч����;
	3.��ɫ��ʾ;
	4.������ʾ;
	5.��ɫ״̬��ʾ��Ѫ��������ֵ;*/

	SetScore(0);                                //��ʼ����Ϊ0;

	m_fnt=new hgeFont("font1.fnt");               //��������;                                  
	/************************************************************************/
	/*                   ���غʹ���������Դ��                               */
	/************************************************************************/
	
	m_bktex  = m_hge->Texture_Load("bk.png");  //���ر���ͼ��Դ��
	m_bkspr = new hgeSprite(m_bktex, 0, 0, 1366, 768);//�����������飻
	m_preX = m_currentX = m_Xoffset = 0.0;                 //��ʼ����һ֡�͵�ǰ֡�ı���ͼ��X�����Լ�����֮��Ĳ�ֵ;

	/************************************************************************/
	/*                    ������Ч��                    */
	m_snd_bigmouse_fly = m_hge->Effect_Load("����ѻ����.mp3");
	m_snd_bigmouse_hurt = m_hge->Effect_Load("����ѻ����.wav");

	m_snd_eggbird_fly = m_hge->Effect_Load("���������Ч.wav");
	m_snd_eggbird_hurt = m_hge->Effect_Load("����������Ч.wav");

	m_snd_lightbird_fly = m_hge->Effect_Load("�����������Ч.wav");
	m_snd_lightbird_hurt = m_hge->Effect_Load("������������Ч.wav");

	m_snd_bombbird_fly = m_hge->Effect_Load("��ը�������Ч.wav");
	m_snd_bombbird_hurt = m_hge->Effect_Load("��ը��������Ч.wav");

	m_snd_pig_hurt = m_hge->Effect_Load("С��������Ч.wav");
	/************************************************************************/


	/************************************************************************/
	/*                ��������������ʼ����Ӧ������                        */
	/************************************************************************/
	hero = new CYoungPig(m_hge);
	hero->SetLife(5);         //��ʼ��С��Ѫ��;
	hero->LoadTexture("������.png");
	hero->SetImage(3, 5, 0, 0, 69, 51);
	//hero->SetFrame(3);
	//hero->SetMode(HGEANIM_NOLOOP);
	hero->Play();

	/************************************************************************/
	/*               ��������ݲ���                                           */
	/************************************************************************/ 
	m_wave = FIRST;//��ʼ������Ϊ��һ����
	
	m_card_state = true;
	/************************************************************************/
	/*                  ����װ������                                       */
	/************************************************************************/
	m_equipManager = new CEquipmentManager(hero, m_hge); 

}

bool battle1_status = false;
float _timer;



//���ⲿ��ʵ���߼��жϺ��߼�����,���������ƶ�����ײ���;
bool CBattle1::Run()  //ÿ֡���øú�����ÿ��100֡����;
{
	
	_timer = m_hge->Timer_GetTime();
	//���ݲ�����������
	if(m_card_state)
		this->GenerateBirdsByWave();
	//ʵʱ����Ƿ���ת����һ����
	this->JumpCard();
	//������Ϸ����;
	UpdateBk();

	//�������״̬;
	if(hero->Update())
		battle1_status = true;
	hero->UpdateEquipmentXpo(m_Xoffset);  //ͨ���������µ��µ�װ��������;

	//������;
	//UpdateBirds();

	//����С�������ʹ��װ��;
	m_equipManager->Update();
	
// 	float x_pig = hero->GetPositionX();
// 	float y_pig = hero->GetPositionY();
// 
// 
// 	CheckCollision();    //�����̺������ײ;


	/************************************************************************/
	/*                 ��ĸ���                                             */
	/************************************************************************/
	
	//������
	for (bigbird_ite = m_b2_bigbirds.begin(); bigbird_ite != m_b2_bigbirds.end(); )
	{
		if (((*bigbird_ite)->GetCurrenPosition().x >= 0) && (*bigbird_ite)->GetCurrenPosition().x <= 20)  //���ɵ���Ļ��ʱ����һ��;
		{
			m_hge->Effect_PlayEx(m_snd_bigmouse_fly, 100, 0, 1.0, false);
		}
		if(NULL != (*bigbird_ite))
		{
			(*bigbird_ite)->Update(0.005f);
			(*bigbird_ite)->AI(Position(this->hero->GetPositionX()+g_pig_wh.x/2,this->hero->GetPositionY()+g_pig_wh.y/2),10,7,4);
			if((*bigbird_ite)->IsHit())  //������ײ��С��;
			{
				m_hge->Effect_PlayEx(m_snd_bigmouse_hurt, 100, 0, 1.0, false);  //���Ŵ�������Ч;
				m_hge->Effect_PlayEx(m_snd_pig_hurt, 100, 0, 1.0, false);   //����С����Ч;
				this->hero->Hurt();  //��Ѫ;
				bigbird_ite = this->m_b2_bigbirds.erase(bigbird_ite);
			}//�����߽�;
			else if ((*bigbird_ite)->GetCurrenPosition().x>WIN_WIDTH+1000)
			{
				bigbird_ite = this->m_b2_bigbirds.erase(bigbird_ite);
			}
			else

				++bigbird_ite;
		}
	}
	//������;
	for (lightbird_ite  = m_b2_lightbirds.begin();lightbird_ite != m_b2_lightbirds.end(); )
	{
		if (((*lightbird_ite)->GetCurrenPosition().x >= 0) && (*lightbird_ite)->GetCurrenPosition().x <= 20)  //���ɵ���Ļ��ʱ����һ��;
		{
			m_hge->Effect_PlayEx(m_snd_lightbird_fly, 100, 0, 1.0, false);
		}
		if (NULL != (*lightbird_ite))
		{
			(*lightbird_ite)->Update(0.005f);
			(*lightbird_ite)->AI(Position(this->hero->GetPositionX()+g_pig_wh.x/2,this->hero->GetPositionY()+g_pig_wh.y/2),7,3,0);
			//���ӵ���ײ;
			if ((*lightbird_ite)->IsCollision(Position(m_equipManager->GetBullet()->GetPositionX()-g_bullet_wh.x,
				m_equipManager->GetBullet()->GetPositionY()-g_bullet_wh.y),g_bullet_attck_distace)
				&& (((*lightbird_ite)->GetColor() == hero->GetColor()) || (hero->IsIgnoring()))) //���������ɫƥ�����ʹ�á����ӡ�ʱ���ɶ�����ɹ���;
			{
				m_hge->Effect_PlayEx(m_snd_lightbird_hurt, 100, 0, 1.0, false);  //����������Ч;
				this->hero->RandomDown((*lightbird_ite)->GetCurrenPosition().x,(*lightbird_ite)->GetCurrenPosition().y);
				lightbird_ite = m_b2_lightbirds.erase(lightbird_ite);
			} //��������;
			else if ((*lightbird_ite)->IsCollision(Position(m_equipManager->GetRocket()->GetPositionX()+g_rocket_wh.x,
				m_equipManager->GetRocket()->GetPositionY()+g_rocket_wh.y), g_rocket_attck_distace))
			{
				m_hge->Effect_PlayEx(m_snd_lightbird_hurt, 100, 0, 1.0, false);  //����������Ч;
				this->hero->RandomDown((*lightbird_ite)->GetCurrenPosition().x,(*lightbird_ite)->GetCurrenPosition().y);
				lightbird_ite = m_b2_lightbirds.erase(lightbird_ite);
			} //��ƨ����;
			else if ((*lightbird_ite)->IsCollision(Position(m_equipManager->GetFart()->GetPositionX()+g_fart_wh.x,
				m_equipManager->GetFart()->GetPositionY()+g_fart_wh.y), g_fart_attck_distace))
			{
				m_hge->Effect_PlayEx(m_snd_lightbird_hurt, 100, 0, 1.0, false);  //����������Ч;
				this->hero->RandomDown((*lightbird_ite)->GetCurrenPosition().x,(*lightbird_ite)->GetCurrenPosition().y);
				lightbird_ite = m_b2_lightbirds.erase(lightbird_ite);
			}
			else
			{
				if ((*lightbird_ite)->IsHit())  //������ײ����;
				{ 
					m_hge->Effect_PlayEx(m_snd_pig_hurt, 100, 0, 1.0, false);  //����С��������Ч;
					this->hero->Hurt();
					lightbird_ite = this->m_b2_lightbirds.erase(lightbird_ite);
				}//�����߽�;
				else if ((*lightbird_ite)->GetCurrenPosition().x >WIN_WIDTH+ 1000)
				{
					--m_max_birds;
					lightbird_ite = this->m_b2_lightbirds.erase(lightbird_ite);
				}
				else
					++lightbird_ite;
			}
		}
	}


	//�µ���
	for (eggbird_ite = m_b2_eggbirds.begin();eggbird_ite != m_b2_eggbirds.end(); )
	{
		if (((*eggbird_ite)->GetCurrenPosition().x >= 0) && ((*eggbird_ite)->GetCurrenPosition().x <= 20))  //���ɵ���Ļ��ʱ����һ��;
		{
			m_hge->Effect_PlayEx(m_snd_eggbird_fly, 100, 0, 1.0,false);
		}
		if(NULL != (*eggbird_ite))
		{
			(*eggbird_ite)->Update(0.005f);
			(*eggbird_ite)->AI(Position(this->hero->GetPositionX()+g_pig_wh.x/2,this->hero->GetPositionY()+g_pig_wh.y/2),7,6,0);
			if ((*eggbird_ite)->IsLayegg())
			{
				CAnimEgg* l_egg = new CAnimEgg(this->m_hge, hero, "Egg.png",Position(0,0),50,70,1,30);
				m_b2_eggs.push_back(l_egg);
				l_egg->Play(HGEANIM_LOOP,(*eggbird_ite)->GetCurrenPosition(),g_b2_egg_x_speed,g_b2_egg_y_speed);
			}
			   //�������ӵ�����;
			if ((*eggbird_ite)->IsCollision(Position(m_equipManager->GetBullet()->GetPositionX()-g_bullet_wh.x,
				m_equipManager->GetBullet()->GetPositionY()-g_bullet_wh.y),g_bullet_attck_distace) 
				&& (((*eggbird_ite)->GetColor() == hero->GetColor()) || (hero->IsIgnoring())))  //��ɫƥ�����ʹ���ˡ����ӡ��Ŷ�������˺�;
			{
				m_hge->Effect_PlayEx(m_snd_eggbird_hurt, 100, 0, 1.0, false);   //����������Ч;
				this->hero->RandomDown((*eggbird_ite)->GetCurrenPosition().x,(*eggbird_ite)->GetCurrenPosition().y);  //�����װ��;
				eggbird_ite = m_b2_eggbirds.erase(eggbird_ite);
			}  //������������;
			else if ((*eggbird_ite)->IsCollision(Position(m_equipManager->GetRocket()->GetPositionX()-g_rocket_wh.x,
				m_equipManager->GetRocket()->GetPositionY()-g_rocket_wh.y), g_rocket_attck_distace))
			{
				m_hge->Effect_PlayEx(m_snd_eggbird_hurt, 100, 0, 1.0, false);   //����������Ч;
				this->hero->RandomDown((*eggbird_ite)->GetCurrenPosition().x,(*eggbird_ite)->GetCurrenPosition().y);
				eggbird_ite = m_b2_eggbirds.erase(eggbird_ite);
			}//������ƨ����;
			else if ((*eggbird_ite)->IsCollision(Position(m_equipManager->GetFart()->GetPositionX()+g_fart_wh.x,
				m_equipManager->GetFart()->GetPositionY()+g_fart_wh.y), g_fart_attck_distace))
			{
				m_hge->Effect_PlayEx(m_snd_eggbird_hurt, 100, 0, 1.0, false);   //����������Ч;
				this->hero->RandomDown((*eggbird_ite)->GetCurrenPosition().x,(*eggbird_ite)->GetCurrenPosition().y);
				eggbird_ite = m_b2_eggbirds.erase(eggbird_ite);
			}
			//�����ɳ��߽�;
			else if ((*eggbird_ite)->GetCurrenPosition().x>WIN_WIDTH+1000) 
			{
				--m_max_birds;
				eggbird_ite = m_b2_eggbirds.erase(eggbird_ite);
			}
			else
				++eggbird_ite;
		}
	}
	//ը����
	for (bombbird_ite = m_b2_bombbirds.begin();bombbird_ite !=  m_b2_bombbirds.end(); )
	{
		if (((*bombbird_ite)->GetCurrenPosition().x >= 0) && ((*bombbird_ite)->GetCurrenPosition().x <= 20))  //���ɵ���Ļ��ʱ����һ��;
		{
			m_hge->Effect_PlayEx(m_snd_bombbird_fly, 100, 0, 1.0,false);
		}
		if (NULL != (*bombbird_ite))
		{
			(*bombbird_ite)->Update(0.005f);
			(*bombbird_ite)->AI(Position(this->hero->GetPositionX()+g_pig_wh.x/2,this->hero->GetPositionY()+g_pig_wh.y/2),8,4,0);
			if ((*bombbird_ite)->IsLayegg())
			{
				CBombEgg* l_egg = new CBombEgg(this->m_hge, hero, "Egg.png",Position(0,70),50,70,1,15);
				this->m_b2_bombs.push_back(l_egg);
				l_egg->Play(HGEANIM_LOOP,(*bombbird_ite)->GetCurrenPosition(),g_b2_bomb_x_speed,g_b2_bomb_y_seepd);
			}  //���ӵ�����;
			if ((*bombbird_ite)->IsCollision(Position(m_equipManager->GetBullet()->GetPositionX()-g_bullet_wh.x,
				m_equipManager->GetBullet()->GetPositionY()-g_bullet_wh.y),g_bullet_attck_distace)
				&& (((*bombbird_ite)->GetColor() == hero->GetColor()) || (hero->IsIgnoring())))  //���������ɫƥ�����С��ʹ�á����ӡ�ʱ���ɶ�������˺�;
			{
				m_hge->Effect_PlayEx(m_snd_bombbird_hurt, 100, 0, 1.0, false);   //����������Ч;
				this->hero->RandomDown((*bombbird_ite)->GetCurrenPosition().x,(*bombbird_ite)->GetCurrenPosition().y);
				bombbird_ite = m_b2_bombbirds.erase(bombbird_ite);
			} //��������;
			else if ((*bombbird_ite)->IsCollision(Position(m_equipManager->GetRocket()->GetPositionX()-g_rocket_wh.x,
				m_equipManager->GetRocket()->GetPositionY()-g_rocket_wh.y), g_rocket_attck_distace))
			{
				m_hge->Effect_PlayEx(m_snd_bombbird_hurt, 100, 0, 1.0, false);   //����������Ч;
				this->hero->RandomDown((*bombbird_ite)->GetCurrenPosition().x,(*bombbird_ite)->GetCurrenPosition().y);
				bombbird_ite = m_b2_bombbirds.erase(bombbird_ite);
			}//��ƨ����;
			else if ((*bombbird_ite)->IsCollision(Position(m_equipManager->GetFart()->GetPositionX()+g_fart_wh.x,
				m_equipManager->GetFart()->GetPositionY()+g_fart_wh.y), g_fart_attck_distace))
			{
				m_hge->Effect_PlayEx(m_snd_bombbird_hurt, 100, 0, 1.0, false);   //����������Ч;
				this->hero->RandomDown((*bombbird_ite)->GetCurrenPosition().x,(*bombbird_ite)->GetCurrenPosition().y);
				bombbird_ite = m_b2_bombbirds.erase(bombbird_ite);
			}
			//�����߽�;
			else if ((*bombbird_ite)->GetCurrenPosition().x>WIN_WIDTH+1000)
			{
				--m_max_birds;
				bombbird_ite = m_b2_bombbirds.erase(bombbird_ite);
			}
			else
				++bombbird_ite;
		}
	}

	//����
	for (egg_ite = m_b2_eggs.begin();egg_ite != m_b2_eggs.end(); )
	{
		if(NULL != (*egg_ite)){
			(*egg_ite)->Update(0.005f);
			(*egg_ite)->Check(Position(this->hero->GetPositionX()+g_pig_wh.x/2,this->hero->GetPositionY()+g_pig_wh.y/2),4);
			if((*egg_ite)->IsHit())
			{
				if((*egg_ite)->GetState() == ATTACKED)
				{
					this->hero->Hurt();  //С���Ѫ;
					m_hge->Effect_PlayEx(m_snd_pig_hurt, 100, 0, 1.0, false); //����С��������Ч;
				}
				egg_ite = this->m_b2_eggs.erase(egg_ite);
			}
			else
				++egg_ite;
		}
	}

	//ը������
	for (bomb_ite = m_b2_bombs.begin();bomb_ite != m_b2_bombs.end();)
	{
		if (NULL != (*bomb_ite))
		{
			(*bomb_ite)->Update(0.005f);
			(*bomb_ite)->Check(Position(this->hero->GetPositionX()+g_pig_wh.x/2,this->hero->GetPositionY()+g_pig_wh.y/2),6);
			if ((*bomb_ite)->IsHit())
			{
				if ((*bomb_ite)->GetState() == ATTACKED)
				{
					this->hero->Hurt();  //С���Ѫ;
					m_hge->Effect_PlayEx(m_snd_pig_hurt, 100, 0, 1.0, false);  //����С��������Ч;
				}
				bomb_ite = this->m_b2_bombs.erase(bomb_ite);
			}
			else
				++bomb_ite;
		}
	}

	//��Ϸ��������;
	if ((hero->GetLife()<=0) || (m_max_birds<=0))
	{
		//MessageBox(NULL,L"������",L"option",MB_OK);
		//Reset();
		m_hge->System_SetState(HGE_HIDEMOUSE, false);
		m_cgame->SetGameState(GAME_OVER);
	}
	return battle1_status;
}

bool CBattle1::Render()
{
	
	//ʵ�ֳ����Ļ��ƣ���������������ȵ�;
	m_hge->Gfx_BeginScene();
	m_hge->Gfx_Clear(0);

	m_bkspr->Render(0, 0);						//���Ʊ���ͼ;
	//m_lifespr->RenderEx(1300, 0, 0, 1, 1);		//����С��Ѫ��;
	//m_rocket->RenderEx(20, 700, 0, 1, 1);		//���ƻ��װ��;
	//m_fart->RenderEx(90, 700, 0, 0.5, 0.5);		//���ơ�ƨ��װ��;
	hero->Render();								//������������
	m_equipManager->Render();					//����װ����

	//����ʣ������ͨ������;
	m_fnt->printf(950, 100, HGETEXT_LEFT, "%d",m_max_birds);

	//�������ƴ�����;
	for (bigbird_ite = m_b2_bigbirds.begin(); bigbird_ite != m_b2_bigbirds.end(); ++bigbird_ite)
	{
		(*bigbird_ite)->SetPositionX((*bigbird_ite)->GetCurrenPosition().x + m_Xoffset);   //�����m_Xoffset����֤��������;
		(*bigbird_ite)->Fly();

	}
	//���������µ���;
	for (eggbird_ite = m_b2_eggbirds.begin();eggbird_ite != m_b2_eggbirds.end();++eggbird_ite)
	{
		(*eggbird_ite)->SetPositionX((*eggbird_ite)->GetCurrenPosition().x + m_Xoffset);
		(*eggbird_ite)->Fly();
	}
	//������;
	for (lightbird_ite = m_b2_lightbirds.begin();lightbird_ite != m_b2_lightbirds.end();++lightbird_ite)
	{
		(*lightbird_ite)->SetPositionX((*lightbird_ite)->GetCurrenPosition().x + m_Xoffset);
		(*lightbird_ite)->Fly();
	}
	//ը����;
	for (bombbird_ite = m_b2_bombbirds.begin();bombbird_ite != m_b2_bombbirds.end();++bombbird_ite)
	{
		(*bombbird_ite)->SetPositionX((*bombbird_ite)->GetCurrenPosition().x + m_Xoffset);
		(*bombbird_ite)->Fly();
	}
	//����
	for (egg_ite = m_b2_eggs.begin();egg_ite != m_b2_eggs.end();++egg_ite)
	{//���õ���X���꣬��֤������ͼ�仯ʱ����Ҳ��Ӧ�ı任����;
		(*egg_ite)->SetPositionX((*egg_ite)->GetCurrenPosition().x + m_Xoffset);
		(*egg_ite)->Fly();
	}
	//ը����
	for (bomb_ite = m_b2_bombs.begin();bomb_ite != m_b2_bombs.end();++bomb_ite)
	{//���õ���X���꣬��֤�����ű���������任���任;
		(*bomb_ite)->SetPositionX((*bomb_ite)->GetCurrenPosition().x + m_Xoffset);
		(*bomb_ite)->Fly();
	}

	m_hge->Gfx_EndScene();

	return false;
}

void CBattle1::SetScore(int _score)    //���÷���;
{
	m_score = _score;
}

int  CBattle1::GetScore() const          //��ȡ�÷�;
{
	return m_score;
}

void CBattle1::UpdateBk()               //����С����ƶ������±���;
{
	if (m_hge->Input_GetKeyState( HGEK_LEFT))
	{
		if (hero->IsLeftWaitingPoint())
		{
			m_currentX = hero->GetTraveledLength() - LEFT_WAITING_POINT - 2;  //����ͼ��X��ʼ����;
			m_Xoffset = m_preX - m_currentX;                                //�ڴ˴�ȷ������ͼ��ǰһ֡�ͺ�һ֡��ƫ����;
			m_preX = m_currentX;
			m_bkspr->SetTextureRect(m_currentX, 0, 1366, 768); 
		}
		else   //���û����¡�����������Ҳ��ڡ���ȴ��㡱������ͼ�����ƶ��ĵ㣩ʱ����������;
		{
			m_Xoffset = 0.0;
		} 
	}
	else
	if (m_hge->Input_GetKeyState( HGEK_RIGHT))
	{
		if (hero->IsRightWaitingPoint())
		{
			m_currentX  = hero->GetTraveledLength() - RIGHT_WAITING_POINT;  //����ͼ��X����;
			m_Xoffset = m_preX - m_currentX;					//�ڴ˴�ȷ������ͼ��ǰһ֡�ͺ�һ֡��ƫ����;
			m_preX = m_currentX;
			m_bkspr->SetTextureRect(m_currentX, 0, 1366, 768, true);  //800 : RIGHT_WAITING_POINT
		}
		else   //���û����¡��Ҽ��������Ҳ��ڡ��ҵȴ��㡱������ͼ�����ƶ��ĵ㣩ʱ����������;
		{
			m_Xoffset = 0.0;
		}
	}
	else
		m_Xoffset = 0.0;
}

// void CBattle1::UpdateBirds()
// {    //���´�����;
// 	for(ite_Ani = m_animBirds.begin(); ite_Ani != m_animBirds.end(); ite_Ani++)
// 	{   
// 		//(*ite_Ani)->SetXDelta((*ite_Ani)->GetPositionX() + hero->GetTraveledLength());//
// 		if (hero->IsRightWaitingPoint())
// 		{
// 			//(*ite_Ani)->SetXDelta(RIGHT_WAITING_POINT - hero->GetTraveledLength());
// 			(*ite_Ani)->SetSpeed((*ite_Ani)->GetSpeed() - 1);
// 			//hero->OutRightWaitingPoint();
// 		}
// 		else
// 			(*ite_Ani)->SetXDelta(0.0);
// // 		else
// // 			if (hero->IsLeftWaitingPoint())
// // 			{
// // 				(*ite_Ani)->SetXDelta()
// // 			}
// 
// 		if((*ite_Ani)->GetPositionX() >= WIN_WIDTH)    //�����ɳ��߽磬С���Ѫ��ͬʱ������λ��;
// 		{
// 			hero->Hurt();
// 			(*ite_Ani)->SetPositionX(-10);
// 		}
// 
// 		(*ite_Ani)->Update(0.01f);
// 	}
// }

// void CBattle1::CheckCollision()
// {
// 	ite_Ani = m_animBirds.begin();
// 	for (; ite_Ani != m_animBirds.end(); ite_Ani++)
// 	{
// 		float x_bullet = m_equipManager->GetBullet()->GetPositionX();//�ӵ�λ��;
// 		float y_bullet = m_equipManager->GetBullet()->GetPositionY();
// 
// 		float x_bird   = (*ite_Ani)->GetPositionX();//���λ��;
// 		float y_bird   = (*ite_Ani)->GetPositionY();
// 
// 		//�ӵ��������ײ���;
// 		if ((((y_bird - y_bullet <= 67)&&(y_bird - y_bullet >= 0))||((y_bullet - y_bird >=90)&&(y_bullet - y_bird <=0)))
// 			&& (((x_bird - x_bullet <= 56)&&(x_bird - x_bullet >= 0))||((x_bullet - x_bird<= 100)&&(x_bullet - x_bird >= 0))))
// 		{                                                       
// 			if (hero->IsIgnoring())									 //���ʹ���ˡ����ӡ����򽫲�������ɫ��ƥ��;
// 			{
// 				(*ite_Ani)->SetPositionX(-20);
// 				SetScore(m_score + 20);								//���ù����Ľ���;
// 			}
// 			else if ((*ite_Ani)->GetColor() == hero->GetColor())	//δʹ�á����ӡ�����ʹ����ɫƥ��;
// 			{
// 				if ((y_bullet<100)&&(y_bullet>85))        
// 				{
// 					hero->RandomDown(x_bird,y_bird);				//���ݴ����λ�����õ���װ��;
// 				}
// 				(*ite_Ani)->SetPositionX(-20);
// 				SetScore(m_score + 20);
// 				// b(*ite_Ani)->SetRandomColor();
// 			}
// 
// 			//m_hge->Effect_Play(m_hge->Effect_Load("menu.wav",0));
// 		}
// 	}
// }  


void CBattle1::GenerateBirdsByWave()
{
	switch (m_wave)
	{
		//��һ��ս����
	case FIRST:
		//����5ֻ������
		m_max_birds = 3;
		for (int i = 0 ; i < 5; ++i)
		{	
			CBigMouseBird* l_bird = new CBigMouseBird(this->m_hge, hero,"Bigmousebird.png",(Color)this->m_hge->Random_Int(0,2),110,80,10,15);
			this->m_b2_bigbirds.push_back(l_bird);
			l_bird->Play(HGEANIM_LOOP,Position(this->m_hge->Random_Float((-500)*i,(-500)*(i+1)),g_b2_bigbird_y),g_b2_bigbird_x_speed,g_b2_bigbird_y_speed);
			
		}
		//����10ֻ�µ���

		for (int i  = 0;i < 10;++i)
		{
			CEggBird* l_bird = new CEggBird(this->m_hge,"EggBird.png",(Color)this->m_hge->Random_Int(0,2),90,100,7,15);
			this->m_b2_eggbirds.push_back(l_bird);
			l_bird->Play(HGEANIM_LOOP,Position(this->m_hge->Random_Float((-500)*i,(-500)*(i+1)),0),g_b2_eggbird_x_speed,g_b2_eggbird_y_speed);
		}
		m_card_state = false;
		break;

		//�ڶ���ս����
	case SECOND:
		//����7ֻ������
		m_max_birds = 4;
		for (int i = 0 ; i < 7; ++i)
		{	
			CBigMouseBird* l_bird = new CBigMouseBird(this->m_hge, hero,"Bigmousebird.png",(Color)this->m_hge->Random_Int(0,2),110,80,10,15);
			this->m_b2_bigbirds.push_back(l_bird);
			l_bird->Play(HGEANIM_LOOP,Position(this->m_hge->Random_Float((-1000)*i,(-1000)*(i+1)),g_b2_bigbird_y),g_b2_bigbird_x_speed,g_b2_bigbird_y_speed);

		}
		//����15ֻ�µ���

		for (int i  = 0;i < 20;++i)
		{
			CEggBird* l_bird = new CEggBird(this->m_hge,"EggBird.png",(Color)this->m_hge->Random_Int(0,2),90,100,7,15);
			this->m_b2_eggbirds.push_back(l_bird);
			l_bird->Play(HGEANIM_LOOP,Position(this->m_hge->Random_Float((-1000)*i,(-1000)*(i+1)),0),g_b2_eggbird_x_speed,g_b2_eggbird_y_speed);
		}
		//����10ֻ������ ;
		for (int i = 0 ; i < 10 ; ++i)
		{
			CLightBird* l_bird = new CLightBird(this->m_hge, hero,"LightningBird.png",(Color)m_hge->Random_Int(0,2),60,60,7,15);
			this->m_b2_lightbirds.push_back(l_bird);
			l_bird->Play(HGEANIM_LOOP,Position(this->m_hge->Random_Float((-1000)*i,(-1000)*(i+1)),g_b2_lightbird_y),g_b2_lightbird_x_speed,g_b2_lightbird_y_speed);

		}
		m_card_state = false;
		break;
		//������ս����
	case THIRD:
		//����10ֻ������
		m_max_birds = 5;
		for (int i = 0 ; i < 10; ++i)
		{	
			CBigMouseBird* l_bird = new CBigMouseBird(this->m_hge, hero, "Bigmousebird.png",(Color)this->m_hge->Random_Int(0,2),110,80,10,15);
			this->m_b2_bigbirds.push_back(l_bird);
			l_bird->Play(HGEANIM_LOOP,Position(this->m_hge->Random_Float((-1000)*i,(-1000)*(i+1)),g_b2_bigbird_y),g_b2_bigbird_x_speed,g_b2_bigbird_y_speed);

		}
		//����20ֻ�µ���

		for (int i  = 0;i < 20;++i)
		{
			CEggBird* l_bird = new CEggBird(this->m_hge,"EggBird.png",(Color)this->m_hge->Random_Int(0,2),90,100,7,15);
			this->m_b2_eggbirds.push_back(l_bird);
			l_bird->Play(HGEANIM_LOOP,Position(this->m_hge->Random_Float((-1000)*i,(-1000)*(i+1)),0),g_b2_eggbird_x_speed,g_b2_eggbird_y_speed);
		}
		//����15ֻ������ ��
		for (int i = 0 ; i < 15 ; ++i)
		{
			CLightBird* l_bird = new CLightBird(this->m_hge, hero, "LightningBird.png",(Color)m_hge->Random_Int(0,2),60,60,7,15);
			this->m_b2_lightbirds.push_back(l_bird);
			l_bird->Play(HGEANIM_LOOP,Position(this->m_hge->Random_Float((-1000)*i,(-1000)*(i+1)),g_b2_lightbird_y),g_b2_lightbird_x_speed,g_b2_lightbird_y_speed);

		}
		//����10ֻը����
		for (int i = 0 ;i < 10 ; ++i)
		{
			CEggBird* l_bird = new CEggBird(this->m_hge,"Bombbird.png",(Color)m_hge->Random_Int(0,2),70,90,8,15);
			this->m_b2_bombbirds.push_back(l_bird);
			l_bird->Play(HGEANIM_LOOP,Position(this->m_hge->Random_Float((-1000)*i,(-1000)*(i+1)),0),g_b2_bombbird_x_speed,g_b2_bombbird_y_speed);
		}
		m_card_state = false;
		break;
	default:
		break;
	}
}

void CBattle1::JumpCard()      //�ؿ���ת;
{
	bool l_isempty = (m_b2_bigbirds.empty()
		&&m_b2_eggbirds.empty()
		&&m_b2_lightbirds.empty()
		&&m_b2_bombbirds.empty()
		&&m_b2_bigbirds.empty()
		&&m_b2_eggs.empty()
		&&m_b2_bombs.empty());
	if (l_isempty&&m_max_birds>0)
	{
		MessageBox(NULL,L"next card",L"option",MB_OK);
		int l_wave = (int)m_wave;
		m_wave = (WAVE)(++l_wave);
		m_card_state = true;
		if (3 ==  (int)m_wave)
		{
			MessageBox(NULL,L" ��ϲ������ˣ�",L"option",MB_OK);
		}
	}
}

void CBattle1::Reset()   //����ս��;
{
// 	Release();   //�ͷ�ս����Դ;
// 	Init();       //z���³�ʼ��ս��;
	m_bkspr->SetTextureRect(0, 0, 1366, 768);        //���ñ���ͼ����������;
	m_preX = m_currentX = m_Xoffset = 0.0;           //������һ֡�͵�ǰ֡�ı���ͼ��X�����Լ�����֮��Ĳ�ֵ;
	hero->SetPositionX(200);      //����С������;
	hero->SetLife(10);       //����С��Ѫ��;
	
}

void CBattle1::Release()              //�ͷ���Դ;
{
	delete    m_bkspr;
	delete    m_fnt;
	delete    hero;
	delete    m_equipManager;
	//	delete    []m_bigMouseBirds;
	m_hge->Texture_Free(m_bktex);

	m_hge->Effect_Free(m_snd_bigmouse_fly);
	m_hge->Effect_Free(m_snd_bigmouse_hurt);
	m_hge->Effect_Free(m_snd_bombbird_fly);
	m_hge->Effect_Free(m_snd_bombbird_hurt);
	m_hge->Effect_Free(m_snd_eggbird_fly);
	m_hge->Effect_Free(m_snd_eggbird_hurt);
	m_hge->Effect_Free(m_snd_lightbird_fly);
	m_hge->Effect_Free(m_snd_lightbird_hurt);
	m_hge->Effect_Free(m_snd_pig_hurt);
}