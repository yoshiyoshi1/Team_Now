#include "../main.h"
#include "map.h"

void map::LoadMap(void) {
	if ((fp = fopen("../data/csv/map1.txt", "r")) == NULL) {
		MessageBox(APP.m_hWnd, "マップ読み込みミス", "", MB_OK);
	}

	for (int i = 0; i < MAPHEIGHT; i++) {
		for (int j = 0; j < MAPWIDTH; j++) {
			fscanf(fp, "%d,", &MapData[i][j]);
		}
	}

	//LoadMesh(&xGlound00, "data/model/Land.x");
	//LoadMesh(&xGlound01, "data/model/Load.x");

	for (int i = 0; i < MAPHEIGHT; i++) {
		for (int j = 0; j < MAPWIDTH; j++) {
			D3DXMatrixTranslation(&mGlound[i][j], j*2.0f, 0.0f, -i * 2.0f);
		}
	}
	fclose(fp);
}

void map::DrawMap(void) {
	for (int i = 0; i < MAPHEIGHT; i++) {
		for (int j = 0; j < MAPWIDTH; j++) {
			//画面外のブロックを表示しないためのif
			//if (mTeapot._41 + 80.0f > mGlound[i][j]._41 && mTeapot._41 - 80.0f < mGlound[i][j]._41) {
				if (MapData[i][j] == 0) {
					cdg.GetDev()->SetTransform(D3DTS_WORLD, &mGlound[i][j]);
					//DrawMesh(&xGlound00);
				}
				else if (MapData[i][j] == 1) {
					cdg.GetDev()->SetTransform(D3DTS_WORLD, &mGlound[i][j]);
					//DrawMesh(&xGlound01);
				}
			//}
		}
	}
}


