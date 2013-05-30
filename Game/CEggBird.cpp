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
	//下蛋鸟进入攻击范围 或者处于攻击状态时；
	if (temp <= g_eggbird_attack||this->m_state == ATTACKING)
	{
		//当下蛋鸟在攻击范围内时，非正在攻击状态时才准备下蛋；
		if ((this->m_state ==  UNATTACK||this->m_state == ATTACKED))
		{
			//改变下蛋鸟的状态为正在攻击状态；
			this->m_state = ATTACKING;
			this->m_animation->SetMode(HGEANIM_NOLOOP);
			//让他的处于播放状态；
			this->m_animation->Resume();
			//变化纹理的坐标为下蛋鸟攻击状态的纹理；
			this->m_animation->SetTextureRect(this->m_tex_position.x,
				this->m_tex_position.y+this->m_height_tex,
				this->m_weidth_tex,
				this->m_height_tex);
			//设置下蛋鸟的攻击状态的纹理帧数；
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
		//处于攻击范围内；
		else if (this->m_state == ATTACKING
			&&!this->m_animation->IsPlaying())
		{
			//记录看是否下蛋的数据；
			this->m_state = ATTACKED;
		}
	}
	//下蛋鸟进入非攻击状态；
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
			//让下蛋鸟继续向右飞行；设置他的方向为右；
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
