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
	//����������Ŀ��ľ�����Ϊ��ʱ���ݣ������Ƚϴ������Ŀ��ľ����ã�
	double temp = sqrt((double)((this->m_screen_position.x+m_weidth_tex/2-target.x)*(this->m_screen_position.x+m_weidth_tex/2-target.x))
		+((this->m_screen_position.y+m_height_tex/2-target.y)*(this->m_screen_position.y+m_height_tex/2-target.y)));

	//Ŀ����������Ĺ�����Χ��
	if ((temp <= g_bigbird_attack_distanc)&&(this->m_state == UNATTACK))
	{
		//�仯���������Ϊ�����񹥻�״̬������
		this->m_animation->SetTextureRect(this->m_tex_position.x,
			this->m_tex_position.y+this->m_height_tex,
			this->m_weidth_tex,
			this->m_height_tex);
		//���ô�����Ĺ���״̬������֡����
		this->m_animation->SetFrames(attacking_frame);

		this->m_animation->Resume();
		//���ô�����Ĺ���״̬Ϊ���ڹ���״̬��
		this->m_state = ATTACKING;

		//�Ѵ����������λ����Ŀ��λ����Ƚ���ȷ��������ķ���
		if((this->m_screen_position.x+this->m_weidth_tex/2) <= target.x)
		{
			this->m_direction = RIGHT;
		}
		else
		{
			this->m_direction = LEFTE;
		}
	}
	else //�������뿪������Χ��
		if ((temp>g_bigbird_attack_distanc)&&(this->m_state == ATTACKING))
		{
			//�仯���������Ϊ������ǹ���״̬������
			this->m_animation->SetTextureRect(this->m_tex_position.x,
				this->m_tex_position.y,
				this->m_weidth_tex,
				this->m_height_tex);
			//���ô�����ķǹ���״̬������֡����
			this->m_animation->SetFrames(unattack_frame);

			this->m_animation->Resume();
			//���������»ָ����ǹ���״̬���������ҷ��ߣ�
			this->m_direction = RIGHT;
			//������Ĺ���״̬��ɷǹ���״̬��
			this->m_state = UNATTACK;
		}
		else //�������ڹ���״̬������û��ײ��Ŀ�ꣻ
			if ((temp<g_bigbird_attack_distanc)&&(this->m_state == ATTACKING)&&(temp > g_bigbird_collision_distance))
			{
				//ͨ��Ŀ��λ����ȷ��������ķ��з���
				if((this->m_screen_position.x+ this->m_weidth_tex/2) <= target.x)
				{
					this->m_direction = RIGHT;
				}
				else if((this->m_screen_position.x+ this->m_weidth_tex/2) > target.x)
				{
					this->m_direction = LEFTE;
				}
			}
			else //������ײ��Ŀ�ꣻ
				if ((this->m_state == ATTACKING)&&(temp <= g_bigbird_collision_distance))
				{
					//����С�������,m_showequipment[4]��ʾС���Ѫ��;
					m_pig->Hurt(); 
					//�仯���������Ϊ������ײ��״̬������
					this->m_animation->SetTextureRect(this->m_tex_position.x,
						this->m_tex_position.y+this->m_height_tex*2,
						this->m_weidth_tex,
						this->m_height_tex);
					//���������ƶ���
					this->m_x_speed = 0.0;
					//ײ��������֡����
					this->m_animation->SetFrames(attacked_frame);
					//����Ϊ��ѭ��ģʽ��Ϊ����ģ�������ֹͣʱ��Ŀ���Ѫ��
					this->m_animation->SetMode(HGEANIM_NOLOOP);
					//�������׮Ϊ����ģ�������ֹͣʱ��Ŀ���Ѫ��
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
