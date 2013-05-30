#pragma once
#include "hge.h"

class CBattle
{
public:
	CBattle();
	CBattle(HGE *_hge);
	~CBattle();
	void    Init();        //��ս�����г�ʼ��������һЩ������Դ,����ʾ����;
	bool    Run();         //��ʼս��;
	bool    Render();      //�Գ��������������ͽ�ɫ�����пɼ��ģ����л���;
	void    Release();     //�ͷ���Դ;
	void    SetScore(int _score);
	int     GetScore() const;
	void    UpdateBk();
protected:
	HGE            *m_hge;
};

