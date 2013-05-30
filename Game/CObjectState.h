#ifndef COBJECTSTATE
#define COBJECTSTATE
#include<math.h>
#include<hge.h>
#include<hgesprite.h>
#include<string>
#include <vector>
#include <hgeanim.h>
#include <hgeparticle.h>
enum ObjectState{adjust,shoot,                                //枪的状态
	begin,MOVE,collision,                                     //子弹的状态
	change,Intial,                                            //力度条的状态
	jump,Static,                                               //猪的状态
	appear,disappear,                                         //绳子的状态  
	Initial};                                                 //所有对象的初始化


const double PI=3.14159265358979323846264338327950288419716;


#endif