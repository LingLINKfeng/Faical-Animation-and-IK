//#include<GL/glew.h>
//#include <GLFW/glfw3.h>
//#include<string>
//#include <cstdlib>
//
//#include<glm/gtx/vector_angle.hpp>
//#include<glm/gtx/quaternion.hpp>
//#include <glm/gtc/quaternion.hpp>
//#include<glm/gtc/matrix_transform.hpp>
//
//#include"VertexBuffer.h"
//#include"VertexArray.h"
//#include"VertexBufferLayout.h"
//#include"IndexBuffer.h"
//#include"Renderer.h"
//#include"Mesh.h"
//#include"Model.h"
//#include"CubemapTexture.h"
//#include"std_image/stb_image.h"
//#include"CCD.h"
//#include"bone.h"
//#include<iostream>
//static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//static void processInput(GLFWwindow *window);
//
//static const unsigned int SCR_WIDTH = 1920;
//static const unsigned int SCR_HEIGHT = 1080;
//static glm::vec3 cameraPos = glm::vec3(0.0f, 25.0f, -15.0f);
//static glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
//static glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
//
//
//static bool isPpressed = false;
//static bool isFmodel = false;
//
//static float targetX = -22;
//static float targetY = 33;
//static float targetZ = 3;
//
//
//static const float cameraSpeed = 1.0f;
//static float yaw = 90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
//static float pitch = 0.0f;
//static float Fyaw = 90.0f;
//static float Fpitch = 0.0f;
//static float deltaPitch = 0;
//static float deltaYaw = 0;
//static float deltaRoll = 0;
//
//static float lastX = SCR_WIDTH / 2.0;
//static float lastY = SCR_HEIGHT / 2.0;
//static float fov = 60.0f;
//static float deltaTime = 0.0f;
//static float lastFrame = 0.0f;
//static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
//	glViewport(0, 0, width, height);
//}
//static void mouse_callback(GLFWwindow* window, double xpos, double ypos)
//{
//	float xoffset;
//	float yoffset;
//	glm::vec3 front;
//
//	if (!isFmodel) {
//		xoffset = xpos - lastX;
//		yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
//		lastX = xpos;
//		lastY = ypos;
//
//		float sensitivity = 0.2f; // change this value to your liking
//		xoffset *= sensitivity;
//		yoffset *= sensitivity;
//
//		yaw += xoffset;
//		pitch += yoffset;
//
//		// make sure that when pitch is out of bounds, screen doesn't get flipped
//		if (pitch > 89.0f)
//			pitch = 89.0f;
//		if (pitch < -89.0f)
//			pitch = -89.0f;
//
//		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
//		front.y = sin(glm::radians(pitch));
//		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
//		cameraFront = glm::normalize(front);
//	}
//}
//static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//	fov -= (float)yoffset;
//	if (fov < 1.0f)
//		fov = 1.0f;
//	if (fov > 45.0f)
//		fov = 45.0f;
//}
//static void processInput(GLFWwindow *window) {
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, false);
//	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && !isPpressed)
//	{
//		isPpressed = true;
//		if (!isFmodel)
//			isFmodel = true;
//		else
//			isFmodel = false;
//	}
//	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_RELEASE)
//		isPpressed = false;
//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//		cameraPos += cameraSpeed * cameraFront;
//	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//		cameraPos -= cameraSpeed * cameraFront;
//	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
//	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
//	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
//		cameraPos += cameraUp * cameraSpeed;
//	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
//		cameraPos -= cameraUp * cameraSpeed;
//	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
//		targetY += 0.3;
//	}
//	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_RELEASE) {
//	}
//	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
//		targetY -= 0.3;
//	}
//	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
//		targetX += 0.3;
//	}
//
//	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_RELEASE) {
//
//	}
//
//	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
//		targetX -= 0.3;
//	}
//	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
//		targetZ += 0.3;
//	}
//
//	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_RELEASE) {
//
//	}
//
//	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
//		targetZ -= 0.3;
//	}
//
//
//}
//int main(void)
//{
//	GLFWwindow* window;
//	/* Initialize the library */
//	if (!glfwInit())
//		return -1;
//
//	/* Create a windowed mode window and its OpenGL context */
//	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LingFeng Zhang", NULL, NULL);
//	if (!window)
//	{
//		glfwTerminate();
//		return -1;
//	}
//
//	/* Make the window's context current */
//	glfwMakeContextCurrent(window);
//	glfwSwapInterval(3);
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//	glfwSetScrollCallback(window, scroll_callback);
//	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//close mouse
//	glEnable(GL_DEPTH_TEST);
//	if (glewInit() != GLEW_OK)
//		std::cout << "error!" << std::endl;
//	float vertices[] = {
//		-0.5f, -0.5f, -0.5f,
//		 0.5f, -0.5f, -0.5f,
//		 0.5f,  0.5f, -0.5f,
//		 0.5f,  0.5f, -0.5f,
//		-0.5f,  0.5f, -0.5f,
//		-0.5f, -0.5f, -0.5f,
//
//		-0.5f, -0.5f,  0.5f,
//		 0.5f, -0.5f,  0.5f,
//		 0.5f,  0.5f,  0.5f,
//		 0.5f,  0.5f,  0.5f,
//		-0.5f,  0.5f,  0.5f,
//		-0.5f, -0.5f,  0.5f,
//
//		-0.5f,  0.5f,  0.5f,
//		-0.5f,  0.5f, -0.5f,
//		-0.5f, -0.5f, -0.5f,
//		-0.5f, -0.5f, -0.5f,
//		-0.5f, -0.5f,  0.5f,
//		-0.5f,  0.5f,  0.5f,
//
//		 0.5f,  0.5f,  0.5f,
//		 0.5f,  0.5f, -0.5f,
//		 0.5f, -0.5f, -0.5f,
//		 0.5f, -0.5f, -0.5f,
//		 0.5f, -0.5f,  0.5f,
//		 0.5f,  0.5f,  0.5f,
//
//		-0.5f, -0.5f, -0.5f,
//		 0.5f, -0.5f, -0.5f,
//		 0.5f, -0.5f,  0.5f,
//		 0.5f, -0.5f,  0.5f,
//		-0.5f, -0.5f,  0.5f,
//		-0.5f, -0.5f, -0.5f,
//
//		-0.5f,  0.5f, -0.5f,
//		 0.5f,  0.5f, -0.5f,
//		 0.5f,  0.5f,  0.5f,
//		 0.5f,  0.5f,  0.5f,
//		-0.5f,  0.5f,  0.5f,
//		-0.5f,  0.5f, -0.5f
//	};
//
//	VertexArray lightVA;
//	VertexBuffer lightVertex(vertices, 3 * 6 * 6);
//	VertexBufferLayout lightLayout;
//	lightLayout.Push<float>(3);
//	lightVA.AddBuffer(lightVertex, lightLayout);
//
//	Shader CookTorranceShader("src/Shader/cook-torrance.shader");
//	Shader targetShdaer("src/Shader/demo.shader");
//	CookTorranceShader.SetUniformVec3("lightPos", glm::vec3(4.0f, 4.0f, 2.0f));
//	CookTorranceShader.SetUniformVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
//	CookTorranceShader.SetUniformVec3("objectColor", glm::vec3(0.8f, 0.2f, 0.3f));
//
//	Model handModel("src/Model/man/hand.obj");
//	Model forearmModel("src/Model/man/forearm.obj");
//	Model upperarmModel("src/Model/man/upperarm.obj");
//	Model bodyModel("src/Model/man/body.obj");
//	Renderer renderer;
//	
//	if (glewInit() != GLEW_OK)
//		std::cout << "error" << std::endl;
//	/* Loop until the user closes the window */
//
//	glm::vec3 end = glm::vec3(-22.5f, 35.5f, 0.7f);
//	Bone hand(glm::vec3(-18.5f, 36.0f, -0.3f), glm::vec3(0.0, 1.0, 0.0));
//	Bone forearm(glm::vec3(-12.0f, 36.0f, -0.65f), glm::vec3(0.0, 1.0, 0.0));
//	Bone upperarm(glm::vec3(-5.2f, 36.0f, -0.65f), glm::vec3(0.0, 1.0, 0.0));
//	//glm::vec3 handPosition = glm::vec3(-18.5f, 36.0f, -0.3f);
//	//glm::vec3 forearmPosition = glm::vec3(-12.0f, 36.0f, -0.65f);
//	//glm::vec3 origin = glm::vec3(-5.2f, 36.0f, -0.65f);
//	std::vector<Bone> joints{ hand ,forearm,upperarm };
//	CCD *ccd=new CCD(joints,end);
//	while (!glfwWindowShouldClose(window))
//	{
//		glm::mat4 hand = glm::mat4(1.0f);
//		glm::mat4 forearm = glm::mat4(1.0f);
//		glm::mat4 upperArm = glm::mat4(1.0f);
//		
//		/* Render here */
//		glfwSetCursorPosCallback(window, mouse_callback);
//		processInput(window);
//
//		renderer.Clear();
//		glm::mat4 projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
//		glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
//
//		CookTorranceShader.Bind();
//		CookTorranceShader.SetUniformVec3("lightPos", glm::vec3(4.0f, 4.0f, 2.0f));
//		CookTorranceShader.SetUniformVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
//		CookTorranceShader.SetUniformVec3("objectColor", glm::vec3(0.8f, 0.2f, 0.3f));
//		CookTorranceShader.SetUniformVec3("viewPos", cameraPos);
//		CookTorranceShader.SetUniformf("roughness", 0.3);
//		CookTorranceShader.SetUniformMat4f("projection", projection);
//		CookTorranceShader.SetUniformMat4f("view", view);
//	
//		
//		//CCD
//		glm::vec3 targetPosition = glm::vec3(targetX, targetY, targetZ);
//		//std::cout << "x:" << targetPosition.x << "y:" << targetPosition.y << "z:" << targetPosition.z << std::endl;
//		ccd->Update(targetPosition);
//
//		upperArm = glm::translate(upperArm, glm::vec3(ccd->GetJoints(2)));
//		upperArm = upperArm * glm::toMat4(ccd->GetQuaternion(2));
//		forearm = glm::translate(forearm, glm::vec3(ccd->GetJoints(1)));
//		forearm = forearm * glm::toMat4(ccd->GetQuaternion(1));
//		hand = glm::translate(hand, glm::vec3(ccd->GetJoints(0)));
//		hand = hand * glm::toMat4(ccd->GetQuaternion(0));
//		
//		CookTorranceShader.SetUniformMat4f("model", forearm);
//		forearmModel.Draw(CookTorranceShader);
//		CookTorranceShader.SetUniformMat4f("model", upperArm);
//		upperarmModel.Draw(CookTorranceShader);
//		CookTorranceShader.SetUniformMat4f("model", hand);
//		handModel.Draw(CookTorranceShader);
//
//		glm::mat4 body = glm::mat4(1.0);
//		CookTorranceShader.SetUniformMat4f("model", body);
//		bodyModel.Draw(CookTorranceShader);
//
//		targetShdaer.Bind();
//		targetShdaer.SetUniformMat4f("view", view);
//		targetShdaer.SetUniformMat4f("projection", projection);
//		
//		if(abs((ccd->GetEnd() -targetPosition).x)<0.2&& abs((ccd->GetEnd() - targetPosition)).y < 0.2 && abs((ccd->GetEnd() - targetPosition)).z < 0.2)
//			targetShdaer.SetUniformVec3("targetColor", glm::vec3(0.0, 1.0, 0.0));
//		else
//		{
//			targetShdaer.SetUniformVec3("targetColor", glm::vec3(1.0, 1.0, 1.0));
//		}
//
//		glm::mat4 model = glm::mat4(1.0f);
//		model = glm::translate(model, glm::vec3(targetX, targetY, targetZ));
//		targetShdaer.SetUniformMat4f("model", model);
//		lightVA.Bind();
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//
//
//		/* Swap front and back buffers */
//		glfwSwapBuffers(window);
//
//		/* Poll for and process events */
//		glfwPollEvents();
//	}
//	delete ccd;
//
//	glfwTerminate();
//	return 0;
//}