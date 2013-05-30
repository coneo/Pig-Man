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
	float            GetPositionX() const;    //取得猪的X坐标;
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

	//x_position，y_position分别表示要加载的图片的左上角位置， width和height表示图片的宽度和高度;
	void    SetImage(int nframe,int nfps, int x_positon, int y_position, int width, int height);    

protected:
	float            X_speed;
	float            Y_speed;
	HGE               *m_hge;
	int               m_fps;             //每秒钟小猪被绘制多少帧
	int               m_frame;
	int               m_life;          //鸟的生命值;
	float             m_xposition;     //鸟的X坐标;
	float             m_yposition;     //鸟的Y坐标;
	bool                 stase ;       //
	hgeAnimation      *m_fly; 

	HTEXTURE          m_tex;           //头像图片;
	bool isright;
	bool isleft;

	int  Width ;
	int  Height;
};

