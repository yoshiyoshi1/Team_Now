#ifndef __CMatrix_h__
#define __CMatrix_h__

namespace SimpleLib{

//==========================================================================================================
// �s�񑀍�N���X
//	D3DXMATRIX�̋@�\�g����
//==========================================================================================================
class CMatrix : public D3DXMATRIX{
public:
	//============================================================
	// �����o�֐�
	//============================================================
	CMatrix(){
		D3DXMatrixIdentity(this);
	}
	CMatrix(const D3DXMATRIX &m){
		_11 = m._11;
		_12 = m._12;
		_13 = m._13;
		_14 = m._14;
		_21 = m._21;
		_22 = m._22;
		_23 = m._23;
		_24 = m._24;
		_31 = m._31;
		_32 = m._32;
		_33 = m._33;
		_34 = m._34;
		_41 = m._41;
		_42 = m._42;
		_43 = m._43;
		_44 = m._44;
	}
	CMatrix(FLOAT _11, FLOAT _12, FLOAT _13, FLOAT _14,
            FLOAT _21, FLOAT _22, FLOAT _23, FLOAT _24,
            FLOAT _31, FLOAT _32, FLOAT _33, FLOAT _34,
            FLOAT _41, FLOAT _42, FLOAT _43, FLOAT _44 );


	//========================================================================
	//
	// �s��u�����v�n�֐�����s����쐬���A�������Ă���(���ΓI�ω�)
	//
	//========================================================================
	// �ړ��s����u��납��v����
	void Move(float x,float y,float z)
	{
		_41 += x;
		_42 += y;
		_43 += z;
	}
	void Move(const D3DXVECTOR3 *v)
	{
		_41 += v->x;
		_42 += v->y;
		_43 += v->z;
	}
	// �ړ��s����u��O����v����
	void Move_Local(float x,float y,float z)
	{
		D3DXMATRIX TmpMat;		// ��Ɨp
		D3DXMatrixTranslation(&TmpMat,x,y,z);
		D3DXMatrixMultiply(this,&TmpMat,this);// ����
	}
	void Move_Local(const D3DXVECTOR3 *v)						// �ړ��������B���[�J�����W�n�ł̈ړ�
	{
		D3DXMATRIX TmpMat;		// ��Ɨp
		D3DXMatrixTranslation(&TmpMat,v->x,v->y,v->z);
		D3DXMatrixMultiply(this,&TmpMat,this);// ����
	}
	// ��]�s����u��납��v����
	void RotateX(float Ang)
	{
		D3DXMATRIX TmpMat;		// ��Ɨp
		D3DXMatrixRotationX(&TmpMat,ToRadian(Ang));
		D3DXMatrixMultiply(this,this,&TmpMat);// ����
	}
	void RotateY(float Ang)
	{
		D3DXMATRIX TmpMat;		// ��Ɨp
		D3DXMatrixRotationY(&TmpMat,ToRadian(Ang));
		D3DXMatrixMultiply(this,this,&TmpMat);// ����
	}
	void RotateZ(float Ang)										// Z��]������
	{
		D3DXMATRIX TmpMat;		// ��Ɨp
		D3DXMatrixRotationZ(&TmpMat,ToRadian(Ang));
		D3DXMatrixMultiply(this,this,&TmpMat);// ����
	}
	void RotateAxis(D3DXVECTOR3 *vAxis,float Ang)				// �w�莲��]������
	{
		D3DXMATRIX TmpMat;		// ��Ɨp
		D3DXMatrixRotationAxis(&TmpMat,vAxis,ToRadian(Ang));
		D3DXMatrixMultiply(this,this,&TmpMat);// ����
	}

	// ��]�s����u��O����v����
	void RotateX_Local(float Ang)								// X��]������ ���[�J�����W�n�ł̉�]
	{
		D3DXMATRIX TmpMat;		// ��Ɨp
		D3DXMatrixRotationX(&TmpMat,ToRadian(Ang));
		D3DXMatrixMultiply(this,&TmpMat,this);// ����
	}
	void RotateY_Local(float Ang)								// Y��]������ ���[�J�����W�n�ł̉�]
	{
		D3DXMATRIX TmpMat;		// ��Ɨp
		D3DXMatrixRotationY(&TmpMat,ToRadian(Ang));
		D3DXMatrixMultiply(this,&TmpMat,this);// ����
	}
	void RotateZ_Local(float Ang)								// Z��]������ ���[�J�����W�n�ł̉�]
	{
		D3DXMATRIX TmpMat;		// ��Ɨp
		D3DXMatrixRotationZ(&TmpMat,ToRadian(Ang));
		D3DXMatrixMultiply(this,&TmpMat,this);// ����
	}
	void RotateAxis_Local(D3DXVECTOR3 *vAxis,float Ang)			// �w�莲��]������ ���[�J�����W�n�ł̉�]
	{
		D3DXMATRIX TmpMat;		// ��Ɨp
		D3DXMatrixRotationAxis(&TmpMat,vAxis,ToRadian(Ang));
		D3DXMatrixMultiply(this,&TmpMat,this);// ����
	}
	// �X�P�[�����O�s����u��납��v����
	void Scale(float x,float y,float z)							// �X�P�[�����O������
	{
		D3DXMATRIX TmpMat;		// ��Ɨp
		D3DXMatrixScaling(&TmpMat,x,y,z);
		D3DXMatrixMultiply(this,this,&TmpMat);// ����
	}
	void Scale(const D3DXVECTOR3 *v)
	{															// �X�P�[�����O������
		D3DXMATRIX TmpMat;		// ��Ɨp
		D3DXMatrixScaling(&TmpMat,v->x,v->y,v->z);
		D3DXMatrixMultiply(this,this,&TmpMat);// ����
	}
	// �X�P�[�����O�s����u��O����v����
	void Scale_Local(float x,float y,float z)					// �X�P�[�����O������ ���[�J�����W�n�ł̊g��
	{
		D3DXMATRIX TmpMat;		// ��Ɨp
		D3DXMatrixScaling(&TmpMat,x,y,z);
		D3DXMatrixMultiply(this,&TmpMat,this);// ����
	}
	void Scale_Local(const D3DXVECTOR3 *v)					// �X�P�[�����O������ ���[�J�����W�n�ł̊g��
	{
		D3DXMATRIX TmpMat;		// ��Ɨp
		D3DXMatrixScaling(&TmpMat,v->x,v->y,v->z);
		D3DXMatrixMultiply(this,&TmpMat,this);// ����
	}

	//========================================================================
	//
	// �s��u�쐬�E����v�n�֐�����s��̓��e�𒼐ڏ㏑���Ȃǂ̑��������֐�(��ΓI�ω�)
	//
	//========================================================================
	// �P�ʍs��쐬
	void CreateIdentity()
	{
		D3DXMatrixIdentity(this);
	}
	void CreateIdentityRotate()
	{
		_11 = 1;_12 = 0;_13=0;_14 = 0;
		_21 = 0;_22 = 1;_23=0;_24 = 0;
		_31 = 0;_32 = 0;_33=1;_34 = 0;
	}
	static void CreateIdentity(D3DXMATRIX *m){
		D3DXMatrixIdentity(m);
	}
	// �t�s��쐬
	void CreateInverse()
	{
		D3DXMatrixInverse(this,nullptr,this);
	}
	void CreateInverse(D3DXMATRIX *destMat)
	{
		D3DXMatrixInverse(destMat, nullptr,this);
	}
	static void CreateInverse(D3DXMATRIX *mOut,float *pDeterminant,const D3DXMATRIX *mIn){
		D3DXMatrixInverse(mOut,pDeterminant,mIn);
	}
	// �ړ��s��쐬
	void CreateMove(float x,float y,float z)
	{
		D3DXMatrixTranslation(this,x,y,z);
	}
	void CreateMove(const D3DXVECTOR3 *v)
	{
		D3DXMatrixTranslation(this,v->x,v->y,v->z);
	}
	static void CreateMove(D3DXMATRIX *mOut,float x,float y,float z)
	{
		D3DXMatrixTranslation(mOut,x,y,z);
	}
	static void CreateMove(D3DXMATRIX *mOut,const D3DXVECTOR3 *v)
	{
		D3DXMatrixTranslation(mOut,v->x,v->y,v->z);
	}
	// X��]�s��쐬
	void CreateRotateX(float Ang)
	{
		D3DXMatrixRotationX(this,ToRadian(Ang));
	}
	static void CreateRotateX(D3DXMATRIX *mOut,float Ang)
	{
		D3DXMatrixRotationX(mOut,ToRadian(Ang));
	}
	// Y��]�s��쐬
	void CreateRotateY(float Ang)
	{
		D3DXMatrixRotationY(this,ToRadian(Ang));
	}
	static void CreateRotateY(D3DXMATRIX *mOut,float Ang)
	{
		D3DXMatrixRotationY(mOut,ToRadian(Ang));
	}
	// Z��]�s��쐬
	void CreateRotateZ(float Ang)
	{
		D3DXMatrixRotationZ(this,ToRadian(Ang));
	}
	static void CreateRotateZ(D3DXMATRIX *mOut,float Ang)
	{
		D3DXMatrixRotationZ(mOut,ToRadian(Ang));
	}
	// �C�ӎ���]�s����쐬
	void CreateRotateAxis(const D3DXVECTOR3 *vAxis,float Ang)
	{
		D3DXMatrixRotationAxis(this,vAxis,ToRadian(Ang));
	}
	static void CreateRotateAxis(D3DXMATRIX *mOut,const D3DXVECTOR3 *vAxis,float Ang)
	{
		D3DXMatrixRotationAxis(mOut,vAxis,ToRadian(Ang));
	}
	// �X�P�[�����O�s��쐬
	void CreateScale(float x,float y,float z)						
	{
		D3DXMatrixScaling(this,x,y,z);
	}
	void CreateScale(const D3DXVECTOR3 *v)
	{
		D3DXMatrixScaling(this,v->x,v->y,v->z);
	}
	static void CreateScale(D3DXMATRIX *mOut,float x,float y,float z)
	{
		D3DXMatrixScaling(mOut,x,y,z);
	}
	static void CreateScale(D3DXMATRIX *mOut,const D3DXVECTOR3 *v)
	{
		D3DXMatrixScaling(mOut,v->x,v->y,v->z);
	}
	// �w�������Z�����������s����쐬
	void SetLookAt(const D3DXVECTOR3 *LookWay, const D3DXVECTOR3 *Up);			// LookWay�̕����Ɍ������s��ɂ���BUp�͏�ƂȂ�������w��B�������łȂ��A���ډ�]�������㏑�����܂��B
	void SetLookAtPos(const D3DXVECTOR3 *TargetPos, const D3DXVECTOR3 *Up);		// ��������Target�̈ʒu�����������̍s��ɂ���BUp�͏�ƂȂ�������w��B�������łȂ��A���ډ�]�������㏑�����܂��B

	// ���W�ݒ�
	void SetPos(float fx,float fy,float fz){
		_41 = fx;
		_42 = fy;
		_43 = fz;
	}
	void SetPos(const D3DXVECTOR3 *v){
		_41 = v->x;
		_42 = v->y;
		_43 = v->z;
	}

	//========================================================================
	// �ϊ�
	//========================================================================
	void ToQuaternion(D3DXQUATERNION *out){									// �s�񂩂�N�H�[�^�j�I����
		D3DXQuaternionRotationMatrix(out,this);
	}
	static void ToQuaternion(D3DXQUATERNION *out,const D3DXMATRIX *mIn){		// �s�񂩂�N�H�[�^�j�I����
		D3DXQuaternionRotationMatrix(out,mIn);
	}

	//============================================================================
	// ���擾
	//============================================================================
	// ���W���x�N�g���^�Ŏ擾
	CVector3& GetPos()
	{
		return *(CVector3*)&_41;
	}
	// X�����x�N�g���^�Ŏ擾
	CVector3& GetXAxis()
	{
		return *(CVector3*)&_11;
	}
	// Y�����x�N�g���^�Ŏ擾
	CVector3& GetYAxis()
	{
		return *(CVector3*)&_21;
	}
	// Z�����x�N�g���^�Ŏ擾
	CVector3& GetZAxis()
	{
		return *(CVector3*)&_31;
	}
};

}

#endif
