//����װ�����ߵļ�¼����ʾ��
//��С������Ϊ��Ա��������showequipment[6] ���ڼ�¼����ʾ��������
//  m_equipment[5]�������߾��飬���ڵ��ߵ����䡣m_equipment[0]Ϊ�����m_equipment[1]Ϊƨ��m_equipment[2]Ϊ����,m_equipment[3]Ϊ����,
//  m_equipment[4]ΪѪ����showequipment[5]Ϊͨ����ĸ��������� showequipment[i]�� m_equipment[i]һһ��Ӧ��


#pragma once
#include "CObjects.h"

class CEquipment:public CObjects
{
public:
	CEquipment();
	CEquipment(HGE *_hge,float x_position,float y_position);
	~CEquipment();
	void AddCount();
	void ReduceCount();
	void SetCount(int number);
	int GetCount();
	void Down();
	void SetSpeed(float speed);
private:
	int m_count;
	float m_downspeed;
};