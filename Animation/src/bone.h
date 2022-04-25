#pragma once
#include<iostream>
#include<vector>
#include<glm/gtx/vector_angle.hpp>
#include<glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>
#include<glm/gtc/matrix_transform.hpp>
class Bone {
public:
	friend class CCD;
	Bone(glm::vec3 position, glm::vec3 Up) :position(position),Up(Up){};
	glm::vec3 GetPosition();
	glm::vec3 GetUp();
	glm::vec3 GetDirection();
private:
	glm::vec3 position;
	glm::vec3 Up;
	
	glm::vec3 default_Direction;

};