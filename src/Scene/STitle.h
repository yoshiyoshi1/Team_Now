//**********************************************
//
//		�^�C�g����ʂ��Ǘ�����N���X
//
//**********************************************


#ifndef __STitle_h__
#define __STitle_h__

#include "SceneBase.h"

class Camera;
class map;

class STitle :public SceneBase 
{
public:
	STitle();
	~STitle();
	int Update()override;
	void Draw()override;
	
	// 3D�`��
	void Render()override;
	// �X�v���C�g�`��
	void DrawSprite()override;
	// �e�L�X�g�\��
	void DisplayText()override;

private:
	Camera* m_Cam;
	map* m_map;
	
	// �\���e�X�g�p
	CTexture m_texSample[2];
	CMesh m_meshSample;


};

#endif
