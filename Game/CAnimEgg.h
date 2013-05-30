#pragma once
#include "canimation.h"

class CYoungPig;

//���Ĺ�����Χ��
const int g_egg_attack_distace = 20;
//����λ�õ�Y����
const int g_y_ground = 630;


class CAnimEgg :
	public CAnimation
{
public:
	CAnimEgg(void);

	//������Ҫ����Դ������
	CAnimEgg(HGE* _hge,//����
		CYoungPig* _pig,  //С��;
		char* filename,//������Դ��
		Position _tex_position,//���������ĳ�ʼ���ꣻ
		int _weidth_tex,int _height_tex,//����Ŀ�͸�
		int _frame,//������֡����
		int _FPS);//�����Ĳ����ٶȣ�

	//�����target��positonΪͼƬ���������ꣻ
	//�����������������ꣻ
	//��ͣ�ؼ�⵰��Ŀ���λ�ù�ϵ��
	void Check(Position target,int attacking_frame);

	//����״̬���ǹ�����ײ�����棬����Ŀ��󣩣�
	State GetState();

	//��⵰�Ƿ�����Ŀ����ߵ����Ƿ���ײ��
	bool IsHit();

	//����������ã�
	bool IsLayegg();
	void AI(Position target, int unattack_frame, int attacking_frame, int attacked_frame);
	

	virtual ~CAnimEgg(void);
protected:
	CYoungPig* m_pig;   //������С����ײʱ��С������ˣ�����ҪС��;
	bool m_ishit;//��¼��ʱ��ײ�����壻

	State m_state;//��¼����״̬
};

