#include "CAnimEgg.h"
#include "CYoungPig.h"

CAnimEgg::CAnimEgg(void)
{
}

CAnimEgg::CAnimEgg(HGE* _hge, CYoungPig* _pig, char* filename, 
	Position _tex_position, 
	int _weidth_tex,int _height_tex,
	int _frame,int _FPS)
{
	this->m_hge = _hge;
	this->m_pig = _pig;
	this->m_tex_position = _tex_position;
	this->m_ishit = false;

	//������Ϊ��ֻ���������� �����Ծ�����������ʾ��
	this->m_direction = RIGHT;
	this->m_state = UNATTACK;

	this->m_weidth_tex = _weidth_tex;
	this->m_height_tex = _height_tex;
	this->m_tex = this->m_hge->Texture_Load(filename);
	this->m_animation = new hgeAnimation(m_tex,_frame,_FPS,
		m_tex_position.x,m_tex_position.y,
		_weidth_tex,_height_tex);
}
void CAnimEgg::Check(Position target,
	int attacking_frame)
{
	//ģ�������������Ч����
	if(this->m_state == UNATTACK)
		this->m_y_speed += 0.98-(this->m_y_speed*0.2);

	if (abs(target.x-this->m_screen_position.x+this->m_weidth_tex/2.0f) <= 40
		||abs(target.y-this->m_screen_position.y+this->m_height_tex/2.0f)<=40)
	{
		double distance = sqrt((target.x-this->m_screen_position.x+m_weidth_tex/2.0f)*(target.x-this->m_screen_position.x+m_weidth_tex/2.0f)
			+(target.y-this->m_screen_position.y+m_height_tex/2.0f)*(target.y-this->m_screen_position.y+m_height_tex/2.0f));
		
		if (distance <= g_egg_attack_distace&&m_state == UNATTACK)
		{//��ײ��Ŀ���ϣ�
			
			//С�������;
			m_pig->Hurt();
			this->m_y_speed = 0;
			this->m_state = ATTACKING;
			this->m_animation->SetFrames(attacking_frame);
			this->m_animation->SetMode(HGEANIM_NOLOOP);
		}
		if (!this->m_animation->IsPlaying())
		{
			//��¼ײ��Ŀ�ꣻ
			this->m_ishit = true;
			this->m_state = ATTACKED;
		}
	}
	//����������
	if ((this->m_screen_position.y+m_height_tex) >= g_y_ground)
	{
		if (this->m_state == UNATTACK)
		{
			//�񵰾�ֹײ�����ϣ�
			this->m_y_speed = 0;
			this->m_state = ATTACKING;
			this->m_animation->SetFrames(attacking_frame);
			this->m_animation->SetMode(HGEANIM_NOLOOP);
		}
		if (!this->m_animation->IsPlaying())
		{
			this->m_ishit = true;
		}
	}
}

bool CAnimEgg::IsHit()
{
	return this->m_ishit;
}
bool CAnimEgg::IsLayegg()
{
	return false;
}
void CAnimEgg::AI(Position target, int unattack_frame, int attacking_frame, int attacked_frame)
{

}
State CAnimEgg::GetState()
{
	return m_state;
}
CAnimEgg::~CAnimEgg(void)
{
	if(NULL != this->m_animation)
	{
		m_hge->Texture_Free(m_tex);
		delete this->m_animation;
		this->m_animation = NULL;
	}
}
