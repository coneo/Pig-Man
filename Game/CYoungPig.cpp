#include "CYoungPig.h"
#include "CGlobal.h"

CYoungPig::CYoungPig()
{

}

CYoungPig::CYoungPig(HGE *_hge)
{
	this->m_hge  = _hge;
	this->m_life = 9;          //������ʮ������;
	this->m_xposition = 200;
	this->m_yposition = 570;   //��ʼ�����λ��;
	this->m_speed = 3.0;       //��ʼ�ٶ�;
	this->m_direction = PRIGHT;   //��ʼ������;
	this->m_color = RED;        //��ʼ��С�����ɫΪ��ɫ;
	this->nframe = 1;          //��ʼ��֡��;
	this->nfps   = 15;         //��ʼ������Ƶ��;
	//m_run->SetMode(HGEANIM_FWD || HGEANIM_NOLOOP);   //���ò���ģʽΪ����ѭ�����š�;

	this->m_timeDeltaOfQuicken = 0.0;   //��ʼ�� "����" ʱ������;
	this->m_timeDeltaOfIgnore = 0.0;

	this->m_isInLeftWaitingPoint = m_isInRightWaitingPoint = false;

	this->m_isSharping  = false;
	this->m_isRocketing = false;
	this->m_isFarting   = false;
	this->m_isIgnoring  = false;

	this->m_isJumping = false;
	this->m_lengthOfTravled = m_xposition;

	m_fnt=new hgeFont("font1.fnt"); 

	m_showequipment[0]=new CEquipment(_hge,5,10);          //5��10��ʾװ����λ����Ϣ;
	m_showequipment[0]->SetImage("Rocket.png",0, 0, 66, 66);

	m_showequipment[1]=new CEquipment(_hge,85,15);      //ƨ
	m_showequipment[1]->SetImage("ƨ.png",69,220,54,49);
	m_showequipment[2]=new CEquipment(_hge,172,17);     //Ь��
	m_showequipment[2]->SetImage("Ь��.png",0 ,0 ,45, 45);
	m_showequipment[3]=new CEquipment(_hge,240,30);    //�۾�
	m_showequipment[3]->SetImage("�۾�.png",0 ,0 ,60 ,24);
	m_showequipment[4]=new CEquipment(_hge,910,20);    //Ѫ��
	m_showequipment[4]->SetImage("����.png",0 ,0 ,35 ,35);
	m_showequipment[5]=new CEquipment(_hge, 910, 70);   //ʣ����ͨ��ֻ��;
	m_showequipment[5]->SetImage("����.png",0 ,0 , 35, 35); 

	m_equipment[0]=new CEquipment(_hge,-100,-100);
	m_equipment[0]->SetImage("Rocket.png",0, 0, 66, 66);
	m_equipment[1]=new CEquipment(_hge,-100,-100);
	m_equipment[1]->SetImage("ƨ.png",69,220,54,49);
	m_equipment[2]=new CEquipment(_hge,-100,-100);
	m_equipment[2]->SetImage("Ь��.png",0 ,0 ,45, 45);
	m_equipment[3]=new CEquipment(_hge,-100,-100);
	m_equipment[3]->SetImage("�۾�.png",0 ,0 ,60 ,24);
	m_equipment[4]=new CEquipment(_hge,-100,-100);
	m_equipment[4]->SetImage("����.png",0 ,0 ,35 ,35);

	//////////////////////////////////////������Ч////////////////////////////////////
	m_sndgaimequ = m_hge->Effect_Load("��װ��.wav");
}

CYoungPig::~CYoungPig()
{
	delete	 []m_showequipment;
	delete   []m_equipment;
	delete    m_fnt;

	m_hge->Effect_Free(m_sndgaimequ);
}

void CYoungPig::Reset()   //����С�����;
{
	for (int i=0; i<3; i++)   //����С���װ������;
	{
		m_showequipment[i]->SetCount(1);
	}
	m_showequipment[4]->SetCount(5);   //����С���Ѫ��;
	this->m_xposition = 200;
	this->m_yposition = 570;   //��ʼ�����λ��;
	this->m_speed = 3.0;       //��ʼ�ٶ�;
	this->m_direction = PRIGHT;   //��ʼ������;
	this->m_color = RED;        //��ʼ��С�����ɫΪ��ɫ;
	this->nframe = 1;          //��ʼ��֡��;
	this->nfps   = 15;         //��ʼ������Ƶ��;
	//m_run->SetMode(HGEANIM_FWD || HGEANIM_NOLOOP);   //���ò���ģʽΪ����ѭ�����š�;

	this->m_timeDeltaOfQuicken = 0.0;   //��ʼ�� "����" ʱ������;
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

void CYoungPig::SetSpeed(float _speed)   //�����ٶ�;
{
	m_speed = _speed;
}

int CYoungPig::GetLife() const
{
	return m_showequipment[4]->GetCount();
}

void CYoungPig::SetLife(int _numlife)   //��ʼ��С���Ѫ��;
{
	m_showequipment[4]->SetCount(_numlife);                   
}

void CYoungPig::Hurt()
{
	m_showequipment[4]->ReduceCount();
}

float deltaY = 10.0;
void CYoungPig::Jump()                    //��;
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

void CYoungPig::GainLife()  //��Ѫ;
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

void CYoungPig::Ignore()   //ʹ������;
{
	if (m_direction == PLEFT)  //����С��ʹ�á����ӡ�֮ǰ�ķ������С����;
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

void CYoungPig::Sharp()     //ʹ�����;
{
	m_isSharping = true;
}

void CYoungPig::UnSharp()
{
	m_isSharping = false;
}

void CYoungPig::Rocket()    //������;
{
	m_isRocketing = true;
}

void CYoungPig::UnRocket()
{
	m_isRocketing = false;
}

void CYoungPig::Fart()      //��ƨ;
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
	if (m_timeDeltaOfIgnore >= 3)  //�����ӡ����꣬��������;
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

bool CYoungPig::IsSharping()  //�ж��Ƿ�����ʹ�á���̡�;
{
	return m_isSharping;
}

bool CYoungPig::IsRocketing()   //�ж��Ƿ�����ʹ�á������;
{
	return m_isRocketing;
}

bool CYoungPig::IsFarting()    //�ж��Ƿ�����ʹ�á���ƨ��;
{
	return m_isFarting;
}

//���ܼ������룬��С����п���;
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
	if (m_hge->Input_GetKeyState(HGEK_LEFT))   //С���ƶ�;
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
			
		//��֤m_lengthOfTraveld ��[0,2048]֮��;
		if (m_lengthOfTravled <= 0)
		{
			m_lengthOfTravled = 0;
		}
	}
	if (m_hge->Input_GetKeyState( HGEK_RIGHT))   //����С���ƶ�;
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

		//��֤m_lengthOfTraveld ��[0,2048]֮��;
		if (m_lengthOfTravled >= 2048)
		{
			m_lengthOfTravled = 2048;
		}
	}
	if (m_hge->Input_KeyDown(HGEK_SPACE)) //�������;
		Sharp();                         
	if ((m_hge->Input_KeyDown( HGEK_Q)) &&(m_showequipment[0]->GetCount()>0) )   //������
		Rocket();
	if((m_hge->Input_KeyDown(HGEK_W))&&(m_showequipment[2]->GetCount()>0) && (m_isquicking==false))
		Quicken();
	if((m_hge->Input_KeyDown(HGEK_E)) && (m_showequipment[3]->GetCount()>0) && (m_isIgnoring == false))
		Ignore();
	if((m_hge->Input_KeyDown(HGEK_R))&&(m_showequipment[1]->GetCount()>0))
		Fart();
	if(m_hge->Input_GetKeyState(HGEK_UP) )
		m_isJumping = true;
	if(m_hge->Input_KeyDown(HGEK_A))    //����С�����ɫΪ��ɫ;
	{
		SetColor(RED);
	}
	if(m_hge->Input_KeyDown(HGEK_S))   //����С�����ɫΪ��ɫ;
	{
		//SetTextre(497,489,74,61);
		SetColor(GREEN);
	}
	if(m_hge->Input_KeyDown(HGEK_D))   //����С�����ɫΪ��ɫ;
	{
		//SetTextre(497,579,56,55);
		SetColor(BLUE);
	}

	return false;
}

//��֤С���ڱ߽緶Χ�ڻ�� ���б߽���;
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
	CheckQuicking();   //����Ƿ�ʹ���˼��٣�����ǣ�����Ӧ�ļ�ʱ;
	CheckIgnoring();
	CheckBoundingCollision();  

	m_run->Update(dt);
	if (m_isJumping)  //�Ƿ�������
	{
		Jump();
	}
	//ChangeStatus();


	for (int i=0;i<=4;i++)
	{
		if (m_equipment[i]->GetPositionY()>570)  //װ����������;
		{
			m_equipment[i]->SetSpeed(0);

		}
	}

	//��װ����
	for (int i=0;i<=4;i++)        
	{
		float x_eq=m_equipment[i]->GetPositionX();
		float y_eq=m_equipment[i]->GetPositionY();
		float x_pig=GetPositionX();
		float y_pig=GetPositionY();
		if((((y_pig - y_eq <= 51)&&(y_pig - y_eq >= 0))||((y_eq - y_pig >=66)&&(y_eq - y_pig <=0)))
			&& (((x_pig - x_eq <= 69)&&(x_pig - x_eq >= 0))||((x_eq - x_pig<= 66)&&(x_eq - x_pig >= 0))))
		{
			//���ų�װ������;
			m_hge->Effect_PlayEx(m_sndgaimequ, 60, 0, 1.0, false);
			m_showequipment[i]->AddCount();
			m_equipment[i]->SetPositionX(-100);
			m_equipment[i]->SetPositionY(-100);
			m_equipment[i]->SetSpeed(0);
		}

	}

	return 	Contrl();         //���̿���;
}

void CYoungPig::UpdateEquipmentXpo(float _battle_bk_xoffset)
{ //��֤���µ�װ���汳�����ƶ����ƶ�;
	for(int i=0; i<=4; i++)
	{
		m_equipment[i]->SetPositionX(m_equipment[i]->GetPositionX() + _battle_bk_xoffset);
	}
}

void CYoungPig::Render()        //�ڴ˴���ʵ��С�����Ŀ���;
{ 
	if (m_hge->Input_KeyDown(HGEK_LEFT))  //���������ƶ��Ķ���;
	{
		m_direction = PLEFT;
		if (IsIgnoring())  //ʹ������ʱ�Ķ���;
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
	if (m_hge->Input_KeyDown(HGEK_RIGHT))  //�������ҵĶ���;
	{
		m_direction = PRIGHT;
		if (IsIgnoring())  //���ʹ��������;
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

	//����С��;
	m_run->Render(m_xposition,m_yposition);   
	ShowCount();
	for (int i=0;i<=5;i++)
	{
		m_showequipment[i]->Show();
	}
	for (int i=0;i<=4;i++)
	{//��֤���µ�װ������������;
		//m_equipment[i]->SetPositionX(m_equipment[i]->GetPositionX() + _battle_bk_xoffset);
		m_equipment[i]->Down();
	}



}

void CYoungPig::ShowCount()     //��ʾװ���ĸ���
{
	m_fnt->printf(55,40,HGETEXT_LEFT,"%d",m_showequipment[0]->GetCount());
	m_fnt->printf(135,40,HGETEXT_LEFT,"%d",m_showequipment[1]->GetCount());
	m_fnt->printf(215,40,HGETEXT_LEFT,"%d",m_showequipment[2]->GetCount());
	m_fnt->printf(290,40,HGETEXT_LEFT,"%d",m_showequipment[3]->GetCount());
	m_fnt->printf(950,40,HGETEXT_LEFT,"%d",m_showequipment[4]->GetCount());

}

void CYoungPig::RandomDown(float x,float y)    //�����������µ���
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