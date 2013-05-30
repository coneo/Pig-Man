#include "CAnimBrid_Run_battle.h"

class CAnimSwoopBird: public CAnimBird_Run_battle
{

public:
	CAnimSwoopBird();
	CAnimSwoopBird(HGE *_hge);
    ~CAnimSwoopBird();
	void  Update();
	void  Render();
	int   GetHeight();
	int   GetWidth();
	void  MoveFollowBgroud();
	void   SetStase();
	bool  getStase();

protected:
	float dt1;
	float dt2;
	bool view;
	int n;
	int m;

	HEFFECT       sndbomb;
};