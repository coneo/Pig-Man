#include "CAnimBrid_Run_battle.h"

class CAnimMoveDownBird: public CAnimBird_Run_battle
{

public:
	CAnimMoveDownBird();
	CAnimMoveDownBird(HGE *_hge);
	~CAnimMoveDownBird();
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
	bool flage;
	int n;
	int m;

};