/****************************************************************
//该类是整个游戏的主线，对游戏的初始化（init）
//然后就开始跑hge游戏（run）
//这样之后，就进入到游戏的主菜单界面
//然后进入到选择关卡界面
//选择关卡之后，进入到游戏的玩的界面，也就是真正的开始玩游戏（play）
//在玩的过程中，游戏可以暂停（stop），当然，也可以恢复（resume）
//最后，我们可以结束游戏（exit）
*****************************************************************/

#ifndef HGE_GAME
#define HGE_GAME

#include <hge.h>
//#include "CMainMenu.h"
#include "CBattle0.h"
#include "CBattle1.h"
#include "CBattle2.h"
#include "CGlobal.h"

class CMainMenu;    //由于CGame类和下面的这几个类要相互调用，故使用类的声明;
class CChooseCard;
class CSeting;
class CHelp;
class CLoading;
class CGameOver;
class CBattleStory;

enum GameState
{
	GAME_LOADING,            //加载游戏;
	GAME_MAINMENU ,           //游戏主菜单；        
	GAME_CHOOSECARD,          //选择游戏关卡;
	GAME_SETING,              //游戏设置;
	GAME_HELP,				  //游戏帮助;
	GAME_START,               //游戏开始；
	GAME_BATTLE1,             //战场一;
	GAME_BATTLE1_STORY1,       //战场一故事1；
	GAME_BATTLE1_STORY2,       //故事2；
	GAME_BATTLE2,             //战场二;
	GAME_BATTLE2_STORY1,      //战场二故事1；
	GAME_BATTLE2_STORY2,      //故事2；
	GAME_BATTLE3,             //战场三;
	GAME_BATTLE3_STORY1,      //战场三故事1；
	GAME_BATTLE3_STORY2,       //故事二；
	GAME_PLAY,                //游戏进行中；
	GAME_OVER,                //结束游戏；
	GAME_EXIT                 //退出游戏;
};

class CGame
{
public:
	CGame();
	~CGame();
	bool         Init( bool(*frameFunc)(), bool(*renderFunc)());    // 对资源的加载；
	void         Run();                        // 开始跑HGE游戏；
	void         Play();                       // 开始玩游戏，和Run()不一样的是，这是进入战场之后;
	void         Pause();                      // 暂停游戏；
	void         Resume();                     // 继续游戏；
	bool         GameCtrl();                   // 根据游戏的状态来对游戏进行控制 -- 整个游戏核心控制;
	bool         GameRender();                 // 绘制游戏中的一切;
	void         Release();                    // 释放资源;
	HGE          *GetHGE();
    GameState    GetState() const;             //获取游戏状态; 
	void         SetGameState(GameState _state);//设置游戏状态;
private:
	HGE          *m_hge;
	GameState     m_state;   //游戏状态，根据该状态进行整个游戏的控制;

	/***************************界面****************************************/
	CLoading	  *m_loading;              //加载游戏;
	CMainMenu     *m_mainMenu;             //主菜单;
	CChooseCard   *m_chooseCard;           //选择关卡;
	CSeting		  *m_seting;               //游戏设置;
	CHelp		  *m_help;                 //游戏帮助;
	CGameOver	  *m_gameover;             //游戏结束;
	CBattleStory  *m_battlestory;          //游戏故事;
	/****************************战场****************************************/

	CBattle1      *m_battle;
	CBattle2	  *m_battle2;
	CBattle0	  *m_battle0;

	/*************************音效***************************/
	HEFFECT        m_sndbk;          //背景音乐，测试用;
	/*******************************************************/
};

#endif