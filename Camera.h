#pragma once
class Camera
{
	float xPosition;
	float yPosition;
	float zPosition;
	float xLookAt;
	float yLookAt;
	float zLookAt;
	float xUp;
	float yUp;
	float zUp;
	float fov;
	float near;
	float far;
public:
	Camera(float xPosition, float yPosition, float zPosition, float xLookAt, float yLookAt, float zLookAt, float xUp, float yUp, float zUp, float fov, float near, float far) {
		this->xPosition = xPosition;
		this->yPosition = yPosition;
		this->zPosition = zPosition;
		this->xLookAt = xLookAt;
		this->yLookAt = yLookAt;
		this->zLookAt = zLookAt;
		this->xUp = xUp;
		this->yUp = yUp;
		this->zUp = zUp;
		this->fov = fov;
		this->near = near;
		this->far = far;
	}
};
