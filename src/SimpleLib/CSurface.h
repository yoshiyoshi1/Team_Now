#ifndef __CSurface_h__
#define __CSurface_h__

namespace SimpleLib{

//==================================
// �T�[�t�F�C�X�N���X
//	����Z�o�b�t�@�̍쐬�E�Z�b�g���\�Ȃ��Ƃɏd�_��u���Ă��܂�
//==================================
class CSurface{
public:
	//==================================================================================
	// �擾
	//==================================================================================
	LPDIRECT3DSURFACE9		GetSur(){return m_lpSur;}		// �T�[�t�F�C�X�擾
	D3DSURFACE_DESC*		GetDesc(){return &m_Desc;}		// ���擾

	//==================================================================================
	// �쐬
	//==================================================================================
	// Z�o�b�t�@�Ƃ��č쐬
	BOOL CreateDepthStencil(UINT Width, UINT Height, D3DFORMAT Format = D3DFMT_D24S8, D3DMULTISAMPLE_TYPE MultiSample = D3DMULTISAMPLE_NONE, DWORD MultisampleQuality = 0, BOOL Discard = FALSE);

	//==================================================================================
	// �[�x�o�b�t�@�Ƃ��ăZ�b�g����
	//==================================================================================
	void SetDepthStencil();

	//==================================================================================
	// ���
	//==================================================================================
	void Release();

	// 
	CSurface() : m_lpSur(0){
	}
	~CSurface(){
		Release();
	}

private:
	LPDIRECT3DSURFACE9		m_lpSur;
	D3DSURFACE_DESC			m_Desc;

private:
	// �R�s�[�֎~�p
	CSurface(const CSurface& src){}
	void operator=(const CSurface& src){}
};

}
#endif