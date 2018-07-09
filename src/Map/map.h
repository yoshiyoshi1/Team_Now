#ifndef __map_h__ 
#define __map_h__

class vertex {
	struct VERTEX {
		D3DXVECTOR3 Pos;
		D3DCOLOR Color;
		D3DXVECTOR2 Tex;
	};
};

class xfile {
	struct XFILE {
		LPD3DXMESH lpMesh;		//メッシュの形のデータ
		DWORD NumMaterial;		//マテリアルの個数
		D3DMATERIAL9 *Mat;		//マテリアルのデータ
		LPDIRECT3DTEXTURE9 *Tex;	//テクスチャのデータ
	};
};
 
class map {
private:
	const int		MAPWIDTH = 80;
	const int		MAPHEIGHT = 80;

public:

	void LoadMap(void);
	void DrawMap(void);

	FILE* fp;
	int MapData[80][80];
	int ret;

	XFILE xGlound00;
	XFILE xGlound01;
	CMatrix mGlound[80][80];

	void DrawMesh(struct XFILE *XFile) {
		for (DWORD i = 0; i < XFile->NumMaterial; i++) {
			cdg.GetDev()->SetMaterial(&(XFile->Mat[i]));
			cdg.GetDev()->SetTexture(0, XFile->Tex[i]);
			XFile->lpMesh->DrawSubset(i);//i番目のグループを表示
		}
	}
	/*void LoadMesh(struct XFILE *XFile,const char FName[]) {
		LPD3DXBUFFER lpD3DXBuffer;

		D3DXLoadMeshFromX(FName, D3DXMESH_MANAGED, cdg.GetDev(), NULL, &lpD3DXBuffer, NULL, &(XFile->NumMaterial), &(XFile->lpMesh));

		XFile->Mat = new D3DMATERIAL9[XFile->NumMaterial];
		XFile->Tex = new LPDIRECT3DTEXTURE9[XFile->NumMaterial];

		D3DXMATERIAL* D3DXMat = (D3DXMATERIAL*)lpD3DXBuffer->GetBufferPointer();

		DWORD i;
		for (i = 0; i<XFile->NumMaterial; i++) {
			XFile->Mat[i] = D3DXMat[i].MatD3D;
			XFile->Mat[i].Ambient = XFile->Mat[i].Diffuse;
			if (FAILED(D3DXCreateTextureFromFile(cdg.GetDev(), D3DXMat[i].pTextureFilename, &(XFile->Tex[i])))) {
				XFile->Tex[i] = NULL;
			}
		}

		lpD3DXBuffer->Release();
	}*/
	void ReleaseMesh(struct XFILE *XFile) {
		if (XFile->lpMesh != NULL) {
			DWORD i;

			delete[] XFile->Mat;
			for (i = 0; i<XFile->NumMaterial; i++) {
				if (XFile->Tex[i] != NULL) {
					XFile->Tex[i]->Release();
					XFile->Tex[i] = NULL;
				}
			}
			delete[] XFile->Tex;
			XFile->lpMesh->Release();

			XFile->lpMesh = NULL;
		}
	}

};
#endif
