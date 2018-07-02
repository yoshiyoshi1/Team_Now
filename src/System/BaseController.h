#ifndef __BaseController_h__
#define __BaseController_h__

class BaseController
{
public:
	// ���̓f�[�^
	//CVector3	m_Axis;			// ������(�A�i���O�X�e�B�b�N)
	int			m_Buttons = 0;	// �{�^��

//*********************************************
// �V���O���g������
public:
	static void CreateInstance() { new BaseController(); }
	static void DeleteInstance() { delete m_lpInstance; }
	static BaseController* GetInstance() { return m_lpInstance; }
private:
	BaseController();
	~BaseController();
	BaseController(BaseController &);
	BaseController & operator= (BaseController &);
	static BaseController *m_lpInstance;

	//*********************************************
};

#define BC BaseController::GetInstance()

// �{�^���p�萔
namespace GameButtons {
	enum {
		Acceel = 0x00000001,
		Brake = 0x00000002,
		TurnRight = 0x00000004,
		TurnLeft = 0x00000008
	};
};

#endif