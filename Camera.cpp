#include"pch.h"
#include"Camera.h"

Camera::Camera(XMVECTOR position, float fov, float aspectRatio)
{
	XMMATRIX view = XMMatrixLookAtLH(position,
									 position - XMVectorSet(1.0f, 0.0f, 0.0f, 1.0f),
									 XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));

	XMMATRIX projection = XMMatrixPerspectiveFovLH(fov, aspectRatio, 0.01f, 1000.0f);

	XMStoreFloat4x4(&mRaw.mView, view);
	XMStoreFloat4x4(&mRaw.mProjection, projection);

	Generate();
}

Camera::Camera(float px, float py, float pz, float fov, float aspectRatio)
{
	XMMATRIX view = XMMatrixLookAtLH(XMVectorSet(px, py, pz, 1.0f),
					 XMVectorSet(px - 1.0f, py, pz, 1.0f),
					 XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
	
	XMMATRIX projection = XMMatrixPerspectiveFovLH(fov, aspectRatio, 0.01f, 1000.0f);

	XMStoreFloat4x4(&mRaw.mView, view);
	XMStoreFloat4x4(&mRaw.mProjection, projection);
	
	Generate();

}

Camera::~Camera()
{}

bool Camera::Generate()
{
	HRESULT result;
	ID3D11Device* device = HW::GetDevice();
	D3D11_BUFFER_DESC bufferDesc{};
	D3D11_SUBRESOURCE_DATA subData{};
	
	bufferDesc.ByteWidth = sizeof(CameraBuffer);
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	
	subData.pSysMem = &mRaw;

	result = device->CreateBuffer(&bufferDesc, &subData, mBuffer.GetAddressOf());
	assert(result == S_OK);
	if (result != S_OK)
	{
		return false;
	}

	return true;
}

void Camera::Release()
{}
