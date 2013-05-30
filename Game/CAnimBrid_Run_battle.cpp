#include "CAnimBrid_Run_battle.h"


	CAnimBird_Run_battle::CAnimBird_Run_battle()
	{

	}

	CAnimBird_Run_battle::CAnimBird_Run_battle(HGE *_hge)
	{   
		Height = 0;
		Width  = 0;
		isright = false;
		isleft  = false;
		m_hge = _hge;
		m_life = 1; //初始化鸟的生命值;
		m_xposition =1000; 
		m_yposition = 20;  //鸟的初始位置;

	}


	CAnimBird_Run_battle::~CAnimBird_Run_battle()

	{
		delete m_fly;
		m_hge->Texture_Free(m_tex);
	}



	void CAnimBird_Run_battle::LoadTexture(char* filename)
	{   
		stase  = false;
		m_tex = m_hge->Texture_Load(filename);

	}


	void CAnimBird_Run_battle::Play()
	{
		m_fly->Play();

	}

	void CAnimBird_Run_battle::SetFps(int _fps)

	{
		   m_fps = _fps;
	}
	void CAnimBird_Run_battle::SetFrame(int _fram)
	{
		m_frame = _fram;
	}
	void CAnimBird_Run_battle::SetImage(int nframe,int nfps,int x_positon, int y_position, int width, int height)
	{   

		Width = width;
		Height= height;

		m_fly = new hgeAnimation(m_tex,nframe,nfps,x_positon,y_position,width,height);
		// m_run->Play();

	}

	float CAnimBird_Run_battle::GetPositionX() const
	{
		return m_xposition;
	}

	float CAnimBird_Run_battle::GetPositionY() const
	{
		return m_yposition;
	}

	void CAnimBird_Run_battle::SetPositionX(float _x)
	{
		m_xposition = _x;
	}

	void CAnimBird_Run_battle::SetPositionY(float _y)
	{
		m_yposition = _y;
	}


	void CAnimBird_Run_battle::SetSpeedX(float _xspeed)

	{
       X_speed = _xspeed;
	}

	void CAnimBird_Run_battle::SetSpeedY(float _yspeed)
	{
		Y_speed = _yspeed;
	}

	float CAnimBird_Run_battle::GetSpeedX()
	{
		return     X_speed;
	}

	float CAnimBird_Run_battle::GetSpeedY()
	{
		return     Y_speed;
	}

	void  CAnimBird_Run_battle::Update()
	{
		
	}



	void CAnimBird_Run_battle::Render()
	{

		float dt = m_hge->Timer_GetDelta();
		//m_xposition += 1;
		m_fly->Render(m_xposition,m_yposition);
		m_fly->Update(dt);

	}