#include "CAnimation.h"


CAnimation::CAnimation(void)
{

}

CAnimation::CAnimation(HGE* _hge, 
	                   char* filename, 
	                   Position _tex_position, 
					   int _weidth_tex,int _height_tex,
					   int _frame,int _FPS)
{
	m_hge = _hge;
//	m_frame = _frame;
//	m_FPS = _FPS;
	this->m_direction = RIGHT;
	

	m_tex_position = _tex_position;
	this->m_weidth_tex = _weidth_tex;
	this->m_height_tex = _height_tex;
	m_tex = m_hge->Texture_Load(filename);
	this->m_animation = new hgeAnimation(m_tex,_frame,_FPS,
		                                 m_tex_position.x,m_tex_position.y,
										 _weidth_tex,_height_tex);

}

void CAnimation::Play(int playmode,Position _screen_position,double _x_speed,double _y_speed)
{
	this->m_screen_position = _screen_position;
	this->m_x_speed = _x_speed;
	this->m_y_speed = _y_speed;
	this->m_animation->SetMode(playmode);
	this->m_animation->Play();
}


void CAnimation::Fly()
{
	this->m_animation->SetFlip(m_direction,false);
	this->m_animation->Render(this->m_screen_position.x,this->m_screen_position.y);
}


void CAnimation::Update(float deltatime)
{
	if (((this->m_direction == RIGHT)&&(this->m_x_speed<0))
		||((this->m_direction == LEFTE)&&(this->m_x_speed > 0)))
		this->m_x_speed =-m_x_speed;

	this->m_screen_position.x += this->m_x_speed;
	this->m_screen_position.y += this->m_y_speed;
	this->m_animation->Update(deltatime);
}

Position CAnimation::GetCurrenPosition()
{
	return m_screen_position;
}

void CAnimation::SetPositionX(int _xpos)   //ÉèÖÃ¾«Áé»æÖÆXÎ»ÖÃ;
{
	m_screen_position.x = _xpos;
}

bool CAnimation::IsCollision(Position _bullet,int _attack_distance)
{//Åö×²¼ì²â;
	if (sqrt((abs(_bullet.x - this->m_screen_position.x+this->m_weidth_tex/2.0f)*abs(_bullet.x-this->m_screen_position.x+this->m_weidth_tex/2.0f))
		+(abs(_bullet.y-this->m_screen_position.y+this->m_height_tex/2.0f)*abs(_bullet.y-this->m_screen_position.y+this->m_height_tex/2.0f))) 
		<= _attack_distance)
	{
		return true;
	}
	else
		return false;
}

Color CAnimation::GetColor()
{
	return m_color;
}

void CAnimation::SetColor(Color _color)
{
	this->m_color = _color;
}

CAnimation::~CAnimation(void)
{
	if (NULL != this->m_animation)
	{
		m_hge->Texture_Free(m_tex);
		delete this->m_animation;
		this->m_animation = NULL;
	}
}
