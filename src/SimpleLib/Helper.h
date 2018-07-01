#ifndef __Helper_h__
#define __Helper_h__

//=================================================================
//
// あると便利なマクロや関数
//
//=================================================================


#pragma warning(disable:4996)
#include <string>

namespace SimpleLib{

// 度 -> ラジアン 変換
#define ToRadian(x) ((x)*0.017453f)
// ラジアン -> 度 変換
#define ToDegree(x) ((x)*57.3f)

// 安全なポインタの解放 ※本当はdefineでなく、テンプレート関数などにしたほうが良い
#define SAFE_FREE(p)		{if(p){free(p);p=nullptr;}}				// mallocしたものを安全にfreeするマクロ
#define SAFE_RELEASE(p)		{if(p){p->Release();p=nullptr;}}		// COMオブジェクト系を安全にReleaseするマクロ
#define SAFE_DELETE(p)		{if(p){delete p;p=nullptr;}}			// newされた変数を安全に解放するマクロ
#define SAFE_DELETE_ARRAY(p){if(p){delete[] p;p=nullptr;}}			// newされた配列を安全に解放するマクロ

// 色関係の短縮名用
#define XRGB(r,g,b) D3DCOLOR_XRGB(r,g,b)
#define ARGB(a,r,g,b) D3DCOLOR_ARGB(a,r,g,b)
#define RGBA(r,g,b,a) D3DCOLOR_RGBA(r,g,b,a)
#define COLORVALUE(a,r,g,b) D3DCOLOR_COLORVALUE(r,g,b,a)

// FPS計測
DWORD FpsProc();

// ログ出力
void AddLogFile(char *LogFileName,char *str, bool bData=false);

//=================================================================
// 可変引数メッセージボックス
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

// キー判定(1回押し)
bool KeyCheck(int keyCode);

}


#endif
