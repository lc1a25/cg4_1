#pragma once
#include "Win.h"
#include <DirectXMath.h>

class Camera
{
private:
	//template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX:: 省略
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
	// ビュー行列
	XMMATRIX matView;
	// 射影行列
	XMMATRIX matProjection;
	// 視点座標
	XMFLOAT3 eye = {0,0,-150};
	// 注視点座標
	XMFLOAT3 target = { 0,20,0 };
	// 上方向ベクトル
	XMFLOAT3 up = { 0,1,0 };

	XMMATRIX matViewProjection;

};
