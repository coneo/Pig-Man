/****************************************************************
//������������Ϸ�����ߣ�����Ϸ�ĳ�ʼ����init��
//Ȼ��Ϳ�ʼ��hge��Ϸ��run��
//����֮�󣬾ͽ��뵽��Ϸ�����˵�����
//Ȼ����뵽ѡ��ؿ�����
//ѡ��ؿ�֮�󣬽��뵽��Ϸ����Ľ��棬Ҳ���������Ŀ�ʼ����Ϸ��play��
//����Ĺ����У���Ϸ������ͣ��stop������Ȼ��Ҳ���Իָ���resume��
//������ǿ��Խ�����Ϸ��exit��
*****************************************************************/

#ifndef HGE_GAME
#define HGE_GAME

#include <hge.h>
//#include "CMainMenu.h"
#include "CBattle0.h"
#include "CBattle1.h"
#include "CBattle2.h"
#include "CGlobal.h"

class CMainMenu;    //����CGame���������⼸����Ҫ�໥���ã���ʹ���������;
class CChooseCard;
class CSeting;
class CHelp;
class CLoading;
class CGameOver;
class CBattleStory;

enum GameState
{
	GAME_LOADING,            //������Ϸ;
	GAME_MAINMENU ,           //��Ϸ���˵���        
	GAME_CHOOSECARD,          //ѡ����Ϸ�ؿ�;
	GAME_SETING,              //��Ϸ����;
	GAME_HELP,				  //��Ϸ����;
	GAME_START,               //��Ϸ��ʼ��
	GAME_BATTLE1,             //ս��һ;
	GAME_BATTLE1_STORY1,       //ս��һ����1��
	GAME_BATTLE1_STORY2,       //����2��
	GAME_BATTLE2,             //ս����;
	GAME_BATTLE2_STORY1,      //ս��������1��
	GAME_BATTLE2_STORY2,      //����2��
	GAME_BATTLE3,             //ս����;
	GAME_BATTLE3_STORY1,      //ս��������1��
	GAME_BATTLE3_STORY2,       //���¶���
	GAME_PLAY,                //��Ϸ�����У�
	GAME_OVER,                //������Ϸ��
	GAME_EXIT                 //�˳���Ϸ;
};

class CGame
{
public:
	CGame();
	~CGame();
	bool         Init( bool(*frameFunc)(), bool(*renderFunc)());    // ����Դ�ļ��أ�
	void         Run();                        // ��ʼ��HGE��Ϸ��
	void         Play();                       // ��ʼ����Ϸ����Run()��һ�����ǣ����ǽ���ս��֮��;
	void         Pause();                      // ��ͣ��Ϸ��
	void         Resume();                     // ������Ϸ��
	bool         GameCtrl();                   // ������Ϸ��״̬������Ϸ���п��� -- ������Ϸ���Ŀ���;
	bool         GameRender();                 // ������Ϸ�е�һ��;
	void         Release();                    // �ͷ���Դ;
	HGE          *GetHGE();
    GameState    GetState() const;             //��ȡ��Ϸ״̬; 
	void         SetGameState(GameState _state);//������Ϸ״̬;
private:
	HGE          *m_hge;
	GameState     m_state;   //��Ϸ״̬�����ݸ�״̬����������Ϸ�Ŀ���;

	/***************************����****************************************/
	CLoading	  *m_loading;              //������Ϸ;
	CMainMenu     *m_mainMenu;             //���˵�;
	CChooseCard   *m_chooseCard;           //ѡ��ؿ�;
	CSeting		  *m_seting;               //��Ϸ����;
	CHelp		  *m_help;                 //��Ϸ����;
	CGameOver	  *m_gameover;             //��Ϸ����;
	CBattleStory  *m_battlestory;          //��Ϸ����;
	/****************************ս��****************************************/

	CBattle1      *m_battle;
	CBattle2	  *m_battle2;
	CBattle0	  *m_battle0;

	/*************************��Ч***************************/
	HEFFECT        m_sndbk;          //�������֣�������;
	/*******************************************************/
};

#endif