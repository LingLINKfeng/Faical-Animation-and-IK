#pragma once
#include<iostream>
#include<vector>
#include<glm/gtx/vector_angle.hpp>
#include<glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include"bone.h"
class CCD {
public:
	CCD( std::vector<Bone> joints,glm::vec3 end);

	void Update(glm::vec3 targetposition);

	glm::quat GetQuaternion(int x) const;
	glm::vec3 GetJoints(int x) const;
	glm::vec3 GetEnd()const;
	

private:
	std::vector<Bone> joints;
	glm::vec3 end;
	std::vector<glm::quat> quaternions{Q1,Q2,Q3};

	int indexQ1 = 1;
	int indexQ2 = 1;
	int indexQ3 = 1;

	glm::quat Q3;
	glm::quat Q2;
	glm::quat Q1;
	glm::quat temp;
	glm::vec3 rotationAxis;
	glm::vec3 hand_target;
	glm::vec3 hand_end;
	glm::vec3 forearm_target;
	glm::vec3 forearm_end;
	glm::vec3 upperArm_target;
	glm::vec3 upperArm_end;

};