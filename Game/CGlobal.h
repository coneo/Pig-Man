#ifndef GLOBAL_
#define GLOBAL_

// const int WIN_WIDTH = GetSystemMetrics(SM_CXSCREEN);//*0.768;    //���ڵĿ��;
// const int WIN_HEIGHT = GetSystemMetrics(SM_CYSCREEN);//*0.9;     //���ڵĸ߶�;
const int WIN_WIDTH = 1024;    //���ڵĿ��;
const int WIN_HEIGHT = 768;     //���ڵĸ߶�;

const  int  LEFT_WAITING_POINT  = 300;                           //С�������ƶ�ʱ�ı���ͼ��ʼ�����ƶ����ٽ�㣻
const  int  RIGHT_WAITING_POINT = WIN_WIDTH - 300;                //С�������ƶ�ʱ�ı���ͼ��ʼ�����ƶ����ٽ��;
const  int  BK_RIGHT_POINT = 2048 - WIN_WIDTH + RIGHT_WAITING_POINT; //����ͼ�ƶ����ұߵ��ٽ�㣬���ڱ���ͼ�Ǵ�0��ʼ����ֻ��BK_RIGHT_POINT;
const  int  Y_ROCKET = 580;       //�������ʱ��Y����;
//const  int  BK_RIGHT_POINT = 2048 - RIGHT_WAITING_POINT;

const  int  LENGTH_OF_PIG = 69;    //С��ĳ���;

enum Color{RED,GREEN,BLUE};

#endif