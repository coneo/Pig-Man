#pragma once
#include <hge.h>

class CGUI
{
public:
	CGUI();
	//CGUI(HGE *_hge);
	~CGUI();
	virtual void Init() = 0;    //��ʼ�����棬ʵ�־���Ĵ���������ļ���;
	virtual void Update() = 0;  //������߼�����;
	virtual void Render() = 0;  //����Ļ���;
protected:
	HGE    *m_hge;
};

