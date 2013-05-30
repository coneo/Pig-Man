#pragma once
#include "CPig.h"
#include "CEquipment.h"
#include "hgefont.h"
#include "CGlobal.h"

enum PDirection {PLEFT, PRIGHT};   //С��ķ���;

class CYoungPig : public CPig
{
public:
	CYoungPig();
	CYoungPig(HGE *_hge);
	~CYoungPig();
	void	Reset();             //С��ĳ�ʼ�����ú����Ĵ�����Ϊ����Ϸ���ã� 
	bool    Update();            //�߼�;
	void    UpdateEquipmentXpo(float _battle_bk_xoffset);  //���µ���װ����X���꣬��֤��X����;
	void    Render();     //����ս���ı���ƫ��������;
	void    SetSpeed(float _speed);      //�����ٶ�;
	int     GetLife() const;             //��ȡ����ֵ;
	void    GainLife();      //���һ������;
	void    SetLife(int _numlife);   //��������ֵ;
	void    Hurt();       //С�����ˣ���Ѫ;
	void    Jump();          //����;
	bool    Contrl();        //������ҵĿ���;
	void    CheckBoundingCollision(); //����Ƿ񳬳��߽�;
	void    ChangeStatus();  //����С���״̬;

	bool    IsLeftWaitingPoint();      //�Ƿ�������ĵȴ���;
	bool    IsRightWaitingPoint();     //�Ƿ�������ĵȴ���;
// 	void    OutLeftWaitingPoint();     //�뿪��ߵĵȴ���;
// 	void    OutRightWaitingPoint();    //�뿪�ұߵĵȴ���;
	int     GetTraveledLength() const;

	void    SetColor(Color _color);      //����С����ɫ��
	Color   GetColor();

	PDirection GetDirection() const;   //��ȡС����;

	void    Sharp();         //���;
	void    Rocket();        //������;
	void    Fart();          //��ƨ;
	void    Quicken();       //����;
	void    Ignore();        //����;

	void    UnSharp();         //ʹ���� ���;
	void    UnRocket();        //ʹ���� ������;
	void    UnFart();          //ʹ���� ��ƨ;

	//void    UnQuicken();       //ʹ���� ����;
	//void    UnIgnore();        //ʹ���� ����;

	void    CheckQuicking();      //����Ƿ�ʹ���� �����١�;
	void    CheckIgnoring();      //����Ƿ�ʹ���� �����ӡ�;

	bool    IsIgnoring();
	bool    IsSharping();        //�ж��Ƿ�ʹ�����;
	bool    IsRocketing();       //�ж��Ƿ����˻��;
	bool    IsFarting();         //�ж��Ƿ��ƨ;

	//void Move();
	void    RandomDown(float x,float y);   //��������ĸ�װ��������λ����Ϣ
	void    ShowCount();

	CEquipment *GetEquipment(int i);

private:
	Color     m_color;              //��Ӧ������ɫ(R,G,B)�����ں���ƥ��;
	PDirection m_direction;        //С��ķ���;

	float   m_speed;              //�ٶ�;
	float   m_timeDeltaOfQuicken;   //���ٵ�ʱ������;
	float   m_timeDeltaOfIgnore;

	bool    m_isInRightWaitingPoint;  //�Ƿ�������ȴ��㼯֮��(���Ƿ񳡾��������ƶ�);
	bool    m_isInLeftWaitingPoint;

	bool    m_isRocketing;        //�Ƿ����ڷ�����;
	bool    m_isSharping;         //�Ƿ�����ʹ�����;
	bool    m_isFarting;          //�Ƿ�����ʹ��ƨ;
	bool    m_isIgnoring;         //�Ƿ�����ʹ�á����ӡ�;
	bool    m_isquicking;

	int     m_lengthOfTravled;    //С���Ѿ����˶��پ���;
	bool    m_isJumping;          //С���Ƿ�����;

	CEquipment     *m_showequipment[6];    //������ʾ6����Ʒ�����,ƨ�����٣����ӣ�Ѫ������ͨ��������;
	CEquipment     *m_equipment[5];        //���ڴ������µ���Ʒ
	hgeFont		   *m_fnt;
	bool            m_israndom;

	////////////////////////////////////////////��Ч//////////////////////////////
	HEFFECT		m_sndgaimequ;    //��װ��������;
};

