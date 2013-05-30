#pragma once
#include "canimation.h"

//�µ���Ĺ�����Χ��
const double g_eggbird_attack = 20.0f;


class CEggBird :
	public CAnimation
{
public:
	CEggBird(void);
	//������Ҫ����Դ������
	CEggBird(HGE* _hge,//����
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
		int attacking_frame,//����״̬֡����
		int attacked_frame = 0);

	//�ж��Ƿ��µ�����Ϊ����Ľ���ã�
	bool IsLayegg();
	//����������ã�
	bool IsHit();
	void Check(Position target,int attacking_frame);
	virtual ~CEggBird(void);
protected:
	State m_state;//��¼�µ����״̬��
};

