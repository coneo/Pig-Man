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

	

	//初始化闪电鸟的攻击位置；
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
	//闪电鸟到达攻击范围后，进行快速俯冲攻击目标；
	if (((int)this->m_screen_position.x+m_weidth_tex/2) > this->m_attack_spot
		&&this->m_state == UNATTACK)
	{
		//变化纹理的坐标为闪电鸟攻击状态的纹理；
		m_animation->SetTextureRect(m_tex_position.x,m_tex_position.y+m_height_tex,
			m_weidth_tex,m_height_tex);
		//设置闪电鸟的攻击状态的纹理帧数；
		m_animation->SetFrames(attacking_frame);

		m_animation->SetMode(HGEANIM_NOLOOP);
		//记录闪电鸟的攻击速度，为后面的计算闪电鸟的跟踪路径服务；
		this->m_speed = this->m_x_speed;
		//设置闪电鸟的攻击状态为正在攻击状态；
		this->m_state = ATTACKING;
	}
	else if (this->m_state == ATTACKING)
	{
		//改变小鸟的速度为攻击速度；
		this->m_speed = g_light_attack_speed;
		//在检测中要用到的临时参数,为后面的方向确定服务；
		double deltax = target.x - this->m_screen_position.x+m_weidth_tex/2.0f;
		double deltay = target.y - this->m_screen_position.y+m_height_tex/2.0f;
		//记录当前目标与闪电鸟的角度；
		double angle ;
		//计算目标与闪电鸟距离
		double distance = sqrt((target.x-this->m_screen_position.x+m_weidth_tex/2.0f)*(target.x-this->m_screen_position.x+m_weidth_tex/2.0f)
			+(target.y-this->m_screen_position.y+m_height_tex/2.0f)*(target.y-this->m_screen_position.y+m_height_tex/2.0f));

		//实时监控小鸟与目标的角度；
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

		//根据角度来计算小鸟的速度和小鸟的路线；

		this->m_x_speed =  this->m_speed*cos(angle);
		this->m_y_speed =  this->m_speed*sin(angle);

		// 根据闪电鸟的速度来改变闪电鸟的方向；
		if (this->m_x_speed >= 0)
		{
			this->m_direction = RIGHT;
		}
		else
			this->m_direction = LEFTE;
		//检测闪电鸟时候撞到目标；
		if (distance <= g_light_attack_distanc)
		{
			//小猪会受伤;
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
		//记住一定要释放纹理资源；
		m_hge->Texture_Free(m_tex);
		delete this->m_animation;
		this->m_animation = NULL;
	}
}
