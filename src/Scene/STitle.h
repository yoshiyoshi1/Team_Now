//**********************************************
//
//		タイトル画面を管理するクラス
//
//**********************************************


#ifndef __STitle_h__
#define __STitle_h__

#include "SceneBase.h"

class STitle :public SceneBase 
{
public:
	STitle();
	~STitle();
	int Update()override;
	void Draw()override;
	void Render()override;

private:
	
};

#endif
