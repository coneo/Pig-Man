#pragma once
#include "canimation.h"

class CYoungPig;

const double g_light_attack_speed = 6;
const double g_light_attack_distanc = 40;

class CLightBird :
	public CAnimation
{
public:
	CLightBird(void);

	//������Ҫ����Դ�����ݣ�
	CLightBird(HGE* _hge,                 //����
		CYoungPig* _pig,                 //С��;
		char* filename,                  //������Դ��
		Color _color,          //���������ĳ�ʼ���ꣻ
		int _weidth_tex,int _height_tex,//����Ŀ�͸�
		int _frame,                     //������֡����
		int _FPS);                     //�����Ĳ����ٶȣ�

	//�����target��positonΪͼƬ���������ꣻ
	//�����������������ꣻ
	//���е�����ж�AI�������
	void AI(Position target,          //Ŀ�����������
		int unattack_frame,           //�ǹ���״̬֡����
		int attacking_frame,           //����֡����
		int attacked_frame = 0);

	//����������Ƿ��Ŀ����ײ��
	bool IsHit();
	//����������ã�
	bool IsLayegg();
	void Check(Position target,int attacking_frame);

	virtual ~CLightBird(void);
protected:
	CYoungPig	*m_pig;             //��������ײ����ʱ��������ˣ�����Ҫ��;
	State m_state;					//��¼�������״̬��
	int m_attack_spot;				//��¼��ʼ��ʱ��һ������Ĺ���λ�ã�
	int m_speed;					//��¼��������ٶ�Ϊ����ĸ����㷨����
	bool m_ishit;                   //��¼�������Ƿ�ײ����Ŀ�ꣻ
};

