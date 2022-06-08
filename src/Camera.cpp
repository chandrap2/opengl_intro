#include "Camera.h"
using namespace std;

Camera::Camera() : pos(vec3(0.0f, 0.0f, 0.0f)),
up(vec3(0.0f, 1.0f, 0.0f)), right(vec3(1.0f, 0.0f, 0.0f)),
front(vec3(0.0, 0.0, -1.0)) {};
//
void Camera::translate(vec3 translate) {
	vec4 temp(pos, 1.0f);
	temp = glm::translate(mat4(1.0f), translate) * temp;
	pos = static_cast<vec3>(temp);
}
//
void Camera::rotate(float deg, vec3 rotate) {
	mat4 rot = glm::rotate(mat4(1.0f), deg, rotate);
	up = static_cast<vec3>(rot * vec4(up, 1.0f));
	front = static_cast<vec3>(rot * vec4(front, 1.0f));
	right = static_cast<vec3>(rot * vec4(right, 1.0f));
}
//
mat4 Camera::look() {
	return glm::lookAt(pos, pos + front, up);
}
