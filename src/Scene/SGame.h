//**********************************************
//
//		ƒQ[ƒ€‰æ–Ê‚ğŠÇ—‚·‚éƒNƒ‰ƒX
//
//**********************************************


#ifndef __SGame_h__
#define __SGame_h__

#include "SceneBase.h"

class SGame :public SceneBase 
{
public:
	SGame();
	~SGame();
	int Update()override;
	void Draw()override;
	void Render()override;

private:
	
};

#endif