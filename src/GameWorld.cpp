#include "main.h"
#include "GameWorld.h"

#include "Scene/SceneBase.h"
#include "Scene/STitle.h"
#include "Scene/SGame.h"


GameWorld *GameWorld::m_lpInstance = NULL;

GameWorld::GameWorld() {
	m_lpInstance = this;

	// ������ʂ̓^�C�g�����
	m_lpNowScene = new STitle();
}

GameWorld::~GameWorld() {
	
	if (m_lpNowScene != NULL) {
		delete m_lpNowScene;
	}
}

//==========================================
// �Q�[���S�̂̍X�V
//==========================================
void GameWorld::Update()
{
	// �e�V�[���̍X�V
	if (m_lpNowScene == NULL) { return; }
	int next = m_lpNowScene->Update();

	// �V�[���؂�ւ�
	if (m_lpNowScene->GetID() != next) {
		ChangeScene(next);
	}
}

//==========================================
// �Q�[���S�̂̕`��
//==========================================
void GameWorld::Draw()
{
	// �e�V�[���̕`��
	if (m_lpNowScene != NULL) {
		m_lpNowScene->Draw();
	}
}


//==========================================
// �V�[���̐؂�ւ�������֐�
//==========================================
void GameWorld::ChangeScene(int _next)
{
	if (m_lpNowScene) {
		delete m_lpNowScene;
		m_lpNowScene = NULL;
	}
	if (_next == SceneBase::TITLE) {
		m_lpNowScene = new STitle();
	}
	if (_next == SceneBase::GAME) {
		m_lpNowScene = new SGame();
	}

}


