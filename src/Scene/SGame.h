//**********************************************
//
//		�Q�[����ʂ��Ǘ�����N���X
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
	
	// 3D�`��
	void Render()override;
	// �X�v���C�g�`��
	void DrawSprite()override;
	// �e�L�X�g�\��
	void DisplayText()override;

private:
	
};

#endif