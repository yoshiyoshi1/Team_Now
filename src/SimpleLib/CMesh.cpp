#include "SimpleLib.h"

using namespace SimpleLib;

// �R���X�g���N�^
CMesh::CMesh()
{
	m_lpMesh = nullptr;
	m_MaterialCnt = 0;
	m_Textures = nullptr;
	m_Materials = nullptr;
	m_lpAdjacency = nullptr;
}
// �f�X�g���N�^
CMesh::~CMesh()
{
	Release();
}

BOOL CMesh::LoadXFile(LPDIRECT3DDEVICE9 lpD3DDev,const char *lpFileName)
{
	// �p�X�A�t�@�C��������
	std::string Path;
	char szDir  [_MAX_PATH]; 
	char szFname[_MAX_FNAME]; 
	char szExt  [_MAX_EXT]; 
	_splitpath( lpFileName, nullptr, szDir, szFname, szExt);
	Path = szDir;
	m_FileName = szFname;
	m_FileName += szExt;

	HRESULT hr;

	LPD3DXBUFFER	pD3DXMtrlBuffer;

	// X�t�@�C���ǂݍ���
	DWORD mateNum;
	hr = D3DXLoadMeshFromX( lpFileName, 
							D3DXMESH_MANAGED, 
							lpD3DDev, 
							&m_lpAdjacency, 
							&pD3DXMtrlBuffer, // �}�e���A���f�[�^���i�[���邽�߂̕ϐ����w��
							nullptr,
							&mateNum, // �}�e���A�������i�[���邽�߂̕ϐ����w��
							&m_lpMesh);	// ���b�V���f�[�^���i�[���邽�߂̕ϐ����w��
	if(FAILED(hr)) return FALSE;

	// �}�e���A����
	m_MaterialCnt = mateNum;
	// pD3DXMtrlBuffer ����A������e�N�X�`���[�̏���ǂݎ��
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();

	// ���b�V���̃}�e���A���̑����Ɋ�Â��āA�}�e���A���z����쐬
	m_Textures = new CTexture[mateNum];
	m_Materials = new D3DMATERIAL9[mateNum];

	// �}�e���A���R�s�[�A�e�N�X�`���ǂݍ���
	std::string strTexFile;
	for(DWORD i=0; i<mateNum; i++ ){
		// �ގ�
		m_Materials[i] = d3dxMaterials[i].MatD3D;			// �����̃R�s�[
		m_Materials[i].Ambient = m_Materials[i].Diffuse;	// Ambient��Diffuse�̃R�s�[���g�p

		// �e�N�X�`����
		strTexFile = Path;
		if(d3dxMaterials[i].pTextureFilename)strTexFile += d3dxMaterials[i].pTextureFilename;

		// �e�N�X�`���ǂݍ���
		m_Textures[i].LoadTexture(strTexFile.c_str());
	}

	// ��Ɨp�}�e���A�� �o�b�t�@�J��
	SAFE_RELEASE(pD3DXMtrlBuffer);

	return TRUE;
}

void CMesh::Release()
{
	// �S�}�e���A�����
	for(int i=0;i<m_MaterialCnt;i++){
		m_Textures[i].Release();
	}
	m_MaterialCnt = 0;

	SAFE_DELETE_ARRAY(m_Textures);
	SAFE_DELETE_ARRAY(m_Materials);

	// �אږʃf�[�^�폜
	SAFE_RELEASE(m_lpAdjacency);

	// ���b�V�� �I�u�W�F�N�g���
	SAFE_RELEASE(m_lpMesh);

	m_FileName = "";
}

void CMesh::Draw()
{
	// �}�e���A���̐��Ԃ񃋁[�v
	for(int i=0; i < m_MaterialCnt; i++ ){
		// i�Ԗڂ̃}�e���A����ݒ�
		cdg.GetDev()->SetMaterial( &m_Materials[i] );
		// i�Ԗڂ̃e�N�X�`����ݒ�
		cdg.GetDev()->SetTexture( 0, m_Textures[i].GetTex() );

		// i�Ԗڂ̃}�e���A���̃��b�V����`��
		m_lpMesh->DrawSubset( i );
	}
}
