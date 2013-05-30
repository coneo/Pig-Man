#pragma once
#include <hge.h>

class CGUI
{
public:
	CGUI();
	//CGUI(HGE *_hge);
	~CGUI();
	virtual void Init() = 0;    //初始化界面，实现精灵的创建，纹理的加载;
	virtual void Update() = 0;  //界面的逻辑控制;
	virtual void Render() = 0;  //界面的绘制;
protected:
	HGE    *m_hge;
};

