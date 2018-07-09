#include "../main.h"
#include "map.h"

void map::LoadMap(void) {
	if ((fp = fopen("../data/Csv/map1.csv", "r")) == NULL) {
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
			//
		}
	}
	fclose(fp);
}

void map::DrawMap(void) {
	for (int i = 0; i < MAPHEIGHT; i++) {
		for (int j = 0; j < MAPWIDTH; j++) {
				if (MapData[i][j] == 0) {
					// Land表示
				}
				else if (MapData[i][j] == 1) {
					// Load表示
				}
		}
	}
}


