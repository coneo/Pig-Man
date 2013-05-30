//ÁúÄñÍ·ÎÄ¼þ
#include "CAnimSwoopBird.h"

class CAnimDragon :public  CAnimSwoopBird
{
public:
	CAnimDragon();
	CAnimDragon(HGE *_hge);
	void Update();
	void Render();
	int  GetHeight();
	int  GetWidth();
	void MoveFollowBgroud();
	~CAnimDragon();
protected:

};