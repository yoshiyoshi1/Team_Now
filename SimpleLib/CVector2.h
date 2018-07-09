#ifndef __CVector2_h__
#define __CVector2_h__

namespace SimpleLib{

//============================================================================
// �R�����x�N�g���N���X
//	D2DXVECTOR2�̋@�\�g����
//============================================================================
class CVector2 : public D3DXVECTOR2{
public:
	// �R���X�g���N�^
	CVector2(){
		x = 0;
		y = 0;
	}
	CVector2(float fx,float fy,float fz){
		x = fx;
		y = fy;
	}
	CVector2(const D3DXVECTOR2 &In){
		x = In.x;
		y = In.y;
	}

	void Set(float fx,float fy,float fz){
		x = fx;
		y = fy;
	}
	void Set(const D3DXVECTOR2 *v){
		x = v->x;
		y = v->y;
	}

	CVector2& operator=(const D3DXVECTOR2& v){
		x = v.x;
		y = v.y;
		return *this;
	}

	// �e���Z�q
	CVector2 operator + () const{ return D3DXVECTOR2::operator+(); }
	CVector2 operator - () const{ return D3DXVECTOR2::operator-(); }

	CVector2 operator + ( CONST D3DXVECTOR2& v) const{ return D3DXVECTOR2::operator+(v); }
	CVector2 operator - ( CONST D3DXVECTOR2& v) const{ return D3DXVECTOR2::operator-(v); }
	CVector2 operator * ( FLOAT f) const{ return D3DXVECTOR2::operator*(f); }
	CVector2 operator / ( FLOAT f) const{ return D3DXVECTOR2::operator/(f); }

	//�x�N�g�����Z
	static void Add(D3DXVECTOR2 *vOut,const D3DXVECTOR2 *v1,const D3DXVECTOR2 *v2){	// �ÓI�֐�
		D3DXVec2Add(vOut,v1,v2);
	}
	void Add(float fx,float fy){
		Add(this,this,&D3DXVECTOR2(fx,fy));
	}
	void Add(const CVector2 *p){
		Add(this,this,p);
	}
	
	//�x�N�g�����Z
	static void Sub(D3DXVECTOR2 *vOut,const D3DXVECTOR2 *v1,const D3DXVECTOR2 *v2){	// �ÓI�֐�
		D3DXVec2Subtract(vOut,v1,v2);
	}
	void Sub(float fx,float fy){
		Sub(this,this,&D3DXVECTOR2(fx,fy));
	}
	void Sub(const D3DXVECTOR2 *p){
		Sub(this,this,p);
	}
	
	// �X�J���[�{
	static void Scale(D3DXVECTOR2 *vOut,const D3DXVECTOR2 *vSrc,float s){		// �ÓI�֐�
		D3DXVec2Scale(vOut,vSrc,s);
	}
	void Scale(float s){
		Scale(this,this,s);
	}

	// ����
	static float Length(const D3DXVECTOR2 *vSrc){						// �ÓI�֐�
		return D3DXVec2Length(vSrc);
	}
	float Length(){
		return Length(this);
	}

	// ���K��
	static void Normalize(D3DXVECTOR2 *vOut,const D3DXVECTOR2 *vSrc){			// �ÓI�֐�
		D3DXVec2Normalize(vOut,vSrc);
	}
	void Normalize(){
		Normalize(this,this);
	}
	void Normalize(D3DXVECTOR2 *vOut) const{
		Normalize(vOut,this);
	}

};

}

#endif
