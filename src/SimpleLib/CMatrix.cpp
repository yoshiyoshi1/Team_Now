#include "SimpleLib.h"

using namespace SimpleLib;

CMatrix::CMatrix(	FLOAT _11, FLOAT _12, FLOAT _13, FLOAT _14,
					FLOAT _21, FLOAT _22, FLOAT _23, FLOAT _24,
					FLOAT _31, FLOAT _32, FLOAT _33, FLOAT _34,
					FLOAT _41, FLOAT _42, FLOAT _43, FLOAT _44 )
{
	this->_11 = _11;
	this->_12 = _12;
	this->_13 = _13;
	this->_14 = _14;
	this->_21 = _21;
	this->_22 = _22;
	this->_23 = _23;
	this->_24 = _24;
	this->_31 = _31;
	this->_32 = _32;
	this->_33 = _33;
	this->_34 = _34;
	this->_41 = _41;
	this->_42 = _42;
	this->_43 = _43;
	this->_44 = _44;
}

// �s���Z������LookWay�̕����Ɍ�����B
// �@LoockWay ��� �������������x�N�g���̃A�h���X
// �@Up ��� ������̃x�N�g���̃A�h���X
void CMatrix::SetLookAt(const D3DXVECTOR3 *LookWay,const D3DXVECTOR3 *Up)
{
	CVector3 v,vX,vY,vZ;
	CVector3 Look;

	CVector3::Normalize(&Look,LookWay);


	// �O��
	CVector3::Cross(&v,Up,&Look);
	v.Normalize();
	if(v.Length() == 0)
		v.x = 1;
	// �O�ς�Y�x�N�g���Z�o
	CVector3::Cross(&vY,&Look,&v);
	vY.Normalize();
	if(vY.Length() == 0)
		vY.y = 1;

	// �s��̉�]������ݒ�
	_11 = v.x;
	_12 = v.y;
	_13 = v.z;

	_21 = vY.x;
	_22 = vY.y;
	_23 = vY.z;

	_31 = Look.x;
	_32 = Look.y;
	_33 = Look.z;
}

// �s���Z������TargetPos�̈ʒu������悤�ɁA������B
// �@TargetPos ��� ���������W
// �@Up ��� ������̃x�N�g���̃A�h���X
void CMatrix::SetLookAtPos(const D3DXVECTOR3 *TargetPos,const D3DXVECTOR3 *Up)
{
	CVector3 v,vX,vY,vZ;
	CVector3 Look;

	// �����x�N�g��
	Look.x = TargetPos->x - _41;
	Look.y = TargetPos->y - _42;
	Look.z = TargetPos->z - _43;
	Look.Normalize();

	// �O��
	CVector3::Cross(&v,Up,&Look);
	v.Normalize();
	// �O�ς�Y�x�N�g���Z�o
	CVector3::Cross(&vY,&Look,&v);
	vY.Normalize();

	// �s��̉�]������ݒ�
	_11 = v.x;
	_12 = v.y;
	_13 = v.z;

	_21 = vY.x;
	_22 = vY.y;
	_23 = vY.z;

	_31 = Look.x;
	_32 = Look.y;
	_33 = Look.z;
}
