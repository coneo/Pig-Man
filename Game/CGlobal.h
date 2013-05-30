#ifndef GLOBAL_
#define GLOBAL_

// const int WIN_WIDTH = GetSystemMetrics(SM_CXSCREEN);//*0.768;    //窗口的宽度;
// const int WIN_HEIGHT = GetSystemMetrics(SM_CYSCREEN);//*0.9;     //窗口的高度;
const int WIN_WIDTH = 1024;    //窗口的宽度;
const int WIN_HEIGHT = 768;     //窗口的高度;

const  int  LEFT_WAITING_POINT  = 300;                           //小猪向左移动时的背景图开始向右移动的临界点；
const  int  RIGHT_WAITING_POINT = WIN_WIDTH - 300;                //小猪向右移动时的背景图开始向右移动的临界点;
const  int  BK_RIGHT_POINT = 2048 - WIN_WIDTH + RIGHT_WAITING_POINT; //背景图移动到右边的临界点，由于背景图是从0开始，故只有BK_RIGHT_POINT;
const  int  Y_ROCKET = 580;       //火箭发射时的Y坐标;
//const  int  BK_RIGHT_POINT = 2048 - RIGHT_WAITING_POINT;

const  int  LENGTH_OF_PIG = 69;    //小猪的长度;

enum Color{RED,GREEN,BLUE};

#endif