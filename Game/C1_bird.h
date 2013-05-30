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
	float   GetPositionX() const;    //ȡ�����X����;
	float   GetPositionY() const;    //��ȡ���y����
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
		hgeAnimation* m_player;//������
		hgeQuad quad;
		HTEXTURE m_tex;
		int random;
		HEFFECT     birdSound;
		char* filename;
		float scale; //��Ĵ�С	
		float angle;//һ��ͼƬ�ĽǶȣ�����˳ʱ����ת����fly������ʹ��
		int   birdScore;
		float birdPull;    //������������ֵΪ800������Ϊǹ��������������֮��ó�
		float birdEnergy;  //������ܣ�����������������С�ɷ���
		int   birdQuality; //�������������������������е��ٶ��й�F=ma
		float maxBirdPull;
		float m_xposition,m_yposition;//bird x��y��λ�ã�Ϊͼ�����Ͻǵ�����
		float x_speed,y_speed;//ͼ�����Ͻ�x��y�任���ٶ�
		float birdAngle;
		float width;        //����ͼƬ����ʵ
		float height;
		float volume;
		float bird_position_px,bird_position_py;
		float initPositionX, initPositionY;
		float initSpeedX,initSpeedY;
};
#endif