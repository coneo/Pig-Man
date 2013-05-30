#pragma once
#include "canimation.h"

class CYoungPig;

//������Ĺ�����Χ����ײ���룻
const double g_bigbird_attack_distanc = 200.0f;
const double g_bigbird_collision_distance = 50.0f;



class CBigMouseBird :
	public CAnimation
{
public:
	CBigMouseBird(void);
	//������Ҫ����Դ������
	CBigMouseBird(HGE* _hge,//����
		CYoungPig*  _pig,  //С��ָ��;
		char* filename,//������Դ��
		Color _color,//���������ĳ�ʼ���ꣻ
		int _weidth_tex,int _height_tex,//����Ŀ�͸�
		int _frame,//������֡����
		int _FPS);//�����Ĳ����ٶȣ�

	//�����target��positonΪͼƬ���������ꣻ
	//���е�����ж�AI�������
	//�����������������ꣻ
	void AI(Position target,//Ŀ����������ꣻ
		int unattack_frame,//�ǹ���״̬֡����
		int attacking_frame,//��Ҫ������֡����
		int attacked_frame);//����֡����
	//���������Ƿ��Ŀ����ײ��
	bool IsHit();

	//����������ã�
	bool IsLayegg();
	void Check(Position target,int attacking_frame);
	
	virtual ~CBigMouseBird(void);
protected:
/*	bool m_isplaying;*/
	State m_state;//��¼�������״̬��

	CYoungPig    *m_pig;     //���ڵ�������ײ��С��ʱ��Ҫ��С���Ѫ������ҪС��;
};

