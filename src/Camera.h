#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

using namespace std;
using glm::vec3;
using glm::vec4;
using glm::mat4;

class Camera {
private:
public:
	vec3 pos, up, right, front;
	Camera();
	void translate(vec3 translate);
	void rotate(float deg, vec3 axis);
	mat4 look();
};