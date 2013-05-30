#include "CBigMouseBird.h"
#include "CYoungPig.h"

CBigMouseBird::CBigMouseBird(void)
{

}
CBigMouseBird::CBigMouseBird(HGE* _hge, 
	CYoungPig* _pig,
	char* filename, 
	Color _color,
	int _weidth_tex,
	int _height_tex, 
	int _frame,
	int _FPS)
{
	this->m_hge = _hge;
	this->m_pig = _pig;
	this->m_color = _color;
	this->m_tex_position = Position(0,_color*_height_tex*3);
	this->m_direction = RIGHT;
	this->m_state = UNATTACK;
	
	this->m_weidth_tex = _weidth_tex;
	this->m_height_tex = _height_tex;
	
	this->m_tex = m_hge->Texture_Load(filename);
	this->m_animation = new hgeAnimation(m_tex,_frame,_FPS,
		m_tex_position.x,m_tex_position.y,
		_weidth_tex,_height_tex);
}


void CBigMouseBird::AI(Position target,int unattack_frame,int attacking_frame,int attacked_frame)
{
	//计算大嘴鸟和目标的距离作为零时数据，用来比较大嘴鸟和目标的距离用；
	double temp = sqrt((double)((this->m_screen_position.x+m_weidth_tex/2-target.x)*(this->m_screen_position.x+m_weidth_tex/2-target.x))
		+((this->m_screen_position.y+m_height_tex/2-target.y)*(this->m_screen_position.y+m_height_tex/2-target.y)));

	//目标进入大嘴鸟的攻击范围；
	if ((temp <= g_bigbird_attack_distanc)&&(this->m_state == UNATTACK))
	{
		//变化纹理的坐标为大嘴鸟攻击状态的纹理；
		this->m_animation->SetTextureRect(this->m_tex_position.x,
			this->m_tex_position.y+this->m_height_tex,
			this->m_weidth_tex,
			this->m_height_tex);
		//设置大嘴鸟的攻击状态的纹理帧数；
		this->m_animation->SetFrames(attacking_frame);

		this->m_animation->Resume();
		//设置大嘴鸟的攻击状态为正在攻击状态；
		this->m_state = ATTACKING;

		//把大嘴鸟的中心位置与目标位置相比较来确定大嘴鸟的方向；
		if((this->m_screen_position.x+this->m_weidth_tex/2) <= target.x)
		{
			this->m_direction = RIGHT;
		}
		else
		{
			this->m_direction = LEFTE;
		}
	}
	else //大嘴鸟离开攻击范围后；
		if ((temp>g_bigbird_attack_distanc)&&(this->m_state == ATTACKING))
		{
			//变化纹理的坐标为大嘴鸟非攻击状态的纹理；
			this->m_animation->SetTextureRect(this->m_tex_position.x,
				this->m_tex_position.y,
				this->m_weidth_tex,
				this->m_height_tex);
			//设置大嘴鸟的非攻击状态的纹理帧数；
			this->m_animation->SetFrames(unattack_frame);

			this->m_animation->Resume();
			//大嘴鸟重新恢复到非攻击状态，继续向右飞走；
			this->m_direction = RIGHT;
			//大嘴鸟的攻击状态变成非攻击状态；
			this->m_state = UNATTACK;
		}
		else //大嘴鸟处于攻击状态，但是没有撞到目标；
			if ((temp<g_bigbird_attack_distanc)&&(this->m_state == ATTACKING)&&(temp > g_bigbird_collision_distance))
			{
				//通过目标位置来确定大嘴鸟的飞行方向；
				if((this->m_screen_position.x+ this->m_weidth_tex/2) <= target.x)
				{
					this->m_direction = RIGHT;
				}
				else if((this->m_screen_position.x+ this->m_weidth_tex/2) > target.x)
				{
					this->m_direction = LEFTE;
				}
			}
			else //大嘴鸟撞到目标；
				if ((this->m_state == ATTACKING)&&(temp <= g_bigbird_collision_distance))
				{
					//首先小猪会受伤,m_showequipment[4]表示小猪的血量;
					m_pig->Hurt(); 
					//变化纹理的坐标为大嘴鸟撞击状态的纹理；
					this->m_animation->SetTextureRect(this->m_tex_position.x,
						this->m_tex_position.y+this->m_height_tex*2,
						this->m_weidth_tex,
						this->m_height_tex);
					//大嘴鸟不再移动；
					this->m_x_speed = 0.0;
					//撞击的纹利帧数；
					this->m_animation->SetFrames(attacked_frame);
					//设置为非循环模式，为后面的，当播放停止时，目标减血；
					this->m_animation->SetMode(HGEANIM_NOLOOP);
					//设置鸟的桩为后面的，当播放停止时，目标减血；
					this->m_state = ATTACKED;
				}
}


bool CBigMouseBird::IsHit()
{
	return (!this->m_animation->IsPlaying());
}

bool CBigMouseBird::IsLayegg()
{
	return false;
}
void CBigMouseBird::Check(Position target,int attacking_frame)
{

}
CBigMouseBird::~CBigMouseBird(void)
{
	if (NULL != this->m_animation)
	{
		m_hge->Texture_Free(m_tex);
		delete this->m_animation;
		this->m_animation = NULL;
	}
}
