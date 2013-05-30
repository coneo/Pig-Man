#pragma once
#include <hge.h>
#include <hgeanim.h>
#include"CGlobal.h"

class CAnimBird_Run_battle
{

public:

	CAnimBird_Run_battle();
	CAnimBird_Run_battle(HGE *_hge);
	~CAnimBird_Run_battle();
	void             Play();
	void             Attack();
	virtual void      Update();
	virtual void     Render();
	 virtual void     MoveFollowBgroud() =0;
	 virtual int    GetWidth()=0;
	 virtual int   GetHeight()=0;
	float            GetPositionX() const;    //ȡ�����X����;
	float            GetPositionY() const;
	void             SetPositionX(float _x);
	void             SetPositionY(float _y);
	void             LoadTexture(char*filename);
	void             SetFrame(int _fram);
	void             SetFps(int  _fps);
	void             SetSpeedX(float _xspeed);
	void             SetSpeedY(float  _yspeed);
    float            GetSpeedX();
	float            GetSpeedY();

	//x_position��y_position�ֱ��ʾҪ���ص�ͼƬ�����Ͻ�λ�ã� width��height��ʾͼƬ�Ŀ�Ⱥ͸߶�;
	void    SetImage(int nframe,int nfps, int x_positon, int y_position, int width, int height);    

protected:
	float            X_speed;
	float            Y_speed;
	HGE               *m_hge;
	int               m_fps;             //ÿ����С�����ƶ���֡
	int               m_frame;
	int               m_life;          //�������ֵ;
	float             m_xposition;     //���X����;
	float             m_yposition;     //���Y����;
	bool                 stase ;       //
	hgeAnimation      *m_fly; 

	HTEXTURE          m_tex;           //ͷ��ͼƬ;
	bool isright;
	bool isleft;

	int  Width ;
	int  Height;
};

