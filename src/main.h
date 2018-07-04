#ifndef __main_h__
#define __main_h__

#include "../SimpleLib/SimpleLib.h"
using namespace SimpleLib;

//============================================================
//
// �A�v���P�[�V�����N���X
//	�O���[�o���ϐ��Ȃǂ��W�߂��悤�ȃN���X
//
//============================================================
class CApp
{
public:
	//=================================================
	// �E�B���h�E�֌W
	HINSTANCE	m_hInst;			
	HWND		m_hWnd;				
	int			m_WndW,m_WndH;		
	bool		m_CloseFlag;		
	bool		m_bEndFlag;		// �I���t���O	
	DWORD		m_FrameCnt;			

	// �E�B���h�E������
	bool InitWindow(HINSTANCE hInstance,int w,int h);	

	// ���̑��̏�����
	void Init();

	// ���C�����[�v
	int Loop();

	// ���
	void Release();

	// �E�B���h�E�֐�
	static LRESULT CALLBACK callWindowProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);
	LRESULT CALLBACK WindowProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);

	// �N���C�A���g�T�C�Y�̐ݒ�
	void SetClientSize(HWND hWnd,int w,int h);

	//=====================================================
	// �}�E�X�p
	int		m_MouseWheelVal;

	// �O��̌o�ߎ���
	DWORD m_PrevTime = 0;

//*********************************************
// �V���O���g���p�^�[��
private:
	// 
	CApp(){
		m_hWnd = nullptr;
		m_WndW = 0;
		m_WndH = 0;
		m_hInst = nullptr;
		m_CloseFlag = false;
		m_bEndFlag = false;
		m_FrameCnt = 0;
		m_MouseWheelVal = 0;

	}

public:
	static CApp &GetInstance(){
		static CApp Instance;
		return Instance;
	}
//*********************************************

};

//========================================================
// ���̑��̃f�[�^
//========================================================

// ����g�p���钸�_�t�H�[�}�b�g�̒�`
struct VERTEX
{
	D3DXVECTOR3 Pos;
	D3DCOLOR Color;
	D3DXVECTOR2 Tex;
};

static const int POLY_VERTEX = 4;	// �|���S���̒��_��

struct XFILE
{
	LPD3DXMESH lpMesh;
	DWORD NumMaterial;
	D3DMATERIAL9 *Mat;
	LPDIRECT3DTEXTURE9 *Tex;
};

struct CLONEVERTEX
{
	D3DXVECTOR3 Pos;
	D3DXVECTOR3 Normal;
	D3DXVECTOR2 Tex;
};

#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)


#define APP CApp::GetInstance()


#endif
