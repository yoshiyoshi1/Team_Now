//**********************************************
//
//		�e�V�[���N���X�̃x�[�X
//
//**********************************************

#ifndef __SceneBase_h__
#define __SceneBase_h__

class SceneBase 
{
public:
	SceneBase() {}
	virtual ~SceneBase() {}
	virtual int Update() = 0;
	virtual void Draw() = 0;
	
	// 3D�`��
	virtual void Render(){}
	// �X�v���C�g�`��
	virtual void DrawSprite(){}
	// �e�L�X�g�\��
	virtual void DisplayText(){}

	enum { TITLE, GAME, RESULT };
	int GetID() { return m_id; }
protected:
	int m_id;
};

#endif