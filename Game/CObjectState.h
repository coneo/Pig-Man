#ifndef COBJECTSTATE
#define COBJECTSTATE
#include<math.h>
#include<hge.h>
#include<hgesprite.h>
#include<string>
#include <vector>
#include <hgeanim.h>
#include <hgeparticle.h>
enum ObjectState{adjust,shoot,                                //ǹ��״̬
	begin,MOVE,collision,                                     //�ӵ���״̬
	change,Intial,                                            //��������״̬
	jump,Static,                                               //���״̬
	appear,disappear,                                         //���ӵ�״̬  
	Initial};                                                 //���ж���ĳ�ʼ��


const double PI=3.14159265358979323846264338327950288419716;


#endif