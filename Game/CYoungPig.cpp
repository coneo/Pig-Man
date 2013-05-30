#include "CYoungPig.h"
#include "CGlobal.h"

CYoungPig::CYoungPig()
{

}

CYoungPig::CYoungPig(HGE *_hge)
{
	this->m_hge  = _hge;
	this->m_life = 9;          //该猪有十条生命;
	this->m_xposition = 200;
	this->m_yposition = 570;   //初始化猪的位置;
	this->m_speed = 3.0;       //初始速度;
	this->m_direction = PRIGHT;   //初始化方向;
	this->m_color = RED;        //初始化小猪的颜色为红色;
	this->nframe = 1;          //初始化帧数;
	this->nfps   = 15;         //初始化播放频率;
	//m_run->SetMode(HGEANIM_FWD || HGEANIM_NOLOOP);   //设置播放模式为“非循环播放”;

	this->m_timeDeltaOfQuicken = 0.0;   //初始化 "急速" 时间增量;
	this->m_timeDeltaOfIgnore = 0.0;

	this->m_isInLeftWaitingPoint = m_isInRightWaitingPoint = false;

	this->m_isSharping  = false;
	this->m_isRocketing = false;
	this->m_isFarting   = false;
	this->m_isIgnoring  = false;

	this->m_isJumping = false;
	this->m_lengthOfTravled = m_xposition;

	m_fnt=new hgeFont("font1.fnt"); 

	m_showequipment[0]=new CEquipment(_hge,5,10);          //5，10表示装备的位置信息;
	m_showequipment[0]->SetImage("Rocket.png",0, 0, 66, 66);

	m_showequipment[1]=new CEquipment(_hge,85,15);      //屁
	m_showequipment[1]->SetImage("屁.png",69,220,54,49);
	m_showequipment[2]=new CEquipment(_hge,172,17);     //鞋子
	m_showequipment[2]->SetImage("鞋子.png",0 ,0 ,45, 45);
	m_showequipment[3]=new CEquipment(_hge,240,30);    //眼镜
	m_showequipment[3]->SetImage("眼镜.png",0 ,0 ,60 ,24);
	m_showequipment[4]=new CEquipment(_hge,910,20);    //血量
	m_showequipment[4]->SetImage("心形.png",0 ,0 ,35 ,35);
	m_showequipment[5]=new CEquipment(_hge, 910, 70);   //剩余鸟通过只数;
	m_showequipment[5]->SetImage("骷髅.png",0 ,0 , 35, 35); 

	m_equipment[0]=new CEquipment(_hge,-100,-100);
	m_equipment[0]->SetImage("Rocket.png",0, 0, 66, 66);
	m_equipment[1]=new CEquipment(_hge,-100,-100);
	m_equipment[1]->SetImage("屁.png",69,220,54,49);
	m_equipment[2]=new CEquipment(_hge,-100,-100);
	m_equipment[2]->SetImage("鞋子.png",0 ,0 ,45, 45);
	m_equipment[3]=new CEquipment(_hge,-100,-100);
	m_equipment[3]->SetImage("眼镜.png",0 ,0 ,60 ,24);
	m_equipment[4]=new CEquipment(_hge,-100,-100);
	m_equipment[4]->SetImage("心形.png",0 ,0 ,35 ,35);

	//////////////////////////////////////加载音效////////////////////////////////////
	m_sndgaimequ = m_hge->Effect_Load("吃装备.wav");
}

CYoungPig::~CYoungPig()
{
	delete	 []m_showequipment;
	delete   []m_equipment;
	delete    m_fnt;

	m_hge->Effect_Free(m_sndgaimequ);
}

void CYoungPig::Reset()   //重置小猪参数;
{
	for (int i=0; i<3; i++)   //重置小猪的装备数量;
	{
		m_showequipment[i]->SetCount(1);
	}
	m_showequipment[4]->SetCount(5);   //重置小猪的血量;
	this->m_xposition = 200;
	this->m_yposition = 570;   //初始化猪的位置;
	this->m_speed = 3.0;       //初始速度;
	this->m_direction = PRIGHT;   //初始化方向;
	this->m_color = RED;        //初始化小猪的颜色为红色;
	this->nframe = 1;          //初始化帧数;
	this->nfps   = 15;         //初始化播放频率;
	//m_run->SetMode(HGEANIM_FWD || HGEANIM_NOLOOP);   //设置播放模式为“非循环播放”;

	this->m_timeDeltaOfQuicken = 0.0;   //初始化 "急速" 时间增量;
	this->m_timeDeltaOfIgnore = 0.0;

	this->m_isInLeftWaitingPoint = m_isInRightWaitingPoint = false;

	this->m_isSharping  = false;
	this->m_isRocketing = false;
	this->m_isFarting   = false;
	this->m_isIgnoring  = false;

	this->m_isJumping = false;
	this->m_lengthOfTravled = m_xposition;

	//m_fnt=new hgeFont("font1.fnt"); 
}

void CYoungPig::SetSpeed(float _speed)   //设置速度;
{
	m_speed = _speed;
}

int CYoungPig::GetLife() const
{
	return m_showequipment[4]->GetCount();
}

void CYoungPig::SetLife(int _numlife)   //初始化小猪的血量;
{
	m_showequipment[4]->SetCount(_numlife);                   
}

void CYoungPig::Hurt()
{
	m_showequipment[4]->ReduceCount();
}

float deltaY = 10.0;
void CYoungPig::Jump()                    //跳;
{
	if (m_isJumping)
	{
		float nfps = m_hge->Timer_GetDelta();
		deltaY = deltaY - nfps*26;
		m_yposition -= deltaY;
		if(m_yposition>570)
		{
			m_isJumping = false;
			deltaY = 10.0;
		}
	}

}

int CYoungPig::GetTraveledLength() const
{
	return m_lengthOfTravled;
}


bool CYoungPig::IsLeftWaitingPoint()
{
	if ((m_lengthOfTravled >= LEFT_WAITING_POINT) 
		&& (m_xposition <= LEFT_WAITING_POINT + m_speed) 
		&& (m_xposition >= LEFT_WAITING_POINT))
		m_isInLeftWaitingPoint = true;
	else
		m_isInLeftWaitingPoint = false;
	return m_isInLeftWaitingPoint;

}

bool CYoungPig::IsRightWaitingPoint()
{
	if ((m_lengthOfTravled <= BK_RIGHT_POINT) 
		&& (m_xposition <= RIGHT_WAITING_POINT + m_speed + 2) 
		&& (m_xposition >= RIGHT_WAITING_POINT))
		m_isInRightWaitingPoint = true;
	else
		m_isInRightWaitingPoint = false;
	return m_isInRightWaitingPoint;
// 		return true;
// 	else
// 		return false;
}

// void CYoungPig::OutLeftWaitingPoint()
// {
// 	m_isInLeftWaitingPoint = false;
// }

void CYoungPig::SetColor(Color _color)
{
	m_color = _color;
}

Color CYoungPig::GetColor()
{
	return m_color;
}

PDirection CYoungPig::GetDirection() const
{
	return m_direction;
}

void CYoungPig::GainLife()  //加血;
{
	m_life++;
}

void CYoungPig::Quicken()
{
	m_isquicking=true;
	SetSpeed(6.0);
	m_timeDeltaOfQuicken = 0.0;
	m_showequipment[2]->ReduceCount();
}

void CYoungPig::Ignore()   //使用无视;
{
	if (m_direction == PLEFT)  //根据小猪使用“无视”之前的方向更改小猪动画;
	{
		SetImage(3, nfps , 0, 101, 69, 49);
		m_run->SetMode(HGEANIM_LOOP);
		Play();
	}
	else if (m_direction == PRIGHT)
	{
		SetImage(3, nfps , 0, 149, 69, 49);
		m_run->SetMode(HGEANIM_LOOP);
		Play();
	}
	m_isIgnoring = true;
	m_timeDeltaOfIgnore = 0.0;
	m_showequipment[3]->ReduceCount();
}

void CYoungPig::Sharp()     //使用针刺;
{
	m_isSharping = true;
}

void CYoungPig::UnSharp()
{
	m_isSharping = false;
}

void CYoungPig::Rocket()    //发射火箭;
{
	m_isRocketing = true;
}

void CYoungPig::UnRocket()
{
	m_isRocketing = false;
}

void CYoungPig::Fart()      //放屁;
{
	m_isFarting = true;
}

void CYoungPig::UnFart()
{
	m_isFarting = false;
}

void CYoungPig::CheckQuicking()
{
	m_timeDeltaOfQuicken += m_hge->Timer_GetDelta();
	if (m_timeDeltaOfQuicken >= 3)
	{
		SetSpeed(3.0);
		m_isquicking=false;
	}
}

void CYoungPig::CheckIgnoring()
{
	m_timeDeltaOfIgnore += m_hge->Timer_GetDelta();
	if (m_timeDeltaOfIgnore >= 3)  //“无视”用完，更换动画;
	{
// 		if (m_direction == PLEFT)
// 		{
// 			SetImage(3, nfps , 0, 51, 69, 51);
// 			m_run->SetMode(HGEANIM_LOOP);
// 			Play();
// 		}
// 		else if (m_direction == PRIGHT)
// 		{
// 			SetImage(3, nfps, 0, 0, 69, 51);
// 			m_run->SetMode(HGEANIM_LOOP);
// 			Play();
// 		}
		m_isIgnoring = false;
	}
}

bool CYoungPig::IsIgnoring()
{
	return m_isIgnoring;
}

bool CYoungPig::IsSharping()  //判断是否正在使用“针刺”;
{
	return m_isSharping;
}

bool CYoungPig::IsRocketing()   //判断是否正在使用“火箭”;
{
	return m_isRocketing;
}

bool CYoungPig::IsFarting()    //判断是否正在使用“放屁”;
{
	return m_isFarting;
}

//接受键盘输入，对小猪进行控制;
bool CYoungPig::Contrl()  
{
// 	switch(INPUT_KEYDOWN)
// 	{
// 	case HGEK_1:
// 		SetTextre(502,820,58,53);
// 		SetColor(1);
// 		break;
// 	}
	if (m_hge->Input_GetKeyState( HGEK_ESCAPE))
		return true;
	if (m_hge->Input_GetKeyState(HGEK_LEFT))   //小猪移动;
	{
		if (IsLeftWaitingPoint())
		{
			m_lengthOfTravled -= m_speed;
		}
		else
		{
			m_xposition  -= m_speed;
			m_lengthOfTravled -= m_speed;
		} 
			
		//保证m_lengthOfTraveld 在[0,2048]之间;
		if (m_lengthOfTravled <= 0)
		{
			m_lengthOfTravled = 0;
		}
	}
	if (m_hge->Input_GetKeyState( HGEK_RIGHT))   //控制小猪移动;
	{
		if (IsRightWaitingPoint())
		{
			m_lengthOfTravled += m_speed;
		}
		else
		{
			m_xposition  += m_speed;
			m_lengthOfTravled += m_speed;
		}

		//保证m_lengthOfTraveld 在[0,2048]之间;
		if (m_lengthOfTravled >= 2048)
		{
			m_lengthOfTravled = 2048;
		}
	}
	if (m_hge->Input_KeyDown(HGEK_SPACE)) //发射针刺;
		Sharp();                         
	if ((m_hge->Input_KeyDown( HGEK_Q)) &&(m_showequipment[0]->GetCount()>0) )   //发射火箭
		Rocket();
	if((m_hge->Input_KeyDown(HGEK_W))&&(m_showequipment[2]->GetCount()>0) && (m_isquicking==false))
		Quicken();
	if((m_hge->Input_KeyDown(HGEK_E)) && (m_showequipment[3]->GetCount()>0) && (m_isIgnoring == false))
		Ignore();
	if((m_hge->Input_KeyDown(HGEK_R))&&(m_showequipment[1]->GetCount()>0))
		Fart();
	if(m_hge->Input_GetKeyState(HGEK_UP) )
		m_isJumping = true;
	if(m_hge->Input_KeyDown(HGEK_A))    //设置小猪的颜色为红色;
	{
		SetColor(RED);
	}
	if(m_hge->Input_KeyDown(HGEK_S))   //设置小猪的颜色为绿色;
	{
		//SetTextre(497,489,74,61);
		SetColor(GREEN);
	}
	if(m_hge->Input_KeyDown(HGEK_D))   //设置小猪的颜色为蓝色;
	{
		//SetTextre(497,579,56,55);
		SetColor(BLUE);
	}

	return false;
}

//保证小猪在边界范围内活动： 进行边界检测;
void CYoungPig::CheckBoundingCollision()
{
	if (GetPositionX() < 1)
		SetPositionX(1);
	if(GetPositionX() > WIN_WIDTH - 70)
		SetPositionX(WIN_WIDTH - 70);
}

bool CYoungPig::Update()
{
	float dt = m_hge->Timer_GetDelta();
	CheckQuicking();   //检查是否使用了加速，如果是，则相应的计时;
	CheckIgnoring();
	CheckBoundingCollision();  

	m_run->Update(dt);
	if (m_isJumping)  //是否在跳：
	{
		Jump();
	}
	//ChangeStatus();


	for (int i=0;i<=4;i++)
	{
		if (m_equipment[i]->GetPositionY()>570)  //装备掉到地上;
		{
			m_equipment[i]->SetSpeed(0);

		}
	}

	//吃装备；
	for (int i=0;i<=4;i++)        
	{
		float x_eq=m_equipment[i]->GetPositionX();
		float y_eq=m_equipment[i]->GetPositionY();
		float x_pig=GetPositionX();
		float y_pig=GetPositionY();
		if((((y_pig - y_eq <= 51)&&(y_pig - y_eq >= 0))||((y_eq - y_pig >=66)&&(y_eq - y_pig <=0)))
			&& (((x_pig - x_eq <= 69)&&(x_pig - x_eq >= 0))||((x_eq - x_pig<= 66)&&(x_eq - x_pig >= 0))))
		{
			//播放吃装备声音;
			m_hge->Effect_PlayEx(m_sndgaimequ, 60, 0, 1.0, false);
			m_showequipment[i]->AddCount();
			m_equipment[i]->SetPositionX(-100);
			m_equipment[i]->SetPositionY(-100);
			m_equipment[i]->SetSpeed(0);
		}

	}

	return 	Contrl();         //键盘控制;
}

void CYoungPig::UpdateEquipmentXpo(float _battle_bk_xoffset)
{ //保证掉下的装备随背景的移动而移动;
	for(int i=0; i<=4; i++)
	{
		m_equipment[i]->SetPositionX(m_equipment[i]->GetPositionX() + _battle_bk_xoffset);
	}
}

void CYoungPig::Render()        //在此处，实现小猪动画的控制;
{ 
	if (m_hge->Input_KeyDown(HGEK_LEFT))  //播放向左移动的动画;
	{
		m_direction = PLEFT;
		if (IsIgnoring())  //使用无视时的动画;
		{
			SetImage(3, nfps , 0, 101, 69, 49);
			m_run->SetMode(HGEANIM_LOOP);
			Play();
		}
		else
		{
			SetImage(3, nfps , 0, 51, 69, 51);
			m_run->SetMode(HGEANIM_LOOP);
			Play();
		}
	}
	if (m_hge->Input_KeyDown(HGEK_RIGHT))  //播放向右的动画;
	{
		m_direction = PRIGHT;
		if (IsIgnoring())  //如果使用了无视;
		{
			SetImage(3, nfps, 0, 149, 69, 49);
			m_run->SetMode(HGEANIM_LOOP);
			Play();
		}
		else
		{
			SetImage(3, nfps, 0, 0, 69, 51);
			m_run->SetMode(HGEANIM_LOOP);
			Play();
		}
	}


// 	if (m_hge->Input_KeyUp(HGEK_LEFT/* && HGEK_RIGHT && HGEK_UP*/))/* && m_hge->Input_KeyUp(HGEK_RIGHT) && m_hge->Input_KeyUp(HGEK_UP)*/
// 	{
// 		SetImage(1, nfps , 69, 51, 69, 51);
// 		m_run->SetMode(HGEANIM_FWD | HGEANIM_NOLOOP);
// 		Play();
// 	}
// 	if (m_hge->Input_KeyUp(HGEK_RIGHT))
// 	{
// 		SetImage(1, nfps, 69, 0, 69, 51);
// 		m_run->SetMode(HGEANIM_NOLOOP);
// 		Play();
// 	}

	//绘制小猪;
	m_run->Render(m_xposition,m_yposition);   
	ShowCount();
	for (int i=0;i<=5;i++)
	{
		m_showequipment[i]->Show();
	}
	for (int i=0;i<=4;i++)
	{//保证掉下的装备的世界坐标;
		//m_equipment[i]->SetPositionX(m_equipment[i]->GetPositionX() + _battle_bk_xoffset);
		m_equipment[i]->Down();
	}



}

void CYoungPig::ShowCount()     //显示装备的个数
{
	m_fnt->printf(55,40,HGETEXT_LEFT,"%d",m_showequipment[0]->GetCount());
	m_fnt->printf(135,40,HGETEXT_LEFT,"%d",m_showequipment[1]->GetCount());
	m_fnt->printf(215,40,HGETEXT_LEFT,"%d",m_showequipment[2]->GetCount());
	m_fnt->printf(290,40,HGETEXT_LEFT,"%d",m_showequipment[3]->GetCount());
	m_fnt->printf(950,40,HGETEXT_LEFT,"%d",m_showequipment[4]->GetCount());

}

void CYoungPig::RandomDown(float x,float y)    //打到鸟后随机掉下道具
{
	int number=m_hge->Random_Int(0,4);
	if ((number<=4)&&(number>=0))
	{
		if (m_equipment[number]->GetPositionY()<0)
		{
			m_equipment[number]->SetSpeed(2);
			m_equipment[number]->SetPositionX(x);
			m_equipment[number]->SetPositionY(y);
		}
	}

}

CEquipment* CYoungPig::GetEquipment(int i)
{
	return m_showequipment[i];
}