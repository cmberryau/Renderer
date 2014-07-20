#include "Camera.h"

namespace Renderer
{
	Camera * Camera::MainCamera()
	{
		return nullptr;
	}

	Matrix4f Camera::ViewMatrix()
	{
		return Matrix4f::Identity();
	}

	Matrix4f Camera::ProjectionMatrix()
	{
		return Matrix4f::Perspective(75.0f, 1.33f, 1.0f, 500.0f);
	}

	Camera::Camera()
	{

	}

	Camera::~Camera()
	{

	}
}