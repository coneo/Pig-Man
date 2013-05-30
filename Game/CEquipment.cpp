#include "CEquipment.h"
CEquipment::CEquipment()
{
	m_count=0;
}

CEquipment::CEquipment(HGE *_hge,float x_position,float y_position)
{
	m_hge=_hge;
	m_count=2;
	m_xposition=x_position;
	m_yposition=y_position;
}

CEquipment::~CEquipment()
{

}

void CEquipment::AddCount()
{
	m_count++;
}

void CEquipment::ReduceCount()
{
	m_count--;
}

void CEquipment::SetCount(int number)
{
	m_count=number;
}

int CEquipment::GetCount()
{
	return m_count;
}

void CEquipment::SetSpeed(float speed)
{
	m_downspeed=speed;
}

void CEquipment::Down()
{
	m_yposition=m_yposition+m_downspeed;
	m_spr->Render(m_xposition,m_yposition);
}