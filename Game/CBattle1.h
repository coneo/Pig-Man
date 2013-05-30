/*****************************************************
ս����������ս�ĳ��أ���ս���У�Ҫʵ�����¼��㣺
	1.������ʾ;
	2.��Ч����;
	3.��ɫ��ʾ;
	4.������ʾ;
	5.��ɫ״̬��ʾ��Ѫ��������ֵ;
	***************************************************/
#pragma once

//ϵͳ�Դ�ͷ�ļ���
#include <list>
#include "hge.h"
#include "hgefont.h"
#include "hgegui.h"
#include "hgeparticle.h"

//��������װ��ͷ�ļ���
#include "CYoungPig.h"
#include "CEquipmentManager.h"


//��͵���ͷ�ļ���
#include "CAnimation.h"
#include "CAnimEgg.h"
#include "CBigMouseBird.h"
#include "CBombEgg.h"
#include "CEggBird.h"
#include "CLightBird.h"

class CGame;       //��battle��Ҫ������Ϸ״̬������ҪCGame;

//������ȫ�ֱ�����
enum WAVE {FIRST, SECOND, THIRD};
//�������ȫ�ֱ�����
const float g_b2_bigbird_y = 570;
const float g_b2_bigbird_x_speed = 2.0f;
const float g_b2_bigbird_y_speed = 0.0f;
//�µ����ȫ�ֱ�����
const float g_b2_eggbird_y = 50;//��ĸ߶ȣ�
const float g_b2_eggbird_x_speed = 2.0f;
const float g_b2_eggbird_y_speed = 0.0f;
//�µ����ȫ�ֱ�����
const float g_b2_bombbird_y = 100;
const float g_b2_bombbird_x_speed = 2.0f;
const float g_b2_bombbird_y_speed = 0.0f;
//������
const float g_b2_lightbird_y = 0;//��ĸ߶ȣ�
const float g_b2_lightbird_x_speed = 2.0f;
const float g_b2_lightbird_y_speed = 0.0f;
//����ȫ�ֱ�����
const float g_b2_egg_x_speed = 0.0f;
const float g_b2_egg_y_speed = 1.0f;
//ը�����ٶȣ�
const float g_b2_bomb_x_speed = 0.0f;
const float g_b2_bomb_y_seepd = 1.0f;
//��������Ⱥ͸߶ȣ�
const Position g_pig_wh = Position(69,51);

//�ӵ�������Χ��
const float g_bullet_attck_distace = 60;
const Position g_bullet_wh =Position(33,52);

//���������Χ;
const float g_rocket_attck_distace = 200;
const Position g_rocket_wh = Position(66,66);

//ƨ�Ĺ�����Χ;
const float g_fart_attck_distace = 500;
const Position g_fart_wh = Position(100,50);


class CBattle1
{
public:
	CBattle1(HGE *_hge, CGame *_game);
	~CBattle1();
	void    Init();					//��ս�����г�ʼ��������һЩ������Դ,����ʾ����;
	
	bool    Run();					//��ʼս�������ⲿ��ʵ���߼��жϺ��߼����ƣ�
    
	bool    Render();				//�Գ��������������ͽ�ɫ�����пɼ��ģ����л���;
	
	void    UpdateBk();				//���±���ͼ,��֤��������;
	//void    UpdateBirds();		//����������꣬ͬʱ��֤��������;
	//void    CheckCollision();		//���������̣�������������ƨ����ײ, ��������Ӧ��Ӧ;
	
	void    SetScore(int _score);   //���÷���;
	int     GetScore() const;       //��ȡ����;
	
	void    GenerateBirdsByWave();	//���ݡ���������������;

	void    JumpCard();             //��ת������
	
	void	Reset();                
	void    Release();				//�ͷ���Դ;
private:
	HGE            *m_hge;          //����
	CGame          *m_cgame;        //��Ϸ��;

	hgeFont		   *m_fnt;          
	hgeSprite      *m_bkspr;		//���ڻ��Ʊ���ͼ;
	HTEXTURE        m_bktex;		//����ͼ������;
	float		    m_preX;      //ǰһ֡����ͼ���Ͻǵ�X���꣬���ڱ���ͼ��Y���겻�䣨����0�����ʲ����Ǳ���ͼ��Y����;
	float			m_currentX;	   //��ǰ֡�ı���ͼ�����Ͻ�X���꣬���ڱ���ͼ��Y���겻�䣨����0�����ʲ����Ǳ���ͼ��Y����;
	float			m_Xoffset;   //����ͼ��ǰһ֡�ͺ�һ֡�Ĳ�ֵ;

	int             m_score;		//��Ϸ�ĵ÷�;

	CYoungPig      *hero;					// ��Ķ���
	CEquipmentManager   *m_equipManager;	//װ��������;
	WAVE            m_wave;					//��¼ս���Ĳ�����
	//���Ϊ����ʧ�ܣ�
	int             m_max_birds;            //ÿһ�����©������
	bool            m_card_state;           //ÿһ����״̬����

	///////////////////////////////////��Ч/////////////////////////////////////
	HEFFECT  m_snd_bigmouse_fly;    //�������������˵�����;
	HEFFECT  m_snd_bigmouse_hurt;  
	HEFFECT  m_snd_eggbird_fly;     //�����������˵���Ч;
	HEFFECT  m_snd_eggbird_hurt;  
	HEFFECT  m_snd_lightbird_fly;   //�������������˵���Ч;
	HEFFECT  m_snd_lightbird_hurt;
	HEFFECT  m_snd_bombbird_fly;    //ը�����������˵���Ч;
	HEFFECT  m_snd_bombbird_hurt;
	HEFFECT  m_snd_pig_hurt;       //С��������Ч;

	//װ�����������������
	std::list<CBigMouseBird*> m_b2_bigbirds;
	std::list<CEggBird*> m_b2_eggbirds;
	std::list<CLightBird*> m_b2_lightbirds;
	std::list<CEggBird*>m_b2_bombbirds;
	//װ���е�������������
	std::list<CAnimEgg*> m_b2_eggs;
	std::list<CBombEgg*> m_b2_bombs;

	//��ĵ�������
	std::list<CBigMouseBird*>::iterator bigbird_ite;
	std::list<CEggBird*>::iterator eggbird_ite;
	std::list<CLightBird*>::iterator lightbird_ite;
	std::list<CEggBird*>::iterator bombbird_ite;

	//���ĵ�������
	std::list<CAnimEgg*>::iterator egg_ite;
	std::list<CBombEgg*>::iterator bomb_ite;


	

};

