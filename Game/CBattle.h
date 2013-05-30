#pragma once
#include "hge.h"

class CBattle
{
public:
	CBattle();
	CBattle(HGE *_hge);
	~CBattle();
	void    Init();        //对战场进行初始化，加载一些场景资源,并显示出来;
	bool    Run();         //开始战斗;
	bool    Render();      //对场景（包括背景和角色等所有可见的）进行绘制;
	void    Release();     //释放资源;
	void    SetScore(int _score);
	int     GetScore() const;
	void    UpdateBk();
protected:
	HGE            *m_hge;
};

