#include "../main.h"
#include "../GameWorld.h"

#include "../Camera/Camera.h"
#include"../Map/map.h"
#include "STitle.h"


STitle::STitle() 
{
	m_id = TITLE;

	cdg.SetDirectionalLight(0,
		&CVector3(1, -1, 0),				// ���C�g�̕���
		&D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),	// ��{�F(�f�B�t�[�Y RGBA)
		&D3DXCOLOR(0.3f, 0.3f, 0.3f, 0.0f),	// ���F(�A���r�G���g RGBA)
		&D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f)	// ���ːF(�X�y�L���� RGBA)
	);


	m_Cam = new Camera();
	m_Cam->SetProj();

	m_map = new map();
	m_map->LoadMap();
	m_meshSample.LoadXFile("../data/Mesh/TestData/Model.x");
	m_texSample[0].LoadTexture("../data/Sprite/TestData/back.png");
	m_texSample[1].LoadTexture("../data/Sprite/TestData/continue.png");
}

STitle::~STitle()
{
	Safe_Delete(m_Cam);
}

//===================================
// �^�C�g����ʂ̍X�V
//===================================
int STitle::Update()
{
	// Esc �L�[�ŃQ�[���I��
	if (GetAsyncKeyState(VK_ESCAPE)) {
		APP.m_CloseFlag = true;
	}

	return TITLE;
}

//===================================
// �^�C�g����ʂ̕`��
//===================================
void STitle::Draw()
{
	// �`��J�n
	cdg.GetDev()->BeginScene();

	// �o�b�N�o�b�t�@�� Z �o�b�t�@���N���A
	cdg.Clear(true, true, false, XRGB(0, 0, 100), 1.0f, 0);


	//-------------------------------------------
	// �J��������
	//-------------------------------------------
	//m_Cam->SetView();

	//-------------------------------------------
	// �`�揈��
	//-------------------------------------------
	Render();


	cdg.BeginSprite();
	{
		//-------------------------------------------
		// �X�v���C�g	2D�摜
		//-------------------------------------------
		DrawSprite();

		//--------------------------------------------
		// �����\��
		//--------------------------------------------
		DisplayText();

	}
	cdg.EndSprite();

	// �`��I��
	cdg.GetDev()->EndScene();

	// �o�b�N�o�b�t�@���v���C�}���o�b�t�@�ɃR�s�[
	cdg.GetDev()->Present(nullptr, nullptr, nullptr, nullptr);

}


//================================================================
// �`�揈��
//================================================================
void STitle::Render()
{

	//-------------------------------------------
	// �\���e�X�g�p
	//-------------------------------------------
	{
		m_map->DrawMap();
		CMatrix m;
		m.CreateMove(0, -2, 10);
		m.RotateY_Local(45);
		m_meshSample.Draw(&m);
	}
}

//================================================================
// �X�v���C�g�`��
//================================================================
void STitle::DrawSprite()
{

	//-------------------------------------------
	// �\���e�X�g�p
	//-------------------------------------------
	{
		CMatrix m;
	
		m.CreateMove(0, 0, 1);
		cdg.DrawSprite(&m_texSample[0], ARGB_FULL, &m);

		m.CreateMove(100, 200, 1);
		cdg.DrawSprite(&m_texSample[1], ARGB_FULL, &m);
	}
}

//================================================================
// �e�L�X�g�\��
//================================================================
void STitle::DisplayText()
{

	//-------------------------------------------
	// �\���e�X�g�p
	//-------------------------------------------
	{
		CMatrix m;
		m.CreateMove(100, 100, 0);
		cdg.DrawFont("�^�C�g��", ARGB_FULL, &m);
	}
}
