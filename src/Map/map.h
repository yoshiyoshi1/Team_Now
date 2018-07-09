#ifndef __map_h__ 
#define __map_h__

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

};
#endif
