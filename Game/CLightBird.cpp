#include "CLightBird.h"
#include "CYoungPig.h"


CLightBird::CLightBird(void)
{
}
CLightBird::CLightBird(HGE* _hge, 
	CYoungPig* _pig,
	char* filename, 
	Color _color, 
	int _weidth_tex,int _height_tex, 
	int _frame,int _FPS)
{
	this->m_hge = _hge;
	this->m_pig = _pig;
	this->m_color = _color;
	//	this->m_frame = _frame;
	//	this->m_FPS = _FPS;
	this->m_tex_position = Position(0,_color*_height_tex*2);
	this->m_direction = RIGHT;
	this->m_state = UNATTACK;
	/*this->m_islay = false;*/
	this->m_ishit = false;

	

	//��ʼ��������Ĺ���λ�ã�
	this->m_attack_spot = m_hge->Random_Int(100,1300);

	this->m_weidth_tex = _weidth_tex;
	this->m_height_tex = _height_tex;

	this->m_tex = m_hge->Texture_Load(filename);
	this->m_animation = new hgeAnimation(m_tex,_frame,_FPS,
		m_tex_position.x,m_tex_position.y,
		_weidth_tex,_height_tex);
}

void CLightBird::AI(Position target, 
	int unattack_frame, 
	int attacking_frame,
	int attacked_frame)
{
	//�����񵽴﹥����Χ�󣬽��п��ٸ��幥��Ŀ�ꣻ
	if (((int)this->m_screen_position.x+m_weidth_tex/2) > this->m_attack_spot
		&&this->m_state == UNATTACK)
	{
		//�仯���������Ϊ�����񹥻�״̬������
		m_animation->SetTextureRect(m_tex_position.x,m_tex_position.y+m_height_tex,
			m_weidth_tex,m_height_tex);
		//����������Ĺ���״̬������֡����
		m_animation->SetFrames(attacking_frame);

		m_animation->SetMode(HGEANIM_NOLOOP);
		//��¼������Ĺ����ٶȣ�Ϊ����ļ���������ĸ���·������
		this->m_speed = this->m_x_speed;
		//����������Ĺ���״̬Ϊ���ڹ���״̬��
		this->m_state = ATTACKING;
	}
	else if (this->m_state == ATTACKING)
	{
		//�ı�С����ٶ�Ϊ�����ٶȣ�
		this->m_speed = g_light_attack_speed;
		//�ڼ����Ҫ�õ�����ʱ����,Ϊ����ķ���ȷ������
		double deltax = target.x - this->m_screen_position.x+m_weidth_tex/2.0f;
		double deltay = target.y - this->m_screen_position.y+m_height_tex/2.0f;
		//��¼��ǰĿ����������ĽǶȣ�
		double angle ;
		//����Ŀ�������������
		double distance = sqrt((target.x-this->m_screen_position.x+m_weidth_tex/2.0f)*(target.x-this->m_screen_position.x+m_weidth_tex/2.0f)
			+(target.y-this->m_screen_position.y+m_height_tex/2.0f)*(target.y-this->m_screen_position.y+m_height_tex/2.0f));

		//ʵʱ���С����Ŀ��ĽǶȣ�
		if (deltax == 0)
		{
			angle = M_PI/2.0f;
		}
		else if (deltax>0&&deltay>10)
		{
			//this->m_direction = RIGHT;
			angle = atan(fabs(deltay/deltax));
		}
		else if (deltax<0&&deltay>10)
		{
			//this->m_direction = LEFTE;
			angle = M_PI-atan(fabs(deltay/deltax));
		}
		else if(deltax < 0&& deltay < 0)
		{
			angle = M_PI + atan(fabs(deltay/deltax));
		}
		else
			angle = 2*M_PI - atan(fabs(deltay/deltax));

		//���ݽǶ�������С����ٶȺ�С���·�ߣ�

		this->m_x_speed =  this->m_speed*cos(angle);
		this->m_y_speed =  this->m_speed*sin(angle);

		// ������������ٶ����ı�������ķ���
		if (this->m_x_speed >= 0)
		{
			this->m_direction = RIGHT;
		}
		else
			this->m_direction = LEFTE;
		//���������ʱ��ײ��Ŀ�ꣻ
		if (distance <= g_light_attack_distanc)
		{
			//С�������;
			m_pig->Hurt();
			this->m_ishit = true;
		}
		
	}

}


bool CLightBird::IsHit()
{
	return m_ishit;
}

bool CLightBird::IsLayegg()
{
	return false;
}

void CLightBird::Check(Position target,int attacking_frame)
{

}
CLightBird::~CLightBird(void)
{
	if (NULL != this->m_animation)
	{
		//��סһ��Ҫ�ͷ�������Դ��
		m_hge->Texture_Free(m_tex);
		delete this->m_animation;
		this->m_animation = NULL;
	}
}
