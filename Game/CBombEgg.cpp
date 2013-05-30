#include "CBombEgg.h"
#include "CYoungPig.h"

CBombEgg::CBombEgg(void)
{
}
CBombEgg::CBombEgg(HGE* _hge, CYoungPig* _pig, char* filename,
	Position _tex_position,
	int _weidth_tex,int _height_tex,
	int _frame,int _FPS)
{
	this->m_hge = _hge;
	this->m_pig = _pig;
	this->m_tex_position = _tex_position;
	this->m_ishit = false;

	//这里因为蛋只有两个方向 ，所以就用左右来表示；
	this->m_direction = RIGHT;
	this->m_state = UNATTACK;

	this->m_weidth_tex = _weidth_tex;
	this->m_height_tex = _height_tex;
	this->m_tex = this->m_hge->Texture_Load(filename);
	this->m_animation = new hgeAnimation(m_tex,_frame,_FPS,
		m_tex_position.x,m_tex_position.y,
		_weidth_tex,_height_tex);
}

void CBombEgg::Check(Position target,int attacking_frame)
{
	//模拟鸟蛋自由下落的效果；
	if(this->m_state == UNATTACK)
		this->m_y_speed += 0.98-(this->m_y_speed*0.2);


	double distance = sqrt((target.x-this->m_screen_position.x+m_weidth_tex/2.0f)*(target.x-this->m_screen_position.x+m_weidth_tex/2.0f)
		+(target.y-this->m_screen_position.y+m_height_tex/2.0f)*(target.y-this->m_screen_position.y+m_height_tex/2.0f));
	
	if (distance <= g_bombegg_attack_distance&&m_state == UNATTACK)
	{
		//鸟蛋撞到目标上；

		//小猪会掉两滴血;
		m_pig->Hurt();
		m_pig->Hurt();
		this->m_y_speed = 0;

		this->m_state = ATTACKING;

		this->m_animation->SetTextureRect(m_tex_position.x,m_tex_position.y+m_height_tex,210,130);
		this->m_screen_position = Position(this->m_screen_position.x+this->m_weidth_tex/2.0f-105,
			this->m_screen_position.y+this->m_height_tex-130);
		this->m_animation->SetFrames(attacking_frame);
		this->m_animation->SetMode(HGEANIM_NOLOOP);
	}
	//鸟蛋碰到地上
	if (this->m_screen_position.y >= g_y_round&&this->m_state == UNATTACK)
	{

		//鸟蛋静止撞到地上；
		this->m_y_speed = 0;

		this->m_animation->SetTextureRect(m_tex_position.x,m_tex_position.y+m_height_tex,210,130);

		this->m_screen_position = Position(this->m_screen_position.x+this->m_weidth_tex/2.0f-105,
			this->m_screen_position.y+this->m_height_tex-130);

		this->m_animation->SetFrames(attacking_frame);

		this->m_animation->SetMode(HGEANIM_NOLOOP);

		this->m_state = GROUDN_FIRING;
	}
	if (!this->m_animation->IsPlaying()&&this->m_state  == ATTACKING)
	{
		//记录撞到目标；
		this->m_ishit = true;
		this->m_state = ATTACKED;
	}

	
	if(this->m_state == GROUDN_FIRING&&this->m_animation->IsPlaying())
	{
		if (distance <= g_bomb_attack_distance)
		{
			this->m_state = ATTACKED;
		}
	}
	if(!this->m_animation->IsPlaying())
	{
		this->m_ishit = true;
	}
}

bool CBombEgg::IsHit()
{
	return this->m_ishit;
}
bool CBombEgg::IsLayegg()
{
	return false;
}
State CBombEgg::GetState()
{
	return this->m_state;
}
void CBombEgg::AI(Position target, int unattack_frame, int attacking_frame, int attacked_frame)
{

}

CBombEgg::~CBombEgg(void)
{
	if (NULL != this->m_animation)
	{
		m_hge->Texture_Free(m_tex);
		delete this->m_animation;
		this->m_animation = NULL;
	}
	

}
