#include "SimpleLib.h"

using namespace SimpleLib;

//================================================================================
//
// Direct3D������������B
//	�����FhWnd���Direct3D�Ŏg�p����E�B���h�E
//	�@�@�@Width�����
//�@�@�@�@Height�������
//�@�@�@�@Format����F���[�h
//�@�@�@�@FullScreen����t���X�N���[���t���O
//�@�߂�l�F�������TRUE
//�@�@�@�@�@���s���FALSE
//
//================================================================================
bool CDirectXGraphics::Init(HWND hWnd, int Width, int Height, D3DFORMAT Format, bool FullScreen)
{
	//=======================================================
	// D3D�I�u�W�F�N�g�쐬
	//=======================================================
	m_lpD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_lpD3D == nullptr) {
		return false;
	}

	//=======================================================
    // ���݂̉�ʃ��[�h���擾
	//=======================================================
	D3DDISPLAYMODE d3ddm;
	if( FAILED( m_lpD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm ) ) ) return false;

	//=======================================================
	// �ݒ�
	//=======================================================
	ZeroMemory( &m_d3dpp, sizeof(m_d3dpp) );
	m_d3dpp.BackBufferCount = 2;
    if (FullScreen){
        m_d3dpp.Windowed = FALSE;
        m_d3dpp.BackBufferWidth = Width;
        m_d3dpp.BackBufferHeight = Height;
	    m_d3dpp.BackBufferFormat = Format;
    }else{
        m_d3dpp.Windowed = TRUE;
        m_d3dpp.BackBufferWidth = 0;
        m_d3dpp.BackBufferHeight = 0;
	    m_d3dpp.BackBufferFormat = d3ddm.Format;
    }
	m_d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	// �X���b�v �G�t�F�N�g
	m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// ���j�^�̐���������҂��Ȃ�
	m_d3dpp.hDeviceWindow = hWnd;
    // Z �o�b�t�@�̎����쐬
	m_d3dpp.EnableAutoDepthStencil = TRUE;
	m_d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;	// 24bitZ�o�b�t�@ + 8bit�X�e���V���o�b�t�@

	//�f�o�C�X�̍쐬 - T&L HAL
	// ��D3DCREATE_MULTITHREADED	�c�@�}���`�X���b�h�ł̃f�o�C�X���������
	// ��D3DCREATE_FPU_PRESERVE		�c�@float�̐��x���������Ɉێ�����(�����x��float���g��)
	if(FAILED(m_lpD3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hWnd,D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE,&m_d3dpp, &m_lpD3DDev)))
	{
		//���s�����̂�HAL�Ŏ��s
		if(FAILED(m_lpD3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hWnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE,&m_d3dpp, &m_lpD3DDev)))
		{
			//���s�����̂�REF�Ŏ��s
			if(FAILED(m_lpD3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_REF,hWnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE,&m_d3dpp, &m_lpD3DDev)))
			{
				//���ǎ��s
				MessageBox(hWnd, "Direct3D�̏������Ɏ��s", "Direct3D������" , MB_OK | MB_ICONSTOP);
				//�I������
				return false;
			}
		}
	}

	//=======================================================
	// Caps�擾
	//=======================================================
	m_lpD3DDev->GetDeviceCaps(&m_Caps);
	
	//=======================================================
	// D3DXSPRITE�쐬
	//=======================================================
	D3DXCreateSprite(m_lpD3DDev,&m_lpSprite);

	//=======================================================
	// D3DXFONT�쐬
	//=======================================================
	D3DXCreateFont( m_lpD3DDev, 12, 0, 0, 1, FALSE, DEFAULT_CHARSET, 
                         OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, 
                         "�l�r �o�S�V�b�N", &m_lpFont );
	m_lpFont->GetDesc(&m_FontDesc);

	//=======================================================
	// �o�b�N�o�b�t�@��Z�o�b�t�@�擾
	//=======================================================
	m_lpD3DDev->GetRenderTarget(0, &m_OrgRenderTarget);
	m_lpD3DDev->GetDepthStencilSurface(&m_OrgDepthStencil);

	return true;
}

void CDirectXGraphics::Release()
{
	SAFE_RELEASE(m_OrgRenderTarget);
	SAFE_RELEASE(m_OrgDepthStencil);

	// D3DXSPRITE���
	SAFE_RELEASE(m_lpSprite);
	// D3DXFONT���
	SAFE_RELEASE(m_lpFont);

	SAFE_RELEASE(m_lpD3DDev);
	SAFE_RELEASE(m_lpD3D);
}

//================================================================================
//
// ��{�I���Ȃ��Ǝv�������_�[�X�e�[�g�̐ݒ�
//  ���ڍׁ�
//    ���C�gON�A���C�g�̐ݒ�͓K���A�@�����K���AZ����L���AZ�������ݗL���A���������[�h�A
//    �E���J�����O�A�V���O���e�N�X�`���A�t�H�OOFF�A�t�H�O�ݒ�͒��_���`�t�H�O�ݒ�E�͈͂�1�`10000�A
//    �A���t�@�u�����hON�A�X�e���V���o�b�t�@ON�A�O���[�V�F�[�f�B���O�A�e�N�X�`���A�h���b�V���O���[�h��Wrap
//================================================================================
void CDirectXGraphics::SetState()
{
	// DirectGraphics�̏ڍאݒ�
	m_lpD3DDev->SetRenderState(D3DRS_ZENABLE,TRUE);					// Z�o�b�t�@�L��
	m_lpD3DDev->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);			// Z�o�b�t�@�ɏ������ݗL��
	m_lpD3DDev->SetRenderState(D3DRS_STENCILENABLE, TRUE);
	
	m_lpD3DDev->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );		// �A���t�@�u�����h�L��
	Blend_Alpha();													// ���������[�h

	m_lpD3DDev->SetRenderState(D3DRS_NORMALIZENORMALS,TRUE);		//���_�@���̎������K��

	m_lpD3DDev->SetRenderState(D3DRS_SHADEMODE,D3DSHADE_GOURAUD);	// �O���[�V�F�[�f�B���O
	m_lpD3DDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);		// �J�����O CCW=�E���=�\�ʂ̂ݕ`��

	SeparateAlphaBlendEnable(TRUE);									// ���ʌv�Z

	// �e�N�X�`���̃��l�̃u�����f�B���O���@�̐ݒ�
	// �e�N�X�`�������������̕��@
	m_lpD3DDev->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE );    // �ȉ��̈����̐�������Z����
	m_lpD3DDev->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );    // �e�N�X�`���̐F���g�p
	m_lpD3DDev->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );    // ���_�̐F���g�p
	// �F������������@
	m_lpD3DDev->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );    // �ȉ��̈����̐�������Z����
	m_lpD3DDev->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );    // �e�N�X�`���̐F���g�p
	m_lpD3DDev->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );    // ���_�̐F���g�p

	// �e�N�X�`���̐ݒ�
	SetTextureFilter_Linear(0);

	m_lpD3DDev->SetSamplerState(0,D3DSAMP_ADDRESSU,D3DTADDRESS_WRAP);	// ���b�v���[�h
	m_lpD3DDev->SetSamplerState(0,D3DSAMP_ADDRESSV,D3DTADDRESS_WRAP);	// ���b�v���[�h

	// �~�b�v�}�b�v�ڍ׃��x����ݒ肷��B
	SetMipmapBias(-1.0f);

	// �f�B���N�V���i�����C�g�ݒ�
	SetDirectionalLight(0,
						&D3DXVECTOR3(0.5f,-1,0.3f),
						&D3DXCOLOR(1.0f,1.0f,1.0f,1),
						&D3DXCOLOR(0.0f,0.0f,0.0f,1),
						&D3DXCOLOR(1.0f,1.0f,1.0f,1));

	// �X�y�L�����L��
	m_lpD3DDev->SetRenderState(D3DRS_SPECULARENABLE, TRUE);

	// �t�H�O(������)
	m_lpD3DDev->SetRenderState(D3DRS_FOGENABLE, FALSE); // Fog��OFF
}

// LIGHT
D3DLIGHT9 CDirectXGraphics::GetLight(UINT LightNo)
{
	D3DLIGHT9 light;
	m_lpD3DDev->GetLight( LightNo, &light );	// LightNo�Ԗڂɂ��̃��C�g��ݒ�
	return light;
}

void CDirectXGraphics::SetDirectionalLight(int LightNo,D3DXVECTOR3 *vDir,D3DXCOLOR *Dif,D3DXCOLOR *Amb,D3DXCOLOR *Spe)
{
	// �f�B���N�V���i�����C�g�ݒ�
	D3DLIGHT9 light;
	ZeroMemory( &light, sizeof(D3DLIGHT9) );
	light.Type    = D3DLIGHT_DIRECTIONAL;
	light.Diffuse = *Dif;	// �f�B�q���[�Y
	light.Ambient = *Amb;	// �A���r�G���g
	light.Specular = *Spe;	// �X�y�L����
	D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction, vDir);

	m_lpD3DDev->SetLight( LightNo, &light );	// LightNo�Ԗڂɂ��̃��C�g��ݒ�
	m_lpD3DDev->LightEnable( LightNo, TRUE );	// LightNo�Ԗڂ̃��C�g��L��
}

void CDirectXGraphics::DrawSprite(CTexture* tex, D3DCOLOR color, D3DXMATRIX* mat)
{
	if(tex == nullptr)return;

	if(mat)m_lpSprite->SetTransform(mat);
	m_lpSprite->Draw(tex->GetTex(), tex->GetRect(), nullptr, nullptr, color);
}

void CDirectXGraphics::DrawSprite(CTexture* tex, int x, int y, int w, int h, D3DCOLOR color)
{
	if(tex == nullptr)return;
	CMatrix m;
	m.CreateScale(	(float)w / tex->GetInfo()->Width,
					(float)h / tex->GetInfo()->Height,
					0
				);
	m.Move((float)x,(float)y,0);

	m_lpSprite->SetTransform(&m);
	m_lpSprite->Draw(tex->GetTex(), tex->GetRect(), nullptr, nullptr, color);
}

void CDirectXGraphics::DrawFont(const char* text,  D3DCOLOR color, D3DXMATRIX* mat)
{
	if(text == nullptr)return;

	if(mat)m_lpSprite->SetTransform(mat);
	RECT rc = {0,0,0,0};
	m_lpFont->DrawText(m_lpSprite, text, -1, &rc, DT_CALCRECT, color);
	m_lpFont->DrawText(m_lpSprite, text, -1, &rc, DT_LEFT, color);
}

void CDirectXGraphics::DrawQuad(float x,float y,float w,float h,float tuCnt,float tvCnt,D3DCOLOR color)
{
	// ���W�ϊ��ςݍ��W�ƃe�N�X�`�����W
	struct VERTEX{
		float x, y, z, rhw;  // �ʒu
		float tu,tv;	// �e�N�X�`��
	};

	VERTEX v[4];
	v[0].x = x;		v[0].y = y;
	v[1].x = x+w;	v[1].y = y;
	v[2].x = x;		v[2].y = y+h;
	v[3].x = x+w;	v[3].y = y+h;

	v[0].tu = 0;
	v[0].tv = 0;
	v[1].tu = tuCnt;
	v[1].tv = 0;
	v[2].tu = 0;
	v[2].tv = tvCnt;
	v[3].tu = tuCnt;
	v[3].tv = tvCnt;

	// RHW, ���_�F�̐ݒ�
	for (int i=0; i<4; i++) {
		v[i].z = 0;
		v[i].rhw = 1;
	}

	m_lpD3DDev->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);

	m_lpD3DDev->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(VERTEX));

}
void CDirectXGraphics::DrawQuad3D(float LSize,float RSize,float TSize,float BSize,float tuCnt,float tvCnt,D3DXCOLOR color)
{
	// ���W�ƃe�N�X�`�����W
	struct VERTEX{
		float x, y, z;  // �ʒu
		float tu,tv;	// �e�N�X�`��
	};

	VERTEX v[4];
	v[0].x = -LSize;	v[0].y = -BSize;	// ����
	v[1].x = RSize;		v[1].y = -BSize;	// �E��
	v[2].x = -LSize;	v[2].y = TSize;		// ����
	v[3].x = RSize;		v[3].y = TSize;		// �E��

	v[0].tu = tuCnt;
	v[0].tv = tvCnt;
	v[1].tu = 0;
	v[1].tv = tvCnt;
	v[2].tu = tuCnt;
	v[2].tv = 0;
	v[3].tu = 0;
	v[3].tv = 0;

	// RHW, ���_�F�̐ݒ�
	for (int i=0; i<4; i++) {
		v[i].z = 0;
	}

	m_lpD3DDev->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);
	m_lpD3DDev->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(VERTEX));

}
