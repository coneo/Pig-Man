//用于装备道具的记录及显示。
//在小猪类中为成员函数，有showequipment[6] 用于记录和显示道具数量
//  m_equipment[5]创建道具精灵，用于道具的下落。m_equipment[0]为火箭，m_equipment[1]为屁，m_equipment[2]为加速,m_equipment[3]为无视,
//  m_equipment[4]为血量。showequipment[5]为通过鸟的个数。其中 showequipment[i]和 m_equipment[i]一一对应。


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