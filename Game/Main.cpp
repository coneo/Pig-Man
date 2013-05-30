/*
** Haaf's Game Engine 1.8
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** hge_tut06 - Creating menus
*/


// Copy the files "menu.wav", "font1.fnt", "font1.png",
// "bg.png" and "cursor.png" from the folder "precompiled"
// to the folder with executable file. Also copy hge.dll
// and bass.dll to the same folder.


#include "hge.h"
#include "hgefont.h"
#include "hgegui.h"

#include "CGame.h"

#include <math.h>


// Pointer to the HGE interface.
// Helper classes require this to work.
//HGE *hge=0;

// Some resource handles
HEFFECT				snd;
HTEXTURE			tex;
hgeQuad				quad;

// Pointers to the HGE objects we will use
hgeGUI				*gui;
hgeFont				*fnt;
hgeSprite			*spr;

CGame              *hgeGame;

bool temp_FrameFunc();
bool temp_RenderFunc();

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	hgeGame = new CGame();

	if( !hgeGame->Init( temp_FrameFunc , temp_RenderFunc))                       
	{
		MessageBox( NULL, L"Game Init Failed!", L"Error", MB_OK );
	}


	// Let's rock now!
	hgeGame->Run();

	hgeGame->Release();

	return 0;
}


bool temp_FrameFunc()
{
	return hgeGame->GameCtrl();
}

bool temp_RenderFunc()
{
	return hgeGame->GameRender();
}