#pragma once
#include "CObjects.h"

enum ObjectsType{
	ROCKET,     //���;
	FART,       //ƨ;
	QUICKEN,    //����;
	IGNORING,   //����;
	LIFE        //Ѫƿ;
};

class CDropingObjects : public CObjects
{
public:
	CDropingObjects();
	~CDropingObjects();

	void   TextureLoad(char* filename);              //���ش�ͼ;
	void   SetTexture(int x_positon, int y_position, int width, int height);  //���þ������������ȷ�����Ǹ�����Ʒ������;
private:
	ObjectsType   m_objType;        //��Ʒ���ͣ�
};

