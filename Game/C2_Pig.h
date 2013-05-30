#ifndef C2_PIG
#define C2_PIG
#include"CObjectState.h"
class C2_Pig
{
public:
	C2_Pig();
	C2_Pig(HGE *_hge);
	~C2_Pig();             
	void                 SetImage(char* filename, int x_positon, 
		int y_position, int width, int height);    
	void                 Render(); 
	float                GetPositionX() const;                                         //取得猪的X坐标;
	float                GetPositionY() const;                                         //获取猪的y坐标
	void                 VStatic();
	void                 move();                                                       //发生碰撞后，小猪发生跳跃
	float                GetPigState()  const;
	void                 SetPigStatejump();
	void                 SetPigStatestatic();
private:
	HGE *m_hge;	
	hgeSprite *m_spr;
	hgeQuad quad;
	HTEXTURE m_tex;
	float m_xposition,m_yposition;                                                     //pig x，y的位置，为图像左上角的坐标
	float angle;                                                                       //一张图片的角度，用于顺时针旋转，在fly函数中使用
	ObjectState  PigState;

};
#endif