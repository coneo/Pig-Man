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
	//x_position��y_position�ֱ��ʾҪ���ص�ͼƬ�����Ͻ�λ�ã� width��height��ʾͼƬ�Ŀ�Ⱥ͸߶�;
    void    LoadTexture(char*filename);
	void    SetImage(int nframe,int nfps, int x_positon, int y_position, int width, int height);    //�������ͷ��;
	
	float   GetPositionX() const;    //ȡ�����X����;
	float   GetPositionY() const;
	void    SetPositionX(float _x);
	void    SetPositionY(float _y);

	//int     GetLife() const;         //��ȡ�������ֵ;
	void    SetFps(float _fps);        //���ò���Ƶ��;
	void    SetFrame(float _fram);     //���ò��ŵ�֡;
	void    SetMode(int _mode);        //���ö����Ĳ���ģʽ;
	void    Play();
	void    Attack();

	virtual bool   Update() = 0;          //����;
	virtual void   Render() = 0;          //����;

	float   GetFps();
	float   GetFrame();

protected:

	int               nfps;             //ÿ����С�����ƶ���֡
	int               nframe;

	int               m_life;          //�������ֵ;
	float             m_xposition;     //���X����;
	float             m_yposition;     //���Y����;
     bool                 stase ;

	HGE               *m_hge;
	//hgeSprite         *m_spr;
	hgeAnimation      *m_run; 
	//hgeAnimation      *m_stand;  
	//hgeAnimation      *m_standlift;  
	//hgeAnimation      *m_jumprigt;
//	hgeAnimation        *m_jumprigt;

	HTEXTURE           m_tex;           //ͷ��ͼƬ;

	
   //HTEXTURE           Texm_run; 
};

