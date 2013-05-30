#pragma once
#include "CObjects.h"

enum ObjectsType{
	ROCKET,     //火箭;
	FART,       //屁;
	QUICKEN,    //极速;
	IGNORING,   //无视;
	LIFE        //血瓶;
};

class CDropingObjects : public CObjects
{
public:
	CDropingObjects();
	~CDropingObjects();

	void   TextureLoad(char* filename);              //加载大图;
	void   SetTexture(int x_positon, int y_position, int width, int height);  //设置精灵的纹理，进而确定是那个该物品的类型;
private:
	ObjectsType   m_objType;        //物品类型；
};

