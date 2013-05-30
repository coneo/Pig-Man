#ifndef C1_BIRD
#define C1_BIRD
#include"CObjectState.h"
#include "CBullet.h"
#include <hge.h>
#include <hgeanim.h>
class C1_bird
{
public:
	C1_bird();
	~C1_bird();             
	void    SetImage(char* fileName, int x_position, int y_position, int _width, int _height,float& _volume);
	void    Fly(); 
	float   GetPositionX() const;    //取得鸟的X坐标;
	float   GetPositionY() const;    //获取鸟的y坐标
	float   GetScale() const;
	float   GetBirdWidth()const;
	float   GetBirdHeight()const;
	float   GetBirdPull() ;
	void    SetBirdPull(int birdpull);
	void    SetScale(float scale);
    void    SetPosition(float _x, float _y);
    void    SetSpeed(float xspeed,float yspeed);
	void    SetSpeed(int weaponPull,float weaponPositionX, float weaponPositionY);
	bool    isBirdAttacked(float& bulletPositionX,float& bulletPositionY);
	ObjectState  BirdState;
	void    SetPlayMode(int mode);
	bool    edgeDetection();
	void    initialState();
	int     getScore();
protected:

		HGE *m_hge;	
		hgeAnimation* m_player;//动画；
		hgeQuad quad;
		HTEXTURE m_tex;
		int random;
		HEFFECT     birdSound;
		char* filename;
		float scale; //鸟的大小	
		float angle;//一张图片的角度，用于顺时针旋转，在fly函数中使用
		int   birdScore;
		float birdPull;    //鸟的拉力，最大值为800，方向为枪的坐标和鸟的坐标之差得出
		float birdEnergy;  //鸟的体能，与所用拉力次数大小成反比
		int   birdQuality; //鸟的质量，与鸟沿跳绳方向飞行的速度有关F=ma
		float maxBirdPull;
		float m_xposition,m_yposition;//bird x，y的位置，为图像左上角的坐标
		float x_speed,y_speed;//图像左上角x，y变换的速度
		float birdAngle;
		float width;        //控制图片的现实
		float height;
		float volume;
		float bird_position_px,bird_position_py;
		float initPositionX, initPositionY;
		float initSpeedX,initSpeedY;
};
#endif