#include "CPig.h"


CPig::CPig()
{
}

CPig::CPig(HGE *_hge)
{   
	m_hge = _hge;
	m_life = 1; //初始化猪的生命值;
	m_xposition = m_yposition = 20;  //猪的初始位置;
	

}

CPig::~CPig()

{
	delete m_run;
	m_hge->Texture_Free(m_tex);
}

void CPig::SetFps(float _fps)
{
	nfps = _fps;
}

void CPig::SetFrame(float _fram)
{
	/*nframe = _fram;*/
	m_run->SetFrame(_fram);
}

void CPig::SetMode(int _mode)
{
	m_run->SetMode(_mode);
}

float CPig::GetFps()
{
	return nfps;
}

float CPig::GetFrame()
{
	return nframe;
}

void CPig::LoadTexture(char* filename)
{   
	stase  = false;
	m_tex = m_hge->Texture_Load(filename);

}

void CPig::SetImage(int nframe,int nfps,int x_positon, int y_position, int width, int height)
{   
	m_run = new hgeAnimation(m_tex,nframe,nfps,x_positon,y_position,width,height);
}

float CPig::GetPositionX() const
{
	return m_xposition;
}

float CPig::GetPositionY() const
{
	return m_yposition;
}

void CPig::SetPositionX(float _x)
{
	m_xposition = _x;
}

void CPig::SetPositionY(float _y)
{
	m_yposition = _y;
}

void CPig::Play()
{
	m_run->Play();
}