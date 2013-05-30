#include "CBattle1.h"
#include "CGlobal.h"
#include "CGame.h"

class CGame; //因为要使用WIN_WIDTH和WIN_HEIGHT;



CBattle1::CBattle1(HGE *_hge, CGame *_game)
{
	m_hge = _hge;
	m_cgame = _game;
	m_max_birds = 2;   //初始化最多能漏掉的鸟数量;
}

CBattle1::~CBattle1()
{

}

void CBattle1::Init()
{
	/*1.背景显示;
	2.音效播放;
	3.角色显示;
	4.道具显示;
	5.角色状态显示：血量、经验值;*/

	SetScore(0);                                //初始分数为0;

	m_fnt=new hgeFont("font1.fnt");               //创建字体;                                  
	/************************************************************************/
	/*                   加载和创建背景资源；                               */
	/************************************************************************/
	
	m_bktex  = m_hge->Texture_Load("bk.png");  //加载背景图资源；
	m_bkspr = new hgeSprite(m_bktex, 0, 0, 1366, 768);//创建背景精灵；
	m_preX = m_currentX = m_Xoffset = 0.0;                 //初始化上一帧和当前帧的背景图的X坐标以及他们之间的差值;

	/************************************************************************/
	/*                    加载音效；                    */
	m_snd_bigmouse_fly = m_hge->Effect_Load("老乌鸦叫声.mp3");
	m_snd_bigmouse_hurt = m_hge->Effect_Load("老乌鸦受伤.wav");

	m_snd_eggbird_fly = m_hge->Effect_Load("蛋鸟飞翔音效.wav");
	m_snd_eggbird_hurt = m_hge->Effect_Load("蛋鸟受伤音效.wav");

	m_snd_lightbird_fly = m_hge->Effect_Load("闪电鸟飞翔音效.wav");
	m_snd_lightbird_hurt = m_hge->Effect_Load("闪电鸟受伤音效.wav");

	m_snd_bombbird_fly = m_hge->Effect_Load("爆炸鸟飞翔音效.wav");
	m_snd_bombbird_hurt = m_hge->Effect_Load("爆炸鸟受伤音效.wav");

	m_snd_pig_hurt = m_hge->Effect_Load("小猪受伤音效.wav");
	/************************************************************************/


	/************************************************************************/
	/*                创建猪猪侠并初始化相应的数据                        */
	/************************************************************************/
	hero = new CYoungPig(m_hge);
	hero->SetLife(5);         //初始化小猪血量;
	hero->LoadTexture("猪猪侠.png");
	hero->SetImage(3, 5, 0, 0, 69, 51);
	//hero->SetFrame(3);
	//hero->SetMode(HGEANIM_NOLOOP);
	hero->Play();

	/************************************************************************/
	/*               创建鸟根据波数                                           */
	/************************************************************************/ 
	m_wave = FIRST;//初始化波数为第一波；
	
	m_card_state = true;
	/************************************************************************/
	/*                  创建装备管理                                       */
	/************************************************************************/
	m_equipManager = new CEquipmentManager(hero, m_hge); 

}

bool battle1_status = false;
float _timer;



//在这部分实现逻辑判断和逻辑控制,如控制猪的移动，碰撞检测;
bool CBattle1::Run()  //每帧调用该函数，每秒100帧左右;
{
	
	_timer = m_hge->Timer_GetTime();
	//根据波数来创建鸟；
	if(m_card_state)
		this->GenerateBirdsByWave();
	//实时监测是否跳转到下一波；
	this->JumpCard();
	//更新游戏背景;
	UpdateBk();

	//更新猪的状态;
	if(hero->Update())
		battle1_status = true;
	hero->UpdateEquipmentXpo(m_Xoffset);  //通过猪来更新掉下的装备的坐标;

	//更新鸟;
	//UpdateBirds();

	//根据小猪操作来使用装备;
	m_equipManager->Update();
	
// 	float x_pig = hero->GetPositionX();
// 	float y_pig = hero->GetPositionY();
// 
// 
// 	CheckCollision();    //检测针刺和鸟的碰撞;


	/************************************************************************/
	/*                 鸟的更新                                             */
	/************************************************************************/
	
	//大嘴鸟；
	for (bigbird_ite = m_b2_bigbirds.begin(); bigbird_ite != m_b2_bigbirds.end(); )
	{
		if (((*bigbird_ite)->GetCurrenPosition().x >= 0) && (*bigbird_ite)->GetCurrenPosition().x <= 20)  //当飞到屏幕中时，叫一声;
		{
			m_hge->Effect_PlayEx(m_snd_bigmouse_fly, 100, 0, 1.0, false);
		}
		if(NULL != (*bigbird_ite))
		{
			(*bigbird_ite)->Update(0.005f);
			(*bigbird_ite)->AI(Position(this->hero->GetPositionX()+g_pig_wh.x/2,this->hero->GetPositionY()+g_pig_wh.y/2),10,7,4);
			if((*bigbird_ite)->IsHit())  //大嘴鸟撞到小猪;
			{
				m_hge->Effect_PlayEx(m_snd_bigmouse_hurt, 100, 0, 1.0, false);  //播放大嘴鸟音效;
				m_hge->Effect_PlayEx(m_snd_pig_hurt, 100, 0, 1.0, false);   //播放小猪音效;
				this->hero->Hurt();  //减血;
				bigbird_ite = this->m_b2_bigbirds.erase(bigbird_ite);
			}//超出边界;
			else if ((*bigbird_ite)->GetCurrenPosition().x>WIN_WIDTH+1000)
			{
				bigbird_ite = this->m_b2_bigbirds.erase(bigbird_ite);
			}
			else

				++bigbird_ite;
		}
	}
	//闪电鸟;
	for (lightbird_ite  = m_b2_lightbirds.begin();lightbird_ite != m_b2_lightbirds.end(); )
	{
		if (((*lightbird_ite)->GetCurrenPosition().x >= 0) && (*lightbird_ite)->GetCurrenPosition().x <= 20)  //当飞到屏幕中时，叫一声;
		{
			m_hge->Effect_PlayEx(m_snd_lightbird_fly, 100, 0, 1.0, false);
		}
		if (NULL != (*lightbird_ite))
		{
			(*lightbird_ite)->Update(0.005f);
			(*lightbird_ite)->AI(Position(this->hero->GetPositionX()+g_pig_wh.x/2,this->hero->GetPositionY()+g_pig_wh.y/2),7,3,0);
			//与子弹相撞;
			if ((*lightbird_ite)->IsCollision(Position(m_equipManager->GetBullet()->GetPositionX()-g_bullet_wh.x,
				m_equipManager->GetBullet()->GetPositionY()-g_bullet_wh.y),g_bullet_attck_distace)
				&& (((*lightbird_ite)->GetColor() == hero->GetColor()) || (hero->IsIgnoring()))) //与猪进行颜色匹配或者使用“无视”时，可对鸟造成攻击;
			{
				m_hge->Effect_PlayEx(m_snd_lightbird_hurt, 100, 0, 1.0, false);  //播放受伤音效;
				this->hero->RandomDown((*lightbird_ite)->GetCurrenPosition().x,(*lightbird_ite)->GetCurrenPosition().y);
				lightbird_ite = m_b2_lightbirds.erase(lightbird_ite);
			} //与火箭相碰;
			else if ((*lightbird_ite)->IsCollision(Position(m_equipManager->GetRocket()->GetPositionX()+g_rocket_wh.x,
				m_equipManager->GetRocket()->GetPositionY()+g_rocket_wh.y), g_rocket_attck_distace))
			{
				m_hge->Effect_PlayEx(m_snd_lightbird_hurt, 100, 0, 1.0, false);  //播放受伤音效;
				this->hero->RandomDown((*lightbird_ite)->GetCurrenPosition().x,(*lightbird_ite)->GetCurrenPosition().y);
				lightbird_ite = m_b2_lightbirds.erase(lightbird_ite);
			} //与屁相碰;
			else if ((*lightbird_ite)->IsCollision(Position(m_equipManager->GetFart()->GetPositionX()+g_fart_wh.x,
				m_equipManager->GetFart()->GetPositionY()+g_fart_wh.y), g_fart_attck_distace))
			{
				m_hge->Effect_PlayEx(m_snd_lightbird_hurt, 100, 0, 1.0, false);  //播放受伤音效;
				this->hero->RandomDown((*lightbird_ite)->GetCurrenPosition().x,(*lightbird_ite)->GetCurrenPosition().y);
				lightbird_ite = m_b2_lightbirds.erase(lightbird_ite);
			}
			else
			{
				if ((*lightbird_ite)->IsHit())  //闪电鸟撞上猪;
				{ 
					m_hge->Effect_PlayEx(m_snd_pig_hurt, 100, 0, 1.0, false);  //播放小猪受伤音效;
					this->hero->Hurt();
					lightbird_ite = this->m_b2_lightbirds.erase(lightbird_ite);
				}//超出边界;
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


	//下蛋鸟；
	for (eggbird_ite = m_b2_eggbirds.begin();eggbird_ite != m_b2_eggbirds.end(); )
	{
		if (((*eggbird_ite)->GetCurrenPosition().x >= 0) && ((*eggbird_ite)->GetCurrenPosition().x <= 20))  //当飞到屏幕中时，叫一声;
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
			   //蛋鸟与子弹相碰;
			if ((*eggbird_ite)->IsCollision(Position(m_equipManager->GetBullet()->GetPositionX()-g_bullet_wh.x,
				m_equipManager->GetBullet()->GetPositionY()-g_bullet_wh.y),g_bullet_attck_distace) 
				&& (((*eggbird_ite)->GetColor() == hero->GetColor()) || (hero->IsIgnoring())))  //颜色匹配或者使用了“无视”才对鸟造成伤害;
			{
				m_hge->Effect_PlayEx(m_snd_eggbird_hurt, 100, 0, 1.0, false);   //播放受伤音效;
				this->hero->RandomDown((*eggbird_ite)->GetCurrenPosition().x,(*eggbird_ite)->GetCurrenPosition().y);  //随机掉装备;
				eggbird_ite = m_b2_eggbirds.erase(eggbird_ite);
			}  //蛋鸟与火箭相碰;
			else if ((*eggbird_ite)->IsCollision(Position(m_equipManager->GetRocket()->GetPositionX()-g_rocket_wh.x,
				m_equipManager->GetRocket()->GetPositionY()-g_rocket_wh.y), g_rocket_attck_distace))
			{
				m_hge->Effect_PlayEx(m_snd_eggbird_hurt, 100, 0, 1.0, false);   //播放受伤音效;
				this->hero->RandomDown((*eggbird_ite)->GetCurrenPosition().x,(*eggbird_ite)->GetCurrenPosition().y);
				eggbird_ite = m_b2_eggbirds.erase(eggbird_ite);
			}//蛋鸟与屁相碰;
			else if ((*eggbird_ite)->IsCollision(Position(m_equipManager->GetFart()->GetPositionX()+g_fart_wh.x,
				m_equipManager->GetFart()->GetPositionY()+g_fart_wh.y), g_fart_attck_distace))
			{
				m_hge->Effect_PlayEx(m_snd_eggbird_hurt, 100, 0, 1.0, false);   //播放受伤音效;
				this->hero->RandomDown((*eggbird_ite)->GetCurrenPosition().x,(*eggbird_ite)->GetCurrenPosition().y);
				eggbird_ite = m_b2_eggbirds.erase(eggbird_ite);
			}
			//如果鸟飞出边界;
			else if ((*eggbird_ite)->GetCurrenPosition().x>WIN_WIDTH+1000) 
			{
				--m_max_birds;
				eggbird_ite = m_b2_eggbirds.erase(eggbird_ite);
			}
			else
				++eggbird_ite;
		}
	}
	//炸弹鸟；
	for (bombbird_ite = m_b2_bombbirds.begin();bombbird_ite !=  m_b2_bombbirds.end(); )
	{
		if (((*bombbird_ite)->GetCurrenPosition().x >= 0) && ((*bombbird_ite)->GetCurrenPosition().x <= 20))  //当飞到屏幕中时，叫一声;
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
			}  //与子弹相碰;
			if ((*bombbird_ite)->IsCollision(Position(m_equipManager->GetBullet()->GetPositionX()-g_bullet_wh.x,
				m_equipManager->GetBullet()->GetPositionY()-g_bullet_wh.y),g_bullet_attck_distace)
				&& (((*bombbird_ite)->GetColor() == hero->GetColor()) || (hero->IsIgnoring())))  //与猪进行颜色匹配或者小猪使用“无视”时，可对鸟造成伤害;
			{
				m_hge->Effect_PlayEx(m_snd_bombbird_hurt, 100, 0, 1.0, false);   //播放受伤音效;
				this->hero->RandomDown((*bombbird_ite)->GetCurrenPosition().x,(*bombbird_ite)->GetCurrenPosition().y);
				bombbird_ite = m_b2_bombbirds.erase(bombbird_ite);
			} //与火箭相碰;
			else if ((*bombbird_ite)->IsCollision(Position(m_equipManager->GetRocket()->GetPositionX()-g_rocket_wh.x,
				m_equipManager->GetRocket()->GetPositionY()-g_rocket_wh.y), g_rocket_attck_distace))
			{
				m_hge->Effect_PlayEx(m_snd_bombbird_hurt, 100, 0, 1.0, false);   //播放受伤音效;
				this->hero->RandomDown((*bombbird_ite)->GetCurrenPosition().x,(*bombbird_ite)->GetCurrenPosition().y);
				bombbird_ite = m_b2_bombbirds.erase(bombbird_ite);
			}//与屁相碰;
			else if ((*bombbird_ite)->IsCollision(Position(m_equipManager->GetFart()->GetPositionX()+g_fart_wh.x,
				m_equipManager->GetFart()->GetPositionY()+g_fart_wh.y), g_fart_attck_distace))
			{
				m_hge->Effect_PlayEx(m_snd_bombbird_hurt, 100, 0, 1.0, false);   //播放受伤音效;
				this->hero->RandomDown((*bombbird_ite)->GetCurrenPosition().x,(*bombbird_ite)->GetCurrenPosition().y);
				bombbird_ite = m_b2_bombbirds.erase(bombbird_ite);
			}
			//超出边界;
			else if ((*bombbird_ite)->GetCurrenPosition().x>WIN_WIDTH+1000)
			{
				--m_max_birds;
				bombbird_ite = m_b2_bombbirds.erase(bombbird_ite);
			}
			else
				++bombbird_ite;
		}
	}

	//蛋：
	for (egg_ite = m_b2_eggs.begin();egg_ite != m_b2_eggs.end(); )
	{
		if(NULL != (*egg_ite)){
			(*egg_ite)->Update(0.005f);
			(*egg_ite)->Check(Position(this->hero->GetPositionX()+g_pig_wh.x/2,this->hero->GetPositionY()+g_pig_wh.y/2),4);
			if((*egg_ite)->IsHit())
			{
				if((*egg_ite)->GetState() == ATTACKED)
				{
					this->hero->Hurt();  //小猪掉血;
					m_hge->Effect_PlayEx(m_snd_pig_hurt, 100, 0, 1.0, false); //播放小猪受伤音效;
				}
				egg_ite = this->m_b2_eggs.erase(egg_ite);
			}
			else
				++egg_ite;
		}
	}

	//炸弹蛋；
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
					this->hero->Hurt();  //小猪掉血;
					m_hge->Effect_PlayEx(m_snd_pig_hurt, 100, 0, 1.0, false);  //播放小猪受伤音效;
				}
				bomb_ite = this->m_b2_bombs.erase(bomb_ite);
			}
			else
				++bomb_ite;
		}
	}

	//游戏结束条件;
	if ((hero->GetLife()<=0) || (m_max_birds<=0))
	{
		//MessageBox(NULL,L"你输了",L"option",MB_OK);
		//Reset();
		m_hge->System_SetState(HGE_HIDEMOUSE, false);
		m_cgame->SetGameState(GAME_OVER);
	}
	return battle1_status;
}

bool CBattle1::Render()
{
	
	//实现场景的绘制，包括背景，鸟，猪等等;
	m_hge->Gfx_BeginScene();
	m_hge->Gfx_Clear(0);

	m_bkspr->Render(0, 0);						//绘制背景图;
	//m_lifespr->RenderEx(1300, 0, 0, 1, 1);		//绘制小猪血量;
	//m_rocket->RenderEx(20, 700, 0, 1, 1);		//绘制火箭装备;
	//m_fart->RenderEx(90, 700, 0, 0.5, 0.5);		//绘制“屁”装备;
	hero->Render();								//绘制猪猪侠；
	m_equipManager->Render();					//绘制装备；

	//绘制剩余的鸟可通过数量;
	m_fnt->printf(950, 100, HGETEXT_LEFT, "%d",m_max_birds);

	//迭代绘制大嘴鸟;
	for (bigbird_ite = m_b2_bigbirds.begin(); bigbird_ite != m_b2_bigbirds.end(); ++bigbird_ite)
	{
		(*bigbird_ite)->SetPositionX((*bigbird_ite)->GetCurrenPosition().x + m_Xoffset);   //鸟加上m_Xoffset，保证世界坐标;
		(*bigbird_ite)->Fly();

	}
	//迭代绘制下蛋鸟;
	for (eggbird_ite = m_b2_eggbirds.begin();eggbird_ite != m_b2_eggbirds.end();++eggbird_ite)
	{
		(*eggbird_ite)->SetPositionX((*eggbird_ite)->GetCurrenPosition().x + m_Xoffset);
		(*eggbird_ite)->Fly();
	}
	//闪电鸟;
	for (lightbird_ite = m_b2_lightbirds.begin();lightbird_ite != m_b2_lightbirds.end();++lightbird_ite)
	{
		(*lightbird_ite)->SetPositionX((*lightbird_ite)->GetCurrenPosition().x + m_Xoffset);
		(*lightbird_ite)->Fly();
	}
	//炸弹鸟;
	for (bombbird_ite = m_b2_bombbirds.begin();bombbird_ite != m_b2_bombbirds.end();++bombbird_ite)
	{
		(*bombbird_ite)->SetPositionX((*bombbird_ite)->GetCurrenPosition().x + m_Xoffset);
		(*bombbird_ite)->Fly();
	}
	//蛋；
	for (egg_ite = m_b2_eggs.begin();egg_ite != m_b2_eggs.end();++egg_ite)
	{//设置蛋的X坐标，保证当背景图变化时，蛋也相应的变换坐标;
		(*egg_ite)->SetPositionX((*egg_ite)->GetCurrenPosition().x + m_Xoffset);
		(*egg_ite)->Fly();
	}
	//炸弹；
	for (bomb_ite = m_b2_bombs.begin();bomb_ite != m_b2_bombs.end();++bomb_ite)
	{//设置蛋的X坐标，保证其随着背景的坐标变换而变换;
		(*bomb_ite)->SetPositionX((*bomb_ite)->GetCurrenPosition().x + m_Xoffset);
		(*bomb_ite)->Fly();
	}

	m_hge->Gfx_EndScene();

	return false;
}

void CBattle1::SetScore(int _score)    //设置分数;
{
	m_score = _score;
}

int  CBattle1::GetScore() const          //获取得分;
{
	return m_score;
}

void CBattle1::UpdateBk()               //根据小猪的移动来更新背景;
{
	if (m_hge->Input_GetKeyState( HGEK_LEFT))
	{
		if (hero->IsLeftWaitingPoint())
		{
			m_currentX = hero->GetTraveledLength() - LEFT_WAITING_POINT - 2;  //背景图的X初始坐标;
			m_Xoffset = m_preX - m_currentX;                                //在此处确定背景图的前一帧和后一帧的偏移量;
			m_preX = m_currentX;
			m_bkspr->SetTextureRect(m_currentX, 0, 1366, 768); 
		}
		else   //当用户按下“左键”，并且不在“左等待点”（背景图向右移动的点）时，背景不动;
		{
			m_Xoffset = 0.0;
		} 
	}
	else
	if (m_hge->Input_GetKeyState( HGEK_RIGHT))
	{
		if (hero->IsRightWaitingPoint())
		{
			m_currentX  = hero->GetTraveledLength() - RIGHT_WAITING_POINT;  //背景图的X坐标;
			m_Xoffset = m_preX - m_currentX;					//在此处确定背景图的前一帧和后一帧的偏移量;
			m_preX = m_currentX;
			m_bkspr->SetTextureRect(m_currentX, 0, 1366, 768, true);  //800 : RIGHT_WAITING_POINT
		}
		else   //当用户按下“右键”，并且不在“右等待点”（背景图向左移动的点）时，背景不动;
		{
			m_Xoffset = 0.0;
		}
	}
	else
		m_Xoffset = 0.0;
}

// void CBattle1::UpdateBirds()
// {    //更新大嘴鸟;
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
// 		if((*ite_Ani)->GetPositionX() >= WIN_WIDTH)    //如果鸟飞出边界，小猪减血，同时重置鸟位置;
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
// 		float x_bullet = m_equipManager->GetBullet()->GetPositionX();//子弹位置;
// 		float y_bullet = m_equipManager->GetBullet()->GetPositionY();
// 
// 		float x_bird   = (*ite_Ani)->GetPositionX();//鸟的位置;
// 		float y_bird   = (*ite_Ani)->GetPositionY();
// 
// 		//子弹和鸟的碰撞检测;
// 		if ((((y_bird - y_bullet <= 67)&&(y_bird - y_bullet >= 0))||((y_bullet - y_bird >=90)&&(y_bullet - y_bird <=0)))
// 			&& (((x_bird - x_bullet <= 56)&&(x_bird - x_bullet >= 0))||((x_bullet - x_bird<= 100)&&(x_bullet - x_bird >= 0))))
// 		{                                                       
// 			if (hero->IsIgnoring())									 //如果使用了“无视”，则将不进行颜色的匹配;
// 			{
// 				(*ite_Ani)->SetPositionX(-20);
// 				SetScore(m_score + 20);								//设置攻击的奖励;
// 			}
// 			else if ((*ite_Ani)->GetColor() == hero->GetColor())	//未使用“无视”，则使用颜色匹配;
// 			{
// 				if ((y_bullet<100)&&(y_bullet>85))        
// 				{
// 					hero->RandomDown(x_bird,y_bird);				//根据打到鸟的位置设置掉下装备;
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
		//第一波战争；
	case FIRST:
		//创建5只大嘴鸟；
		m_max_birds = 3;
		for (int i = 0 ; i < 5; ++i)
		{	
			CBigMouseBird* l_bird = new CBigMouseBird(this->m_hge, hero,"Bigmousebird.png",(Color)this->m_hge->Random_Int(0,2),110,80,10,15);
			this->m_b2_bigbirds.push_back(l_bird);
			l_bird->Play(HGEANIM_LOOP,Position(this->m_hge->Random_Float((-500)*i,(-500)*(i+1)),g_b2_bigbird_y),g_b2_bigbird_x_speed,g_b2_bigbird_y_speed);
			
		}
		//创建10只下蛋鸟；

		for (int i  = 0;i < 10;++i)
		{
			CEggBird* l_bird = new CEggBird(this->m_hge,"EggBird.png",(Color)this->m_hge->Random_Int(0,2),90,100,7,15);
			this->m_b2_eggbirds.push_back(l_bird);
			l_bird->Play(HGEANIM_LOOP,Position(this->m_hge->Random_Float((-500)*i,(-500)*(i+1)),0),g_b2_eggbird_x_speed,g_b2_eggbird_y_speed);
		}
		m_card_state = false;
		break;

		//第二波战争；
	case SECOND:
		//创建7只大嘴鸟；
		m_max_birds = 4;
		for (int i = 0 ; i < 7; ++i)
		{	
			CBigMouseBird* l_bird = new CBigMouseBird(this->m_hge, hero,"Bigmousebird.png",(Color)this->m_hge->Random_Int(0,2),110,80,10,15);
			this->m_b2_bigbirds.push_back(l_bird);
			l_bird->Play(HGEANIM_LOOP,Position(this->m_hge->Random_Float((-1000)*i,(-1000)*(i+1)),g_b2_bigbird_y),g_b2_bigbird_x_speed,g_b2_bigbird_y_speed);

		}
		//创建15只下蛋鸟；

		for (int i  = 0;i < 20;++i)
		{
			CEggBird* l_bird = new CEggBird(this->m_hge,"EggBird.png",(Color)this->m_hge->Random_Int(0,2),90,100,7,15);
			this->m_b2_eggbirds.push_back(l_bird);
			l_bird->Play(HGEANIM_LOOP,Position(this->m_hge->Random_Float((-1000)*i,(-1000)*(i+1)),0),g_b2_eggbird_x_speed,g_b2_eggbird_y_speed);
		}
		//创建10只闪电鸟 ;
		for (int i = 0 ; i < 10 ; ++i)
		{
			CLightBird* l_bird = new CLightBird(this->m_hge, hero,"LightningBird.png",(Color)m_hge->Random_Int(0,2),60,60,7,15);
			this->m_b2_lightbirds.push_back(l_bird);
			l_bird->Play(HGEANIM_LOOP,Position(this->m_hge->Random_Float((-1000)*i,(-1000)*(i+1)),g_b2_lightbird_y),g_b2_lightbird_x_speed,g_b2_lightbird_y_speed);

		}
		m_card_state = false;
		break;
		//第三波战争；
	case THIRD:
		//创建10只大嘴鸟；
		m_max_birds = 5;
		for (int i = 0 ; i < 10; ++i)
		{	
			CBigMouseBird* l_bird = new CBigMouseBird(this->m_hge, hero, "Bigmousebird.png",(Color)this->m_hge->Random_Int(0,2),110,80,10,15);
			this->m_b2_bigbirds.push_back(l_bird);
			l_bird->Play(HGEANIM_LOOP,Position(this->m_hge->Random_Float((-1000)*i,(-1000)*(i+1)),g_b2_bigbird_y),g_b2_bigbird_x_speed,g_b2_bigbird_y_speed);

		}
		//创建20只下蛋鸟；

		for (int i  = 0;i < 20;++i)
		{
			CEggBird* l_bird = new CEggBird(this->m_hge,"EggBird.png",(Color)this->m_hge->Random_Int(0,2),90,100,7,15);
			this->m_b2_eggbirds.push_back(l_bird);
			l_bird->Play(HGEANIM_LOOP,Position(this->m_hge->Random_Float((-1000)*i,(-1000)*(i+1)),0),g_b2_eggbird_x_speed,g_b2_eggbird_y_speed);
		}
		//创建15只闪电鸟 ：
		for (int i = 0 ; i < 15 ; ++i)
		{
			CLightBird* l_bird = new CLightBird(this->m_hge, hero, "LightningBird.png",(Color)m_hge->Random_Int(0,2),60,60,7,15);
			this->m_b2_lightbirds.push_back(l_bird);
			l_bird->Play(HGEANIM_LOOP,Position(this->m_hge->Random_Float((-1000)*i,(-1000)*(i+1)),g_b2_lightbird_y),g_b2_lightbird_x_speed,g_b2_lightbird_y_speed);

		}
		//创建10只炸弹鸟；
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

void CBattle1::JumpCard()      //关卡跳转;
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
			MessageBox(NULL,L" 恭喜你过关了！",L"option",MB_OK);
		}
	}
}

void CBattle1::Reset()   //重置战场;
{
// 	Release();   //释放战场资源;
// 	Init();       //z重新初始化战场;
	m_bkspr->SetTextureRect(0, 0, 1366, 768);        //重置背景图的纹理坐标;
	m_preX = m_currentX = m_Xoffset = 0.0;           //重置上一帧和当前帧的背景图的X坐标以及他们之间的差值;
	hero->SetPositionX(200);      //重置小猪坐标;
	hero->SetLife(10);       //重置小猪血量;
	
}

void CBattle1::Release()              //释放资源;
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