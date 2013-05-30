#include  "CAnimBrid_Run_battle.h" 

class   CAnimEggBird :public  CAnimBird_Run_battle

{
public:

  CAnimEggBird();
  CAnimEggBird(HGE *_hge);

  void  Update();
  void Render();
  void MoveFollowBgroud();
  int  GetHeight();
  int  GetWidth();

private:


};