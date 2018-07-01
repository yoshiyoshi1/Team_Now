#ifndef __CTexture_h__
#define __CTexture_h__

namespace SimpleLib{

//==============================================================================================
// �e�N�X�`���N���X
//	�e�N�X�`���̓ǂݍ��݁ART�e�N�X�`���̍쐬�E�Z�b�g�Ȃǂ��\
//�@����͎����ōs����
//==============================================================================================
class CTexture{
public:
	//===============================================================================================
	// ���擾
	//===============================================================================================
	LPDIRECT3DTEXTURE9	GetTex(){return m_lpTex;}	// �e�N�X�`���擾
	LPDIRECT3DSURFACE9	GetSur(){return m_lpSur;}	// �T�[�t�F�C�X�擾
	RECT*				GetRect(){return &m_rc;}	// RECT�擾
	std::string			GetName(){return m_strName;}// �t�@�C����
	D3DXIMAGE_INFO*		GetInfo(){return &m_Info;}	// ���

	//===============================================================================================
	// �ǂݍ��݁E�쐬
	//===============================================================================================

	// �ȈՔŃt�@�C������e�N�X�`���ǂݍ���
	// [����] nonPow2 �c �ǂݍ��񂾃e�N�X�`����2�ׂ̂���Ɋg�k���Ȃ��悤�ɂ���
	BOOL LoadTexture(LPCTSTR pSrcFile, bool nonPow2 = false);

	// �t�@�C������e�N�X�`���ǂݍ���(�g��)
	// ������D3DXCreateTextureFromFileEx()�Ƃقړ���
	BOOL LoadTextureEx(
						LPCTSTR pSrcFile,
						UINT Width,
						UINT Height,
						UINT MipLevels,
						DWORD Usage,
						D3DFORMAT Format,
						D3DPOOL Pool,
						DWORD Filter,
						DWORD MipFilter,
						D3DCOLOR ColorKey,
						PALETTEENTRY *pPalette
						);

	// �e�N�X�`���쐬
	BOOL CreateTexture(	
						UINT Width,
						UINT Height,
						UINT MipLevels,
						DWORD Usage,
						D3DFORMAT Format,
						D3DPOOL Pool
						);

	// �����_�[�^�[�Q�b�g�e�N�X�`���Ƃ��č쐬
	BOOL CreateRenderTarget(UINT Width,	UINT Height, D3DFORMAT Format = D3DFMT_A8R8G8B8){
		return CreateTexture(Width, Height, 1, D3DUSAGE_RENDERTARGET, Format, D3DPOOL_DEFAULT);
	}

	//===============================================================================================
	// �e�N�X�`�����f�o�C�X�ɐݒ�
	//===============================================================================================
	void SetTexture(DWORD StageNo=0);

	//===============================================================================================
	// ���
	//===============================================================================================
	void Release();
	
	//===============================================================================================
	// �����_�[�^�[�Q�b�g�ɐݒ�
	//===============================================================================================
	HRESULT SetRenderTarget(DWORD Index=0);

	//===============================================================================================
	// ���ډ��H
	//===============================================================================================
	template<class T>
	bool Fill(T fill, DWORD LockFlag=0);	// �h��Ԃ�

	// 
	CTexture();
	~CTexture();

private:
	LPDIRECT3DTEXTURE9	m_lpTex;		// �e�N�X�`��
	LPDIRECT3DSURFACE9	m_lpSur;		// �T�[�t�F�C�X
	D3DXIMAGE_INFO		m_Info;			// ���
	RECT				m_rc;			// RECT
	std::string			m_strName;		// �t�@�C����

private:
	// �R�s�[�֎~�p
	CTexture(const CTexture& src){}
	void operator=(const CTexture& src){}
};



// 
template<class T>
bool CTexture::Fill(T fill,DWORD LockFlag)
{
	D3DLOCKED_RECT LockedRect;
	// ���b�N���āA�s�N�Z���̐擪�A�h���X�擾
	if(SUCCEEDED(m_lpTex->LockRect(0, &LockedRect, nullptr, LockFlag))){
		//==================================
		//�����ŉ摜�f�[�^��]��
		//==================================
		T* p1 = (T*)LockedRect.pBits;
		T pitch = LockedRect.Pitch / sizeof(T);
		for ( UINT y = 0; y < m_Info.Height ; y++ )
		{
			for ( UINT x = 0; x < m_Info.Width; x++ )
			{
				p1[x] = fill;
			}
			p1 += pitch;    //���̍s
		}
	
		m_lpTex->UnlockRect(0);
		return true;
	}
	return false;
}

}

#endif
