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
//
//#include<iostream>
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void processInput(GLFWwindow *window);
//
//const unsigned int SCR_WIDTH = 1920;
//const unsigned int SCR_HEIGHT = 1080;
//glm::vec3 cameraPos = glm::vec3(0.0f, 15.0f, -50.0f);
//glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
//glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
//
//
//bool isPpressed = false;
//bool isFmodel = false;
//
//float targetX = 10;
//float targetY = 32;
//
//
//float cameraSpeed = 1.0f;
//float yaw = 90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
//float pitch = 0.0f;
//float Fyaw = 90.0f;
//float Fpitch = 0.0f;
//float deltaPitch = 0;
//float deltaYaw = 0;
//float deltaRoll = 0;
//
//float lastX = 1920.0f / 2.0;
//float lastY = 1080.0f / 2.0;
//float fov = 60.0f;
//float deltaTime = 0.0f;
//float lastFrame = 0.0f;
//void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
//	glViewport(0, 0, width, height);
//}
//void mouse_callback(GLFWwindow* window, double xpos, double ypos)
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
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//	fov -= (float)yoffset;
//	if (fov < 1.0f)
//		fov = 1.0f;
//	if (fov > 45.0f)
//		fov = 45.0f;
//}
//void processInput(GLFWwindow *window) {
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
//		targetY += 0.5;
//	}
//	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_RELEASE) {
//	}
//	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
//		targetY -= 0.5;
//	}
//	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
//		targetX += 0.5;
//	}
//
//	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_RELEASE) {
//
//	}
//
//	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
//		targetX -= 0.5;
//	}
//	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
//
//	}
//
//	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_RELEASE) {
//
//	}
//
//	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
//
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
//	CookTorranceShader.SetUniformVec3("lightPos", glm::vec3(4.0f, 4.0f, 2.0f));
//	CookTorranceShader.SetUniformVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
//	CookTorranceShader.SetUniformVec3("objectColor", glm::vec3(0.8f, 0.2f, 0.3f));
//
//	Model arm("src/Model/arm.obj");
//	Renderer renderer;
//
//	if (glewInit() != GLEW_OK)
//		std::cout << "error" << std::endl;
//	/* Loop until the user closes the window */
//	//glm::mat4 forearm = glm::mat4(1.0f);
//	//forearm = glm::translate(forearm, glm::vec3(0.0, 32.0f, 0.0));
//	
//	glm::quat Q2;
//	glm::quat Q1;
//	glm::mat4 view;
//	glm::vec3 origin = glm::vec3(0.0, 16.0, 0.0);//first joint position
//	glm::vec3 FP = glm::vec3(0.0, 32.0, 0.0);//second joint position
//	glm::vec3 FEP = glm::vec3(0.0, 48.0, 0.0);//end position
//	glm::vec3 up = glm::normalize(FP - FEP);//default direction
//	
//	int indexQ1 = 1;
//	int indexQ2 = 1;
//	while (!glfwWindowShouldClose(window))
//	{
//		glm::mat4 bigArm = glm::mat4(1.0f);
//		glm::mat4 forearm = glm::mat4(1.0f);
//
//		/* Render here */
//		glfwSetCursorPosCallback(window, mouse_callback);
//		processInput(window);
//
//		renderer.Clear();
//		
//		glm::mat4 projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
//		glm::mat4 view = glm::lookAt(cameraPos, cameraPos+cameraFront, cameraUp);
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
//		//CCD
//		glm::vec3 targetPosition = glm::vec3(targetX, targetY, 0.0f);
//		glm::vec3 FP_T = glm::normalize(targetPosition - FP);
//		glm::vec3 OR_T = glm::normalize(targetPosition - origin);
//		glm::vec3 up = glm::normalize(FEP - FP);
//		
//		float angle1 = glm::angle(FP_T, up);//calculate angle
//		if (glm::cross(FP_T, up).z > 0) {
//			angle1 = -angle1;
//		}
//		glm::vec3 EulerAngles(0, 0, angle1);
//		glm::quat Quaternion = glm::quat(EulerAngles);
//		glm::quat temp = glm::angleAxis(angle1, glm::vec3(0.0,0.0,1.0));
//		FEP = FP+Quaternion*(FEP - FP);//update joint position
//
//		glm::vec3 OR_FEP = glm::normalize(FEP - origin);
//		float angle2 = glm::angle(OR_T, OR_FEP);
//		if (glm::cross(OR_T, glm::normalize(OR_FEP)).z > 0) {
//			angle2 = -angle2;
//		}
//		
//
//		glm::vec3 EulerAngles2(0, 0, angle2);
//		glm::quat Quaternion2 = glm::quat(EulerAngles2);
//		glm::quat temp2 = glm::angleAxis(angle2, glm::vec3(0.0, 0.0, 1.0));
//		if (indexQ2 == 1) {
//			Q2 = Quaternion2;
//			indexQ2++;
//		}
//		else
//			Q2 = Quaternion2 * Q2;
//
//		FP = origin+ Quaternion2 * (FP- origin);//update joint position
//		FEP = origin+ Quaternion2 * (FEP- origin);//update joint position
//
//		bigArm = glm::translate(bigArm, glm::vec3(0, 16.0, 0.0));
//		bigArm = bigArm * glm::toMat4(Q2);
//		forearm = glm::translate(forearm, glm::vec3(FP.x,FP.y, 0.0));
//		if (indexQ1 == 1) {
//			Q1 = Quaternion;
//			indexQ1++;
//		}
//		else
//			Q1 = Quaternion * Q1;
//		forearm = forearm *  glm::toMat4(Q1);	
//		forearm = forearm * glm::toMat4(Q2);
//
//		CookTorranceShader.SetUniformMat4f("model", forearm);
//		arm.Draw(CookTorranceShader);
//		CookTorranceShader.SetUniformMat4f("model", bigArm);
//		arm.Draw(CookTorranceShader);
//
//		glm::mat4 model = glm::mat4(1.0f);
//		model = glm::translate(model, glm::vec3(targetX, targetY,0.0f));
//		CookTorranceShader.SetUniformMat4f("model", model);
//		lightVA.Bind();
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//		/* Swap front and back buffers */
//		glfwSwapBuffers(window);
//
//		/* Poll for and process events */
//		glfwPollEvents();
//	}
//
//	glfwTerminate();
//	return 0;
//}