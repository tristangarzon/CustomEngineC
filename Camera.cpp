#include "Camera.h"

namespace GAME {

	Camera* Camera::currentCamera = nullptr;

	Camera::Camera(const int viewportWidth, const int viewportHeight, const Vec3 pos_)
	{
		pos = pos_;
		float aspect = float(viewportWidth) / float(viewportHeight);
		projectionMatrix = MMath::perspective(45.0f, aspect, 0.75f, 100.0f);

		updateViewMatrix();
	}

	Camera::~Camera() {

	}

	void Camera::updateViewMatrix()
	{
		viewMatrix = MMath::lookAt(pos,
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 1.0f, 0.0f));
	}

	Matrix4&  Camera::getProjectionMatrix()
	{
		return projectionMatrix;
	}


	Matrix4&  Camera::getViewMatrix()
	{
		return viewMatrix;
	}

	void Camera::setPos(const Vec3& pos_)
	{
		Entity::setPos(pos_);
		updateViewMatrix();
	}

	void Camera::setOrientation(const Vec3& orientation_)
	{
		Entity::setOrientation(orientation_);
		updateViewMatrix();
	}

}