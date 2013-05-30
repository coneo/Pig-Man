#pragma once
#include "CGUI.h"
#include "CGUIItem.h"

class CGame;

class CBattleStory : public CGUI
{
public:
	CBattleStory(HGE *_hge, CGame *_game);
	~CBattleStory();
	void  Init();      //��ʼ��;
	void  Update();    //���£�
	void  Render();    //���ƣ�
private:
	CBattleStory();
	CGame      *m_cgame;

	CGUIItem   *m_battle1_story1;  //ս��һ�Ĺ���1��
	CGUIItem   *m_battle1_story2;  //ս�����Ĺ���2��

	CGUIItem   *m_battle2_story1;  //ս�����Ĺ���1��
	CGUIItem   *m_battle2_story2;  //ս�����Ĺ���2��

	CGUIItem   *m_battle3_story1;  //ս�����Ĺ���1��
	CGUIItem   *m_battle3_story2;  //ս�����Ĺ���2��

	float       m_timeDelta;      //ʱ��ƫ���������ڱ�֤�������������ת�Ž�����Ϸ��
};

