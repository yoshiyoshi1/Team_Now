#ifndef __RouteSearch_h__
#define __RouteSearch_h__

class RouteSearch
{
public:
	RouteSearch();
	~RouteSearch(){}

	void Update();

	void SetData();

private:
	//-----------------------------
	// �e�X�g�f�[�^
	static const int SIZE_X = 10;
	static const int SIZE_Y = 10;
	
	int m_RouteData[SIZE_Y][SIZE_X];
	//-----------------------------
};

#endif