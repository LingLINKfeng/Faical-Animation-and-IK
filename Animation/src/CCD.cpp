#include "CCD.h"

CCD::CCD(std::vector<Bone> joints, glm::vec3 end)
	: joints(joints),end(end)
{
	joints[0].default_Direction = joints[0].position - joints[1].position;//hand
	joints[1].default_Direction = joints[1].position - joints[2].position;//forearm
	joints[2].default_Direction = glm::vec3(1.0f,0.0f,0.0f);//upperarm
}

void CCD::Update(glm::vec3 targetPosition)
{
	//hand
	hand_target = glm::normalize(targetPosition - joints[0].position);
	hand_end = glm::normalize(end - joints[0].position);

	joints[0].default_Direction = glm::normalize(joints[0].position - joints[1].position);
	float angle_hand = glm::angle(hand_target, hand_end);
	rotationAxis = glm::normalize(glm::cross(hand_target, hand_end));
	
	if (glm::angle(hand_target, joints[0].default_Direction) > 1.5 )
		angle_hand = 0;
	else if (glm::angle(hand_target, joints[0].default_Direction) < -1)
		angle_hand = 0;
	temp = glm::angleAxis(angle_hand, -rotationAxis);
	end = joints[0].position + temp * (end - joints[0].position);
	if (indexQ1 == 1) {
		indexQ1++;
		quaternions[0] = temp;
	}
	else {
		quaternions[0] = temp * quaternions[0];
	}

	//forearm
	forearm_target = glm::normalize(targetPosition - joints[1].position);
	forearm_end = glm::normalize(end - joints[1].position);
	joints[1].default_Direction = glm::normalize(joints[1].position - joints[2].position);;

	float angle_forearm = glm::angle(forearm_target, forearm_end);
	rotationAxis = glm::normalize(glm::cross(forearm_target, forearm_end));
	temp = glm::angleAxis(angle_forearm, -rotationAxis);

	//update Up ,constrain
	glm::vec3 vector1 = glm::normalize(glm::vec3(end.x - joints[1].position.x, 0, end.z - joints[1].position.z));
	glm::vec3 vector2 = glm::normalize(glm::vec3(targetPosition.x - joints[1].position.x, 0, targetPosition.z - joints[1].position.z));

	float yawangle = glm::angle(vector2, vector1);
	float an = glm::angle(vector2, glm::vec3(joints[1].default_Direction.x, 0, joints[1].default_Direction.z));
	if (glm::cross(vector2, glm::vec3(joints[1].default_Direction.x, 0, joints[1].default_Direction.z)).y > 0)
		an = -an;
	if (glm::cross(vector1, vector2).y < 0) {
		yawangle = -yawangle;
		
	}
	std::cout <<an << std::endl;
	if (an > 2.5f)
		yawangle = 0;
	else if (an < 0.0f)
		yawangle = 0;
	glm::quat yaw = glm::angleAxis(yawangle, joints[1].Up);
	joints[1].Up = glm::normalize(glm::rotate(yaw, joints[0].Up));

	end = joints[1].position + yaw * (end - joints[1].position);
	joints[0].position = joints[1].position + yaw * (joints[0].position - joints[1].position);
	if (indexQ2 == 1) {
		indexQ2++;
		quaternions[0] = yaw * quaternions[0];
		quaternions[1] = yaw;
	}
	else {
		quaternions[0] = yaw * quaternions[0];
		quaternions[1] = yaw * quaternions[1];
	}

	//upperarm
	upperArm_target = glm::normalize(targetPosition - joints[2].position);
	upperArm_end = glm::normalize(end - joints[2].position);
	joints[2].default_Direction = glm::vec3(-1.0f, 0.0f, 0.0f);
	float angle_upperArm = glm::angle(upperArm_target, upperArm_end);

	rotationAxis = glm::normalize(glm::cross(upperArm_target, upperArm_end));
	temp = glm::angleAxis(angle_upperArm, -rotationAxis);

	end = joints[2].position + temp * (end - joints[2].position);
	joints[0].position = joints[2].position + temp * (joints[0].position - joints[2].position);
	joints[1].position = joints[2].position + temp * (joints[1].position - joints[2].position);
	if (indexQ3 == 1) {
		indexQ3++;
		quaternions[0] = temp * quaternions[0];
		quaternions[1] = temp * quaternions[1];
		quaternions[2] = temp;
	}
	else {
		quaternions[0] = temp * quaternions[0];
		quaternions[1] = temp * quaternions[1];
		quaternions[2] = temp * quaternions[2];
	}
	
}

glm::quat CCD::GetQuaternion(int x) const
{
	return quaternions[x];
}

glm::vec3 CCD::GetJoints(int x) const
{
	return joints[x].position;
}

glm::vec3 CCD::GetEnd() const
{
	return this->end;
}

