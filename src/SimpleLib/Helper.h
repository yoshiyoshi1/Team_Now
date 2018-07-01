#ifndef __Helper_h__
#define __Helper_h__

//=================================================================
//
// ����ƕ֗��ȃ}�N����֐�
//
//=================================================================


#pragma warning(disable:4996)
#include <string>

namespace SimpleLib{

// �x -> ���W�A�� �ϊ�
#define ToRadian(x) ((x)*0.017453f)
// ���W�A�� -> �x �ϊ�
#define ToDegree(x) ((x)*57.3f)

// ���S�ȃ|�C���^�̉�� ���{����define�łȂ��A�e���v���[�g�֐��Ȃǂɂ����ق����ǂ�
#define SAFE_FREE(p)		{if(p){free(p);p=nullptr;}}				// malloc�������̂����S��free����}�N��
#define SAFE_RELEASE(p)		{if(p){p->Release();p=nullptr;}}		// COM�I�u�W�F�N�g�n�����S��Release����}�N��
#define SAFE_DELETE(p)		{if(p){delete p;p=nullptr;}}			// new���ꂽ�ϐ������S�ɉ������}�N��
#define SAFE_DELETE_ARRAY(p){if(p){delete[] p;p=nullptr;}}			// new���ꂽ�z������S�ɉ������}�N��

// �F�֌W�̒Z�k���p
#define XRGB(r,g,b) D3DCOLOR_XRGB(r,g,b)
#define ARGB(a,r,g,b) D3DCOLOR_ARGB(a,r,g,b)
#define RGBA(r,g,b,a) D3DCOLOR_RGBA(r,g,b,a)
#define COLORVALUE(a,r,g,b) D3DCOLOR_COLORVALUE(r,g,b,a)

// FPS�v��
DWORD FpsProc();

// ���O�o��
void AddLogFile(char *LogFileName,char *str, bool bData=false);

//=================================================================
// �ψ������b�Z�[�W�{�b�N�X
//=================================================================
inline void DispMsg(HWND hWnd,char *format, ...)
{
	char str[1024];
	va_list argptr;

	va_start(argptr, format);
	vsprintf(str,format, argptr);
	va_end(argptr);

	MessageBox(hWnd,str,"Message",MB_OK);
}

// �L�[����(1�񉟂�)
bool KeyCheck(int keyCode);

}


#endif
