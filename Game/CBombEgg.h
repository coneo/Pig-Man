#pragma once
#include "canimation.h"

class CYoungPig;

//���Ĺ�����Χ��
const double g_bombegg_attack_distance = 20;
//ը���Ĺ�����Χ��
const double g_bomb_attack_distance = 100;
//����λ�ã�
const double g_y_round = 570;


class CBombEgg :
	public CAnimation
{
public:
	CBombEgg(void);
	//������Ҫ����Դ������
	CBombEgg(HGE* _hge,//����
		CYoungPig* _pig, //С��;
		char* filename,//������Դ��
		Position _tex_position,//���������ĳ�ʼ���ꣻ
		int _weidth_tex,int _height_tex,//����Ŀ�͸�
		int _frame,//������֡����
		int _FPS);//�����Ĳ����ٶȣ�

	//�����target��positonΪͼƬ���������ꣻ
	//�����������������ꣻ
	//���е�����ж�AI�������
	void Check(Position target,int attacking_frame);

	//���ը�����Ƿ��Ŀ����ײ��
	bool IsHit();

	//����������ã�
	bool IsLayegg();
	State GetState();
	void AI(Position target, int unattack_frame, int attacking_frame, int attacked_frame);

	virtual ~CBombEgg(void);
protected:
	CYoungPig* m_pig;  //ը����С����ײʱ��С�����Ѫ;
	bool m_ishit; //��¼��ʱ��ײ�����壻
	State m_state;//��¼����״̬
};

