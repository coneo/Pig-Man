#include "CEggBird.h"


CEggBird::CEggBird(void)
{

}
CEggBird::CEggBird(HGE* _hge,
	char* filename,
	Color _color,
	int _weidth_tex,int _height_tex,
	int _frame,int _FPS)
{
	this->m_hge = _hge;
	this->m_color = _color;
	this->m_tex_position = Position(0,_color*_height_tex*2);
	this->m_direction = RIGHT;
	this->m_state = UNATTACK;

	this->m_weidth_tex = _weidth_tex;
	this->m_height_tex = _height_tex;

	this->m_tex = m_hge->Texture_Load(filename);
	this->m_animation = new hgeAnimation(m_tex,_frame,_FPS,
		m_tex_position.x,m_tex_position.y,
		_weidth_tex,_height_tex);
}
void CEggBird::AI(Position target, 
	int unattack_frame, 
	int attacking_frame,
	int attcked_frame)
{
	double temp = abs(target.x-this->m_screen_position.x+m_weidth_tex/2.0f);
	//�µ�����빥����Χ ���ߴ��ڹ���״̬ʱ��
	if (temp <= g_eggbird_attack||this->m_state == ATTACKING)
	{
		//���µ����ڹ�����Χ��ʱ�������ڹ���״̬ʱ��׼���µ���
		if ((this->m_state ==  UNATTACK||this->m_state == ATTACKED))
		{
			//�ı��µ����״̬Ϊ���ڹ���״̬��
			this->m_state = ATTACKING;
			this->m_animation->SetMode(HGEANIM_NOLOOP);
			//�����Ĵ��ڲ���״̬��
			this->m_animation->Resume();
			//�仯���������Ϊ�µ��񹥻�״̬������
			this->m_animation->SetTextureRect(this->m_tex_position.x,
				this->m_tex_position.y+this->m_height_tex,
				this->m_weidth_tex,
				this->m_height_tex);
			//�����µ���Ĺ���״̬������֡����
			this->m_animation->SetFrames(attacking_frame);
		
			if((this->m_screen_position.x+m_weidth_tex/2.0f) <= target.x)
			{
				this->m_direction = RIGHT;
			}
			else
			{
				this->m_direction = LEFTE;
			}
		}
		//���ڹ�����Χ�ڣ�
		else if (this->m_state == ATTACKING
			&&!this->m_animation->IsPlaying())
		{
			//��¼���Ƿ��µ������ݣ�
			this->m_state = ATTACKED;
		}
	}
	//�µ������ǹ���״̬��
	else if (temp > g_eggbird_attack)
	{
		if ((this->m_state == ATTACKING||this->m_state == ATTACKED))
		{
			this->m_animation->SetTextureRect(this->m_tex_position.x,
				this->m_tex_position.y,
				this->m_weidth_tex,
				this->m_height_tex);

			this->m_animation->SetFrames(unattack_frame);
			this->m_animation->SetMode(HGEANIM_LOOP);

			this->m_animation->Resume();
			//���µ���������ҷ��У��������ķ���Ϊ�ң�
			this->m_direction = RIGHT;

			this->m_state=  UNATTACK;
		}
	}
}
bool CEggBird::IsHit()
{
	return false;
}

bool CEggBird::IsLayegg()
{
	if(m_state == ATTACKED)
		return true;
	else 
		return false;
}

void CEggBird::Check(Position target,int attacking_frame)
{

}
CEggBird::~CEggBird(void)
{
	if (NULL != m_animation)
	{
		m_hge->Texture_Free(m_tex);
		delete m_animation;
		m_animation = NULL;
	}
}
