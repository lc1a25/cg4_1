#pragma once
#include "Win.h"
#include <DirectXMath.h>

class Camera
{
private:
	//template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX:: �ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	void Init();

	void UpdateCamera();

	void CameraMoveVector(XMFLOAT3 move);


	void CameraMoveVector2(XMFLOAT3 move);

	//getter
	const XMMATRIX& GetMatViewProjection() { return matViewProjection; }

	const XMFLOAT3& GetEye() { return eye; }
	const XMFLOAT3& GetTarget() { return target; }

	//setter
	void SetEye(XMFLOAT3 eye) 
	{ this->eye = eye; 
	  UpdateCamera(); }
	void SetTarget(XMFLOAT3 target) 
	{ this->target = target; 
	  UpdateCamera();
	}

private:
	// �r���[�s��
	XMMATRIX matView;
	// �ˉe�s��
	XMMATRIX matProjection;
	// ���_���W
	XMFLOAT3 eye = {0,0,-150};
	// �����_���W
	XMFLOAT3 target = { 0,20,0 };
	// ������x�N�g��
	XMFLOAT3 up = { 0,1,0 };

	XMMATRIX matViewProjection;

};
