#ifndef CBATTLE2
#define CBATTLE2
#include"C1_bird.h"
#include"CWeapon.h"
#include"CBullet.h"
#include"CStrength.h"
#include "hgefont.h"
#include "bigMouseBird.h"
#include <hgeanim.h>

const static int screenWidth   = 1024;
const static int screenHeight  = 768;
class CBattle2
{
public:
	CBattle2(HGE *_hge);
	~CBattle2();
	void    Init();        //��ս�����г�ʼ��������һЩ������Դ,����ʾ����;
	bool    Run();         //��ʼս��;
	bool    Render();
	void    Release();     //�ͷ���Դ;

private:
	void            ButterflyRun();
	void            paintBg();
	void            timeAndScore();
	void            Shooting();
	void            timeOver();
	void            resourceLoading();
	void            Rain();
    void            RenderBulletandRope();                //�������Ӻ��ӵ�
	HGE             *m_hge;
	hgeSprite       *m_sprBackground;   //���ڻ��Ʊ���ͼ;
	hgeSprite       *m_sprBg1;
	hgeSprite       *m_sprGround;  //���Ƶ���
	hgeSprite       *m_sprFlower;
	hgeSprite       *m_sprFlowerMove;
	hgeSprite       *m_sprGrass;
	hgeSprite       *m_sprTree;
	hgeSprite       *m_sprButterfly;
	hgeSprite       *m_sprDirection;
	hgeSprite       *m_sprStrength;
	HTEXTURE        m_direction;
	HTEXTURE        m_butterfly;
	HTEXTURE        m_stone;
	HTEXTURE        m_tree;
	HTEXTURE        m_flower;
	HTEXTURE        m_flowerMove;
	int             flowerFlag;
	HTEXTURE        m_grass;
	HTEXTURE        m_tex;   //����ͼ������;
	HTEXTURE        m_bg1;
	HTEXTURE        m_ground;  //����
	HTEXTURE        m_rain;   //���
	HTEXTURE        m_Strength;
	bigMouseBird    *animDragon;
	bigMouseBird    *animBirdBlue;
	CWeapon         *NewWeapon;
	CBullet         *NewBullet;
	CStrength       *NewStrength;
	float timeCount;
	int   score;
	hgeFont				*fnt;
	HEFFECT             snd[5]; //�ȼ�����������ļ�
	float butterflyLX;
	float butterflyRX;
	float butterflyY;
	float butterflyAngle;
	float volume;
	//����Ч����ʵ��
	hgeAnimation* m_goose;//������
	HTEXTURE      goose;
	float     goose_x_positon,goose_y_positon,goose_scale;
	//�������Ч��
	hgeSprite*			m_spt;  
	hgeParticleSystem*	part[64];
};
#endif