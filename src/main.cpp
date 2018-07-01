//======================================================================================
//
// �Q�[���T�C�N��
//
//======================================================================================
#include "main.h"
#include "GameWorld.h"

//=========================================================
//���C��
//=========================================================
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInst,LPSTR lpszArgs,int nWinMode)
{
	// ���������[�N��m�点��
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);

	if(APP.InitWindow(hInstance, 1280, 720) == false){
		return 0;
	}

	// ���̑��̏�����
	APP.Init();

	// ���[�v
	APP.Loop();

	// ���
	APP.Release();

	return 0;
}

//=========================================================
// �����ݒ�
//=========================================================
bool CApp::InitWindow(HINSTANCE hInstance,int w,int h)
{
	// �J�����g�f�B���N�g���擾
	m_hInst = hInstance;

	//--------------------------------------------------------------------
	// ���C���E�B���h�E�쐬
	//--------------------------------------------------------------------
	//�E�B���h�E�N���X�̒�`
	WNDCLASSEX wc;											
	wc.cbSize=sizeof(WNDCLASSEX);							
	wc.style = 0;											
	wc.lpfnWndProc = &CApp::callWindowProc;					
	wc.cbClsExtra = 0;										
	wc.cbWndExtra = 0;										
	wc.hInstance = m_hInst;									
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);			
	wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);		
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);			
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	
	wc.lpszMenuName = nullptr;								
	wc.lpszClassName = "Window";							

	//�E�B���h�E�N���X�̓o�^
	if(!RegisterClassEx(&wc)){
		return FALSE;
	}

	//�E�B���h�E�̍쐬
	m_hWnd = CreateWindow(
		"Window",										
		"Team_NOW",		// �^�C�g���o�[										
		WS_OVERLAPPEDWINDOW-WS_THICKFRAME,					
		0,												
		0,																	
		800,											
		600,											
		nullptr,										
		nullptr,										
		m_hInst,										
		nullptr);										

	// �N���C�A���g�̃T�C�Y��ݒ�
	SetClientSize(m_hWnd,w,h);

	timeBeginPeriod(1);

	//--------------------------------------------------------------------
	// �t���X�N���[���m�F
	//--------------------------------------------------------------------
	bool bFullScreen = false;
	if (MessageBox(m_hWnd, "�t���X�N���[���ɂ��܂����H", "�m�F", MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDYES) {
		bFullScreen = true;
	}

	//--------------------------------------------------------------------
	// Direct3D������
	//--------------------------------------------------------------------
	if(cdg.Init(m_hWnd, m_WndW, m_WndH, D3DFMT_X8R8G8B8, bFullScreen) == FALSE){
		MessageBox(m_hWnd,"Direct3D�������~�X","",MB_OK);
		return FALSE;
	}

	// ��{�I�ȃ����_�[�X�e�[�g�ݒ�
	cdg.SetState();

	//--------------------------------------------------------------------
	//�E�B���h�E�̕\��
	//--------------------------------------------------------------------
	ShowWindow(m_hWnd,SW_SHOW);
	//�E�B���h�E�̍X�V
	UpdateWindow(m_hWnd);


	//--------------------------------------------------------------------
	// ���̑�
	//--------------------------------------------------------------------
	m_CloseFlag = false;
	m_bEndFlag = false;

	return TRUE;
}

//======================================================
// ���
//======================================================
void CApp::Release()
{
	// �V���O���g���̃C���X�^���X�폜
	GW->DeleteInstance();

	// Direct3D���
	cdg.Release();
}

//======================================================
// ������
//======================================================
void CApp::Init()
{
	// �V���O���g���̃C���X�^���X��
	GW->CreateInstance();
}

//======================================================
// ���C�����[�v
//======================================================
int CApp::Loop()
{
	MSG msg;	
	
	//���b�Z�[�W���[�v
	while(1){
		
		// �~�{�^����������I���t���OON�B
		if (m_CloseFlag) {
			m_bEndFlag = true;		// �I���t���OON
		}
		
		// �I���t���O�������Ă���Ȃ�A���[�v����o��
		if (m_bEndFlag)break;

		// ���b�Z�[�W�擾
		if(PeekMessage(&msg,nullptr,0,0,PM_REMOVE)){
			//���b�Z�[�W����
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		// �Q�[������
		else{
			DWORD st = timeGetTime();	// �J�n���Ԃ��擾

			//------------------------------------------
			// �����E�`��
			//------------------------------------------
			// FPS���� (60FPS)
			DWORD NowTime = timeGetTime();
			if ((NowTime - m_PrevTime) >= 1000 / 60) {
				m_PrevTime = NowTime;
				GW->Update();
				GW->Draw();
			}

			//------------------------------------------
			// �`��
			//------------------------------------------
			cdg.GetDev()->Present(nullptr, nullptr, nullptr, nullptr);


			// �z�C�[���l�̓��Z�b�g
			m_MouseWheelVal = 0;

			m_FrameCnt++;
		}
		
	}

	return 0;
}

//======================================================
//�E�B���h�E�֐� callWindowProc
//======================================================
LRESULT CALLBACK CApp::callWindowProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	return APP.WindowProc(hWnd,message,wParam,lParam);
}

//======================================================
// �E�B���h�E�֐� WindowProc
//======================================================
LRESULT CApp::WindowProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{

	//���b�Z�[�W�ɂ���ď�����I��
	switch(message){
		case WM_SIZE:
			{
				RECT rcWnd,rcCli;
				GetWindowRect(hWnd, &rcWnd); // �E�B���h�E��RECT�擾
				GetClientRect(hWnd, &rcCli); // �N���C�A���g�̈��RECT�擾
				m_WndW = rcCli.right;
				m_WndH = rcCli.bottom;
			}
			break;
		case WM_CLOSE:// �E�B���h�E�������
			m_CloseFlag = true;
			break;
		// �z�C�[���X�N���[����
		case WM_MOUSEWHEEL:
			{
				m_MouseWheelVal = (short)HIWORD(wParam);
			}
			break;
        default:
			//�s�v�ȃ��b�Z�[�W�̌�n��
			return DefWindowProc(hWnd,message,wParam,lParam);
	}
	return 0;
}


//======================================================
// �E�B���h�E�̃N���C�A���g�̃T�C�Y���w��T�C�Y�ɂ���B
//======================================================
void CApp::SetClientSize(HWND hWnd,int w,int h)
{
	RECT rcWnd,rcCli;

	GetWindowRect(hWnd,&rcWnd); // �E�B���h�E��RECT�擾
	GetClientRect(hWnd,&rcCli); // �N���C�A���g�̈��RECT�擾

	// �E�B���h�E�̗]�����l���āA�N���C�A���g�̃T�C�Y���w��T�C�Y�ɂ���B
	MoveWindow(hWnd,
			rcWnd.left,// X���W
			rcWnd.top,// Y���W
			w + (rcWnd.right-rcWnd.left)-(rcCli.right-rcCli.left),
			h + (rcWnd.bottom-rcWnd.top)-(rcCli.bottom-rcCli.top),
			TRUE);
}
