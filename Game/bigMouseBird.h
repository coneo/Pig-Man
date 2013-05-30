#ifndef BIGMOUSEBIRD_H 
#define BIGMOUSEBIRD_H
#include <hge.h>
#include "C1_bird.h"
#include"CWeapon.h"
#include"CBullet.h"
#include "hgefont.h"
#include "hgeparticle.h"
#include <hgeanim.h>
enum birdState{FLY = 0,BECATCHED,SLIP,FORCEESCAPED};
enum pigState {DISAPPEAR,APPEAR};
class bigMouseBird : public C1_bird
{
public:
	bigMouseBird();
	bigMouseBird(HGE* hge,float initX, float initY, int score,char* musicFly,char* musicDead);
	~bigMouseBird();
	void       initPig();
	void       judgePigState();
	void       beCatched();//��ץ
	void       slip();//��������
	void       forceEscaped();//������������Ч��
	void       pigCacthBird();
	void       judgeState(CWeapon* NewWeapon,CBullet* NewBullet,int& score);
	void       catchBirdWithWeapon(CWeapon* NewWeapon,CBullet* NewBullet);
	void       setFrames(int frames);
private:
	birdState  state;
	pigState   pigstate;
	HEFFECT    sndBird[2]; //�����Ч,һ���������еģ�һ��������
	HEFFECT    sndPig;
	float bulletPositionX;
	float bulletPositionY;
	float weaponPositionX;
	float weaponPositionY;
	float pigPositionX;
	float pigPositionY;
	float birdDiePositionX;
	int   maxLinePull;
	int   birdPull;
	int   weaponPull;
	HTEXTURE      pig_tex;
	HTEXTURE      bird_tex;
	hgeAnimation* heroPig;
	hgeAnimation* dieBird;
	hgeSprite*			m_spts;  
	hgeParticleSystem*	parts[12];
	HTEXTURE            m_change;   //���
	hgeSprite*    m_sprPigDisappear;
	hgeSprite*    m_sprPigAppear;
	hgeSprite*    m_sprBirdDead;
	hgeFont	*     birdPullFnt;
	HTEXTURE      m_PigDisappear;
	HTEXTURE      m_PigAppear;
	HTEXTURE      m_birdDead;
};

#endif