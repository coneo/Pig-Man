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
	float                GetPositionX() const;                                         //ȡ�����X����;
	float                GetPositionY() const;                                         //��ȡ���y����
	void                 VStatic();
	void                 move();                                                       //������ײ��С������Ծ
	float                GetPigState()  const;
	void                 SetPigStatejump();
	void                 SetPigStatestatic();
private:
	HGE *m_hge;	
	hgeSprite *m_spr;
	hgeQuad quad;
	HTEXTURE m_tex;
	float m_xposition,m_yposition;                                                     //pig x��y��λ�ã�Ϊͼ�����Ͻǵ�����
	float angle;                                                                       //һ��ͼƬ�ĽǶȣ�����˳ʱ����ת����fly������ʹ��
	ObjectState  PigState;

};
#endif