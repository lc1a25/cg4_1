#include "Camera.h"
using namespace DirectX;

void Camera::Init()
{
	// ビュー行列の生成
	matView = XMMatrixLookAtLH(
		XMLoadFloat3(&eye),
		XMLoadFloat3(&target),
		XMLoadFloat3(&up));

	// 平行投影による射影行列の生成
	//constMap->mat = XMMatrixOrthographicOffCenterLH(
	//	0, window_width,
	//	window_height, 0,
	//	0, 1);
	// 透視投影による射影行列の生成
	matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(60.0f),
		(float)Win::window_width / Win::window_height,
		0.1f, 1000.0f
	);

	matViewProjection = matView * matProjection;
}

void Camera::UpdateCamera()
{
	// ビュー行列の更新
	matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));

	matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(60.0f),
		(float)Win::window_width / Win::window_height,
		0.1f, 1000.0f
	);

	matViewProjection = matView * matProjection;
}

void Camera::CameraMoveVector(XMFLOAT3 move, bool frag)
{
	XMFLOAT3 eye_moved = GetEye();
	XMFLOAT3 target_moved = GetTarget();

	if (frag == true)
	{
		eye_moved.x += move.x;
		eye_moved.y += move.y;
		eye_moved.z += move.z;

		target_moved.x += move.x;
		target_moved.y += move.y;
		target_moved.z += move.z;
	}
	else
	{
		eye_moved.x -= move.x;
		eye_moved.y -= move.y;
		eye_moved.z -= move.z;

		target_moved.x -= move.x;
		target_moved.y -= move.y;
		target_moved.z -= move.z;
	}
	SetEye(eye_moved);
	SetTarget(target_moved);
}

void Camera::CameraMoveVectorAdd(XMFLOAT3 move)
{
	XMFLOAT3 eye_moved = GetEye();
	XMFLOAT3 target_moved = GetTarget();

	eye_moved.x += move.x;
	eye_moved.y += move.y;
	eye_moved.z += move.z;

	target_moved.x += move.x;
	target_moved.y += move.y;
	target_moved.z += move.z;

	SetEye(eye_moved);
	SetTarget(target_moved);
}

void Camera::CameraMoveVectorSub(XMFLOAT3 move)
{
	XMFLOAT3 eye_moved = GetEye();
	XMFLOAT3 target_moved = GetTarget();

	eye_moved.x -= move.x;
	eye_moved.y -= move.y;
	eye_moved.z -= move.z;

	target_moved.x -= move.x;
	target_moved.y -= move.y;
	target_moved.z -= move.z;

	SetEye(eye_moved);
	SetTarget(target_moved);
}
