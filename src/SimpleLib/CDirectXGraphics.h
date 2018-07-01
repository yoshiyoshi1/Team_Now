#ifndef __CDirectXGraphics_h__
#define __CDirectXGraphics_h__

namespace SimpleLib{

//==========================================================================================================
//
// �Ȉ�Direct3D����N���X
//	Direct3D9�ɕK�v�ȕϐ���A�悭���鑀����֐������Ă��܂��B
//
//==========================================================================================================
class CDirectXGraphics{
public:
	//=============================================
	// �擾�n
	//=============================================
	LPDIRECT3D9				GetD3D(){return m_lpD3D;}				// D3D�I�u�W�F�N�g�擾
	LPDIRECT3DDEVICE9		GetDev(){return m_lpD3DDev;}			// D3D�f�o�C�X�擾
	LPD3DXSPRITE			GetSprite(){return m_lpSprite;}			// D3DSprite�擾
	LPD3DXFONT				GetFont(){return m_lpFont;}				// D3DFont�擾
	D3DPRESENT_PARAMETERS*	GetD3DPP(){return &m_d3dpp;}			// D3D�p�����[�^�擾
	D3DLIGHT9				GetLight(UINT LightNo);					// ���C�g���擾
	D3DCAPS9*				GetCaps(){return &m_Caps;}				// �f�o�C�X���擾

	int						GetRezoW(){return m_d3dpp.BackBufferWidth;}	// X�𑜓x�擾(��ʂ̕�)
	int						GetRezoH(){return m_d3dpp.BackBufferHeight;}// Y�𑜓x�擾(��ʂ̍�)

	//=============================================
	// Direct3D������
	//=============================================
	bool Init(HWND hWnd, int Width, int Height, D3DFORMAT Format, bool FullScreen);
	// Direct3D�̊�{�I�ȃ����_�[�X�e�[�g���̐ݒ�
	void SetState();

	//=============================================
	// Direct3D���
	//=============================================
	void Release();

	//=============================================
	// �����_�[�^�[�Q�b�g�EZ�o�b�t�@�֌W
	//=============================================
	// �N���A
	void Clear(bool bRenderTarget, bool bZBuffer, bool bStencilBuffer, D3DCOLOR color = 0xFFFFFFFF, float z = 1.0f, DWORD stencil = 0){
		DWORD flags = 0;
		if(bRenderTarget)	flags |= D3DCLEAR_TARGET;
		if(bZBuffer)		flags |= D3DCLEAR_ZBUFFER;
		if(bStencilBuffer)	flags |= D3DCLEAR_STENCIL;

		m_lpD3DDev->Clear(0, nullptr, flags, color, z, stencil);
	}
	// �f�t�H���g�̃o�b�N�o�b�t�@���Z�b�g�B
	void ResetRenderTarget(){
		m_lpD3DDev->SetRenderTarget(0,m_OrgRenderTarget);
		// �c���1�`3�͉���
		m_lpD3DDev->SetRenderTarget(1, nullptr);
		m_lpD3DDev->SetRenderTarget(2, nullptr);
		m_lpD3DDev->SetRenderTarget(3, nullptr);
	}
	// �f�t�H���g��Z�o�b�t�@���Z�b�g�B
	void ResetDepthStencil(){
		m_lpD3DDev->SetDepthStencilSurface(m_OrgDepthStencil);
	}
	// �����_�[�^�[�Q�b�g�ύX
	void SetRenderTarget(DWORD Idx, LPDIRECT3DTEXTURE9 texture){
		if(texture == nullptr){
			m_lpD3DDev->SetRenderTarget(Idx, nullptr);
		}
		else{
			LPDIRECT3DSURFACE9 rt;
			if (SUCCEEDED(texture->GetSurfaceLevel(0, &rt))) {
				m_lpD3DDev->SetRenderTarget(Idx, rt);
				rt->Release();
			}
		}
	}
	// Z�o�b�t�@�ύX
	void SetDepthStencil(LPDIRECT3DSURFACE9 depth_stencil){
		m_lpD3DDev->SetDepthStencilSurface(depth_stencil);
	}

	// ���s�����쐬�E�ݒ�
	void SetDirectionalLight(int LightNo,D3DXVECTOR3 *vDir,D3DXCOLOR *Dif,D3DXCOLOR *Amb,D3DXCOLOR *Spe);

	//============================================================
	// �����_�[�X�e�[�g�ݒ�n
	//============================================================
	// ���C�e�B���O�L������
	void LightEnable(BOOL bl){
		m_lpD3DDev->SetRenderState(D3DRS_LIGHTING,bl);
	}
	// Z�o�b�t�@����L������
	void ZEnable(BOOL bl){
		m_lpD3DDev->SetRenderState(D3DRS_ZENABLE,bl);
	}
	// Z�o�b�t�@�������ݗL������
	void ZWriteEnable(BOOL bl){
		m_lpD3DDev->SetRenderState(D3DRS_ZWRITEENABLE,bl);
	}
	// �J�����O���[�h�ݒ� �ʏ��D3DCULL_CCW �J�����O���Ȃ��ꍇ��D3DCULL_NONE
	void CullMode(DWORD Mode){
		m_lpD3DDev->SetRenderState(D3DRS_CULLMODE,Mode);
	}
	// �A���t�@�u�����h�L��
	void AlphaBlendEnable(BOOL bl){
		m_lpD3DDev->SetRenderState(D3DRS_ALPHABLENDENABLE,bl);
	}
	// �������`��ݒ�
	void Blend_Alpha(){
		m_lpD3DDev->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD );
		m_lpD3DDev->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
		m_lpD3DDev->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	}
	// ���Z�����`��ݒ�
	void Blend_Add(){
		m_lpD3DDev->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD );
		m_lpD3DDev->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		m_lpD3DDev->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE);
	}
	// �����_�����O�^�[�Q�b�g�ʃA���t�@�ݒ�
	void SeparateAlphaBlendEnable(BOOL enable){
		m_lpD3DDev->SetRenderState( D3DRS_SEPARATEALPHABLENDENABLE, enable );
		if(enable){
			m_lpD3DDev->SetRenderState( D3DRS_BLENDOPALPHA, D3DBLENDOP_ADD );
			m_lpD3DDev->SetRenderState( D3DRS_SRCBLENDALPHA, D3DBLEND_ONE );
			m_lpD3DDev->SetRenderState( D3DRS_DESTBLENDALPHA, D3DBLEND_INVSRCALPHA );
		}
	}
	//========================================================================
	// �T���v��
	//========================================================================
	// �e�N�X�`����Ԃ���`��
	void SetTextureFilter_Linear(DWORD SamplerStageIndex)
	{
		m_lpD3DDev->SetSamplerState(SamplerStageIndex,D3DSAMP_MINFILTER,D3DTEXF_LINEAR);
		m_lpD3DDev->SetSamplerState(SamplerStageIndex,D3DSAMP_MAGFILTER,D3DTEXF_LINEAR);
		m_lpD3DDev->SetSamplerState(SamplerStageIndex,D3DSAMP_MIPFILTER,D3DTEXF_LINEAR);
	}
	// �e�N�X�`����Ԃ𖳂���
	void SetTextureFilter_Point(DWORD SamplerStageIndex)
	{
		m_lpD3DDev->SetSamplerState(SamplerStageIndex,D3DSAMP_MINFILTER,D3DTEXF_POINT);
		m_lpD3DDev->SetSamplerState(SamplerStageIndex,D3DSAMP_MAGFILTER,D3DTEXF_POINT);
		m_lpD3DDev->SetSamplerState(SamplerStageIndex,D3DSAMP_MIPFILTER,D3DTEXF_NONE);
	}
	// �~�b�v�}�b�v�ڍדx�ݒ�
	void SetMipmapBias(float fVal){
		m_lpD3DDev->SetSamplerState( 0, D3DSAMP_MIPMAPLODBIAS,*((DWORD*)&fVal) );
	}
	// Wrap���[�h
	void SetAddressU_Wrap(DWORD SamplerStageIndex){
		m_lpD3DDev->SetSamplerState(SamplerStageIndex, D3DSAMP_ADDRESSU,D3DTADDRESS_WRAP);
	}
	void SetAddressV_Wrap(DWORD SamplerStageIndex){
		m_lpD3DDev->SetSamplerState(SamplerStageIndex, D3DSAMP_ADDRESSV,D3DTADDRESS_WRAP);
	}
	// Clamp���[�h
	void SetAddressU_Clamp(DWORD SamplerStageIndex){
		m_lpD3DDev->SetSamplerState(SamplerStageIndex, D3DSAMP_ADDRESSU,D3DTADDRESS_CLAMP);
	}
	void SetAddressV_Clamp(DWORD SamplerStageIndex){
		m_lpD3DDev->SetSamplerState(SamplerStageIndex, D3DSAMP_ADDRESSV,D3DTADDRESS_CLAMP);
	}

	//========================================================================
	// D3DXSprite
	//========================================================================
	// �X�v���C�g�`��J�n
	BOOL BeginSprite(DWORD Flags=D3DXSPRITE_ALPHABLEND){
		HRESULT hr = m_lpSprite->Begin(Flags);
		if(hr == D3D_OK)return TRUE;

		return FALSE;
	}
	// �X�v���C�g�`��I��
	void EndSprite(){
		m_lpSprite->End();
	}
	// �X�v���C�g�`�� ��BeginSprite()�`EndSprite()�̊Ԃŏ�������
	void DrawSprite(CTexture* tex, D3DCOLOR color, D3DXMATRIX* mat);
	void DrawSprite(CTexture* tex, int x, int y, int w, int h, D3DCOLOR color);	// ���W�A���A�����w��Version
	void DrawFont(const char* text,  D3DCOLOR color, D3DXMATRIX* mat);

	//========================================================================
	// 2D�`��̕`��ݒ�p
	//========================================================================
	void Begin2DState(){
		LightEnable(FALSE);
		ZEnable(FALSE);
		ZWriteEnable(FALSE);
		SetAddressU_Clamp(0);
		SetAddressV_Clamp(0);
	}
	void End2DState(){
		LightEnable(TRUE);
		ZEnable(TRUE);
		ZWriteEnable(TRUE);
		SetAddressU_Wrap(0);
		SetAddressV_Wrap(0);
	}

	//========================================================================
	// �ȈՕ`��p
	//========================================================================
	// 2D�̎l�p�`��`��
	void DrawQuad(float x, float y, float w, float h, float tuCnt = 1, float tvCnt = 1, D3DCOLOR color = 0xFFFFFFFF);
	// 3D�̎l�p�`��`��
	void DrawQuad3D(float LSize, float RSize, float TSize, float BSize, float tuCnt = 1, float tvCnt = 1, D3DXCOLOR color = 0xFFFFFFFF);


private:

	IDirect3D9*					m_lpD3D;			// D3D�I�u�W�F�N�g
	IDirect3DDevice9*			m_lpD3DDev;			// D3D�f�o�C�X
	D3DPRESENT_PARAMETERS		m_d3dpp;			// �ڍאݒ�
	LPD3DXSPRITE				m_lpSprite;			// D3DXSPRITE
	LPD3DXFONT					m_lpFont;			// D3DXFONT
	D3DXFONT_DESC				m_FontDesc;			// ���̃t�H���g�̏��
	D3DCAPS9					m_Caps;				// �f�o�C�X�̏��

	LPDIRECT3DSURFACE9			m_OrgRenderTarget;	// �f�t�H���g�̃o�b�N�o�b�t�@
	LPDIRECT3DSURFACE9			m_OrgDepthStencil;	// �f�t�H���g�̐[�x(Z)�o�b�t�@

// �V���O���g���p
public:

	CDirectXGraphics() :
		m_lpD3D(0),m_lpD3DDev(0),m_lpSprite(0),m_lpFont(0),m_OrgRenderTarget(0),m_OrgDepthStencil(0)
	{
	}

	static CDirectXGraphics &getInstance(){
		static CDirectXGraphics Instance;
		return Instance;
	}

};

// �ȒP�ɃA�N�Z�X�ł���悤�ɂ��邽�߂̃}�N��
#define cdg CDirectXGraphics::getInstance()



}
#endif
