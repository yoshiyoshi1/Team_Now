#ifndef __CVector3_h__
#define __CVector3_h__

namespace SimpleLib{

//============================================================================
// �R�����x�N�g���N���X
//	D3DXVECTOR3�̋@�\�g����
//============================================================================
class CVector3 : public D3DXVECTOR3{
public:
	// �R���X�g���N�^
	CVector3(){
		x = 0;
		y = 0;
		z = 0;
	}
	CVector3(float fx,float fy,float fz){
		x = fx;
		y = fy;
		z = fz;
	}
	CVector3(const D3DXVECTOR3 &In){
		x = In.x;
		y = In.y;
		z = In.z;
	}

	void Set(float fx,float fy,float fz){
		x = fx;
		y = fy;
		z = fz;
	}
	void Set(const D3DXVECTOR3 *v){
		x = v->x;
		y = v->y;
		z = v->z;
	}

	CVector3& operator=(const D3DXVECTOR3& v){
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}

	// �e���Z�q
	CVector3 operator + () const{ return D3DXVECTOR3::operator+(); }
	CVector3 operator - () const{ return D3DXVECTOR3::operator-(); }

	CVector3 operator + ( CONST D3DXVECTOR3& v) const{ return D3DXVECTOR3::operator+(v); }
	CVector3 operator - ( CONST D3DXVECTOR3& v) const{ return D3DXVECTOR3::operator-(v); }
	CVector3 operator * ( FLOAT f) const{ return D3DXVECTOR3::operator*(f); }
	CVector3 operator / ( FLOAT f) const{ return D3DXVECTOR3::operator/(f); }

	//�x�N�g�����Z
	static void Add(D3DXVECTOR3 *vOut,const D3DXVECTOR3 *v1,const D3DXVECTOR3 *v2){	// �ÓI�֐�
		D3DXVec3Add(vOut,v1,v2);
	}
	void Add(float fx,float fy,float fz){
		Add(this,this,&D3DXVECTOR3(fx,fy,fz));
	}
	void Add(const CVector3 *p){
		Add(this,this,p);
	}
	
	//�x�N�g�����Z
	static void Sub(D3DXVECTOR3 *vOut,const D3DXVECTOR3 *v1,const D3DXVECTOR3 *v2){	// �ÓI�֐�
		D3DXVec3Subtract(vOut,v1,v2);
	}
	void Sub(float fx,float fy,float fz){
		Sub(this,this,&D3DXVECTOR3(fx,fy,fz));
	}
	void Sub(const D3DXVECTOR3 *p){
		Sub(this,this,p);
	}
	
	// ����
	static float Dot(const D3DXVECTOR3 *v1,const D3DXVECTOR3 *v2){			// �ÓI�֐�
		return D3DXVec3Dot(v1,v2);
	}
	float Dot(const D3DXVECTOR3 *v1){
		return Dot(this,v1);
	}

	// �O��
	static void Cross(D3DXVECTOR3 *vOut,const D3DXVECTOR3 *v1,const D3DXVECTOR3 *v2){// �ÓI�֐�
		D3DXVec3Cross(vOut,v1,v2);
	}
	// �O�� ���� x vBack
	void CrossBack(D3DXVECTOR3 *vOut,const D3DXVECTOR3 *vBack){
		Cross(vOut,this,vBack);
	}
	// �O�� vBack x ����
	void CrossFront(D3DXVECTOR3 *vOut,const D3DXVECTOR3 *vFront){
		Cross(vOut,vFront,this);
	}
	
	// �X�J���[�{
	static void Scale(D3DXVECTOR3 *vOut,const D3DXVECTOR3 *vSrc,float s){		// �ÓI�֐�
		D3DXVec3Scale(vOut,vSrc,s);
	}
	void Scale(float s){
		Scale(this,this,s);
	}

	// ����
	static float Length(const D3DXVECTOR3 *vSrc){						// �ÓI�֐�
		return D3DXVec3Length(vSrc);
	}
	float Length(){
		return Length(this);
	}
	// ���K��
	static void Normalize(D3DXVECTOR3 *vOut,const D3DXVECTOR3 *vSrc){			// �ÓI�֐�
		D3DXVec3Normalize(vOut,vSrc);
	}
	void Normalize(){
		Normalize(this,this);
	}
	void Normalize(D3DXVECTOR3 *vOut) const{
		Normalize(vOut,this);
	}


	// �s��ŕϊ�(��]�E���W)
	static void TransformCoord(D3DXVECTOR3 *vOut,const D3DXVECTOR3 *vSrc,const D3DXMATRIX *D3DXMATRIX){	// �ÓI�֐�
		D3DXVec3TransformCoord(vOut,vSrc,D3DXMATRIX);
	}
	void TransformCoord(const D3DXMATRIX *D3DXMATRIX){
		TransformCoord(this,this,D3DXMATRIX);
	}
	void TransformCoord(D3DXVECTOR3 *vSrc,const D3DXMATRIX *D3DXMATRIX){
		TransformCoord(this,vSrc,D3DXMATRIX);
	}
	
	// �s��ŕϊ�(��]�݂̂̕ϊ�)
	static void TransformNormal(D3DXVECTOR3 *vOut,const D3DXVECTOR3 *vSrc,const D3DXMATRIX *D3DXMATRIX){// �ÓI�֐�
		D3DXVec3TransformNormal(vOut,vSrc,D3DXMATRIX);
	}
	void TransformNormal(const D3DXMATRIX *D3DXMATRIX){
		TransformNormal(this,this,D3DXMATRIX);
	}
	void TransformNormal(D3DXVECTOR3 *vOut,const D3DXMATRIX *D3DXMATRIX){
		TransformNormal(vOut,this,D3DXMATRIX);
	}

};

}

#endif
