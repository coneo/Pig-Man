#pragma once
#include <hge.h>
#include <hgesprite.h>
#include "hgeanim.h"
class CPig
{

public:

	CPig();
	CPig(HGE *_hge);
	~CPig();
	//x_position，y_position分别表示要加载的图片的左上角位置， width和height表示图片的宽度和高度;
    void    LoadTexture(char*filename);
	void    SetImage(int nframe,int nfps, int x_positon, int y_position, int width, int height);    //设置鸟的头像;
	
	float   GetPositionX() const;    //取得猪的X坐标;
	float   GetPositionY() const;
	void    SetPositionX(float _x);
	void    SetPositionY(float _y);

	//int     GetLife() const;         //获取猪的生命值;
	void    SetFps(float _fps);        //设置播放频率;
	void    SetFrame(float _fram);     //设置播放的帧;
	void    SetMode(int _mode);        //设置动画的播放模式;
	void    Play();
	void    Attack();

	virtual bool   Update() = 0;          //更新;
	virtual void   Render() = 0;          //绘制;

	float   GetFps();
	float   GetFrame();

protected:

	int               nfps;             //每秒钟小猪被绘制多少帧
	int               nframe;

	int               m_life;          //猪的生命值;
	float             m_xposition;     //猪的X坐标;
	float             m_yposition;     //猪的Y坐标;
     bool                 stase ;

	HGE               *m_hge;
	//hgeSprite         *m_spr;
	hgeAnimation      *m_run; 
	//hgeAnimation      *m_stand;  
	//hgeAnimation      *m_standlift;  
	//hgeAnimation      *m_jumprigt;
//	hgeAnimation        *m_jumprigt;

	HTEXTURE           m_tex;           //头像图片;

	
   //HTEXTURE           Texm_run; 
};

