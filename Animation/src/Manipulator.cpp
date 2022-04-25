#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<ImGUI/imgui.h>
#include<ImGUI/imgui_impl_opengl3.h>
#include<ImGUI/imgui_impl_glfw.h>

#include <fstream>
#include<string>
#include <cstdlib>
#include<glm/gtx/vector_angle.hpp>
#include<glm/gtc/matrix_transform.hpp>

#include"VertexBuffer.h"
#include"VertexArray.h"
#include"VertexBufferLayout.h"
#include"IndexBuffer.h"
#include"Renderer.h"
#include"Mesh.h"
#include"Model.h"
#include"CubemapTexture.h"
#include"std_image/stb_image.h"
#include"CCD.h"
#include"bone.h"
#include<iostream>
#include<Eigen/Dense>

static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
static void processInput(GLFWwindow *window);

static const unsigned int SCR_WIDTH = 1920;
static const unsigned int SCR_HEIGHT = 1080;
static glm::vec3 cameraPos = glm::vec3(0.0f, 17.0f, 36.0f);
static glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
static glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
static std::vector<Model> facemodel;
glm::vec3 vertex;
glm::mat4 projection;
glm::mat4 view;
glm::mat4 model;


static bool isPpressed = false;
static bool isFmodel = false;

float targetX = 0;
float targetY = 0;
float targetZ = 0;


static const float cameraSpeed = 1.0f;
static float yaw = 90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
static float pitch = 0.0f;
static float Fyaw = -90.0f;
static float Fpitch = 0.0f;
static float deltaPitch = 0;
static float deltaYaw = 0;
static float deltaRoll = 0;

static float lastX = SCR_WIDTH / 2.0;
static float lastY = SCR_HEIGHT / 2.0;
static float fov = 60.0f;
static float deltaTime = 0.0f;
static float lastFrame = 0.0f;
float I[250][24];
static int currentIndex = 0;
static int index = 0;
static bool hold = false;
static int p = 0;
static bool press = false;
static double world_mousex, world_mousey;
static std::vector<int> constrains;

static Eigen::MatrixXd F(3 * 28284, 1);
static Eigen::MatrixXd f0(3 * 28284, 1);
static Eigen::MatrixXd w(24, 1);
static Eigen::MatrixXd B(3 * 28284, 24);
static Eigen::MatrixXd m0,m,B_bar,W,I_unit,A,b;
static double alpha=0.1, mio=0.001;

static double mouse_xpos, mouse_ypos,world_mousez, current_x, current_y, current_z;

static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
static void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	float xoffset;
	float yoffset;
	glm::vec3 front;

	if (!isFmodel) {
		xoffset = xpos - lastX;
		yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
		lastX = xpos;
		lastY = ypos;

		float sensitivity = 0.2f; // change this value to your liking
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch += yoffset;

		// make sure that when pitch is out of bounds, screen doesn't get flipped
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		cameraFront = glm::normalize(front);
	}
}
static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	fov -= (float)yoffset;
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 45.0f)
		fov = 45.0f;
}
static void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, false);
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && !isPpressed)
	{
		isPpressed = true;
		if (!isFmodel)
			isFmodel = true;
		else
			isFmodel = false;
	}
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_RELEASE)
		isPpressed = false;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		cameraPos += cameraUp * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		cameraPos -= cameraUp * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
			targetY += 0.03;
	}
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_RELEASE) {
		targetY = 0;
	}
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
			targetY -= 0.05;
	}
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
			targetX += 0.03;
	}
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_RELEASE) {
		targetX = 0;
	}
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
			targetX -= 0.05;
	}
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
			targetZ += 0.03;
	}
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_RELEASE) {
		targetZ = 0;
	}
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
			targetZ -= 0.05;
	}
}
void vectorPicker(int x, int y, glm::mat4 VM, glm::mat4 P, Model model)
{
	glm::vec3 window;
	window.x = x;
	window.y = SCR_HEIGHT - y - 1;
	glReadPixels(window.x, window.y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &window.z);
	glm::vec3 object = glm::unProject(window, VM, P, glm::vec4(0.0, 0.0, SCR_WIDTH, SCR_HEIGHT));
	world_mousex = object.x ;
	world_mousey = object.y ;
	world_mousez = object.z;
	GLfloat dist = 60;
	GLfloat temp = 0.0f;
	for (int i = 0; i < model.f.size(); i++) {
		temp = glm::distance(object, model.f[i]);
		if (temp < dist) {
			dist = temp;
			index = i;
		}
		i++;
	}
	vertex = model.f[index];

}
void readFile(const std::string &file_path)
{

	std::ifstream myfile(file_path);
	if (!myfile.is_open())
	{
		std::cout << "can not open this file" << std::endl;
		return exit(1);
	}
	for (int i = 0; i < 250; i++)
	{
		for (int j = 0; j < 24; j++)
		{
			myfile >> I[i][j];
		}
	}
	//std::cout << I[1][5] << std::endl;
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (action == GLFW_PRESS)switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
		constrains.emplace_back(index);
		m0.conservativeResize(Eigen::Index(constrains.size() * 3), 1);
		m0(3 * constrains.size() - 3, 0) = vertex.x;
		m0(3 * constrains.size() - 2, 0) = vertex.y;
		m0(3 * constrains.size() - 1, 0) = vertex.z;
		current_x = vertex.x;
		current_y = vertex.y;
		current_z = vertex.z;
		currentIndex = index;
		hold = true;
		break;
	}

}
int main(void)
{
	GLFWwindow* window;
	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LingFeng Zhang", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	readFile("src/Model/blendshape_animation.txt");
	/* Make the window's context current */

	glfwMakeContextCurrent(window);
	glfwSwapInterval(3);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	//glfwSetCursorPosCallback(window, mouse_callback);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//close mouse
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	glEnable(GL_DEPTH_TEST);
	if (glewInit() != GLEW_OK)
		std::cout << "error!" << std::endl;

	Shader CookTorranceShader("src/Shader/cook-torrance.shader");
	CookTorranceShader.SetUniformVec3("lightPos", glm::vec3(4.0f, 4.0f, 2.0f));
	CookTorranceShader.SetUniformVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
	CookTorranceShader.SetUniformVec3("objectColor", glm::vec3(0.8f, 0.2f, 0.3f));
	Model face("src/Model/face/neutral.obj");

	{
		Model face_jaw_open("src/Model/face/Mery_jaw_open.obj"); facemodel.emplace_back(face_jaw_open);
		Model face_kiss("src/Model/face/Mery_kiss.obj"); facemodel.emplace_back(face_kiss);
		Model face_l_brow_lower("src/Model/face/Mery_l_brow_lower.obj"); facemodel.emplace_back(face_l_brow_lower);
		Model face_l_brow_narrow("src/Model/face/Mery_l_brow_narrow.obj"); facemodel.emplace_back(face_l_brow_narrow);
		Model face_l_brow_raise("src/Model/face/Mery_l_brow_raise.obj"); facemodel.emplace_back(face_l_brow_raise);
		Model face_l_eye_closed("src/Model/face/Mery_l_eye_closed.obj"); facemodel.emplace_back(face_l_eye_closed);
		Model face_l_eye_lower_open("src/Model/face/Mery_l_eye_lower_open.obj"); facemodel.emplace_back(face_l_eye_lower_open);
		Model face_l_eye_upper_open("src/Model/face/Mery_l_eye_upper_open.obj"); facemodel.emplace_back(face_l_eye_upper_open);
		Model face_l_nose_wrinkle("src/Model/face/Mery_l_nose_wrinkle.obj"); facemodel.emplace_back(face_l_nose_wrinkle);
		Model face_l_puff("src/Model/face/Mery_l_puff.obj"); facemodel.emplace_back(face_l_puff);
		Model face_l_sad("src/Model/face/Mery_l_sad.obj"); facemodel.emplace_back(face_l_sad);
		Model face_l_smile("src/Model/face/Mery_l_smile.obj"); facemodel.emplace_back(face_l_smile);

		Model Mery_l_suck("src/Model/face/Mery_l_suck.obj"); facemodel.emplace_back(Mery_l_suck);
		Model Mery_r_brow_lower("src/Model/face/Mery_r_brow_lower.obj"); facemodel.emplace_back(Mery_r_brow_lower);
		Model Mery_r_brow_narrow("src/Model/face/Mery_r_brow_narrow.obj"); facemodel.emplace_back(Mery_r_brow_narrow);
		Model Mery_r_brow_raise("src/Model/face/Mery_r_brow_raise.obj"); facemodel.emplace_back(Mery_r_brow_raise);
		Model Mery_r_eye_closed("src/Model/face/Mery_r_eye_closed.obj"); facemodel.emplace_back(Mery_r_eye_closed);
		Model Mery_r_eye_lower_open("src/Model/face/Mery_r_eye_lower_open.obj"); facemodel.emplace_back(Mery_r_eye_lower_open);
		Model Mery_r_eye_upper_open("src/Model/face/Mery_r_eye_upper_open.obj"); facemodel.emplace_back(Mery_r_eye_upper_open);
		Model Mery_r_nose_wrinkle("src/Model/face/Mery_r_nose_wrinkle.obj"); facemodel.emplace_back(Mery_r_nose_wrinkle);
		Model Mery_r_puff("src/Model/face/Mery_r_puff.obj"); facemodel.emplace_back(Mery_r_puff);
		Model Mery_r_sad("src/Model/face/Mery_r_sad.obj"); facemodel.emplace_back(Mery_r_sad);
		Model Mery_r_smile("src/Model/face/Mery_r_smile.obj"); facemodel.emplace_back(Mery_r_smile);
		Model Mery_r_suck("src/Model/face/Mery_r_suck.obj"); facemodel.emplace_back(Mery_r_suck);
	}

	

	Renderer renderer;
	//std::cout << facemodel.size() << std::endl;
	for (int i = 0; i < 28284 * 2; i += 2)
	{
		int j = 3 * (i / 2);
		f0(j, 0) = face.f[i].x;
		f0(j + 1, 0) = face.f[i].y;
		f0(j + 2, 0) = face.f[i].z;
		for (int k = 0; k < 24; k++) {
			B(j, k) = facemodel[k].f[i].x - f0(j, 0);;
			B(j + 1, k) = facemodel[k].f[i].y - f0(j + 1, 0);;
			B(j + 2, k) = facemodel[k].f[i].z - f0(j + 2, 0);;
		}
	}
	for (int i = 0; i < 24; i++) {
		w(i, 0) = 0;
	}

	if (glewInit() != GLEW_OK)
		std::cout << "error" << std::endl;
	/* Loop until the user closes the window */
	int frame = 0;
	int speed = 2;

	while (!glfwWindowShouldClose(window))
	{
		glfwGetCursorPos(window, &mouse_xpos, &mouse_ypos);
		
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		/* Render here */
		processInput(window);

		renderer.Clear();
		projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 15.0f, 50.0f);
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		model = glm::mat4(1.0f);

		if (constrains.size()) {
			m.conservativeResize(Eigen::Index(constrains.size() * 3), 1);
			m(3 * constrains.size() - 3, 0) = current_x + targetX;
			m(3 * constrains.size() - 2, 0) = current_y + targetY;
			m(3 * constrains.size() - 1, 0) = current_z + targetZ;
			std::cout << targetY << std::endl;
		}

		// render your GUI
		ImGui::Begin("BLENDER FACIAL ANIMATION");
		float face_jaw_open = w(0, 0);
		ImGui::SliderFloat("face_jaw_open", &face_jaw_open, 0, 1.0);
		float face_kiss = w(1, 0);
		ImGui::SliderFloat("face_kiss", &face_kiss, 0, 1.0);
		float face_l_brow_lower = w(2, 0);
		ImGui::SliderFloat("face_l_brow_lower", &face_l_brow_lower, 0, 1.0);
		float face_l_brow_narrow = w(3, 0);
		ImGui::SliderFloat("face_l_brow_narrow", &face_l_brow_narrow, 0, 1.0);
		
		float face_l_brow_raise = w(4, 0);
		ImGui::SliderFloat("face_l_brow_raise", &face_l_brow_raise, 0, 1.0);
		float face_l_eye_closed = w(5, 0);
		ImGui::SliderFloat("face_l_eye_closed", &face_l_eye_closed, 0, 1.0);
		float face_l_eye_lower_open = w(6, 0);
		ImGui::SliderFloat("face_l_eye_lower_open", &face_l_eye_lower_open, 0, 1.0);
		float face_l_eye_upper_open = w(7, 0);
		ImGui::SliderFloat("face_l_eye_upper_open", &face_l_eye_upper_open, 0, 1.0);
		
		float face_l_nose_wrinkle = w(8, 0);
		ImGui::SliderFloat("face_l_nose_wrinkle", &face_l_nose_wrinkle, 0, 1.0);
		float face_l_puff = w(9, 0);
		ImGui::SliderFloat("face_l_puff", &face_l_puff, 0, 1.0);
		float face_l_sad = w(10, 0);
		ImGui::SliderFloat("face_l_sad", &face_l_sad, 0, 1.0);
		float face_l_smile = w(11, 0);
		ImGui::SliderFloat("face_l_smile", &face_l_smile, 0, 1.0);
		
		float Mery_l_suck = w(12, 0);
		ImGui::SliderFloat("Mery_l_suck", &Mery_l_suck, 0, 1.0);
		float Mery_r_brow_lower = w(13, 0);
		ImGui::SliderFloat("Mery_r_brow_lower", &Mery_r_brow_lower, 0, 1.0);
		float Mery_r_brow_narrow = w(14, 0);
		ImGui::SliderFloat("Mery_r_brow_narrow", &Mery_r_brow_narrow, 0, 1.0);
		float Mery_r_brow_raise = w(15, 0);
		ImGui::SliderFloat("Mery_r_brow_raise", &Mery_r_brow_raise, 0, 1.0);
		
		float Mery_r_eye_closed = w(16, 0);
		ImGui::SliderFloat("Mery_r_eye_closed", &Mery_r_eye_closed, 0, 1.0);
		float Mery_r_eye_lower_open = w(17, 0);
		ImGui::SliderFloat("Mery_r_eye_lower_open", &Mery_r_eye_lower_open, 0, 1.0);
		float Mery_r_eye_upper_open = w(18, 0);
		ImGui::SliderFloat("Mery_r_eye_upper_open", &Mery_r_eye_upper_open, 0, 1.0);
		float Mery_r_nose_wrinkle = w(19, 0);
		ImGui::SliderFloat("Mery_r_nose_wrinkle", &Mery_r_nose_wrinkle, 0, 1.0);
		
		float Mery_r_puff = w(20, 0);
		ImGui::SliderFloat("Mery_r_puff", &Mery_r_puff, 0, 1.0);
		float Mery_r_sad = w(21, 0);
		ImGui::SliderFloat("Mery_r_sad", &Mery_r_sad, 0, 1.0);
		float Mery_r_smile = w(22, 0);
		ImGui::SliderFloat("Mery_r_smile", &Mery_r_smile, 0, 1.0);
		float Mery_r_suck = w(23, 0);
		ImGui::SliderFloat("Mery_r_suck", &Mery_r_suck, 0, 1.0);
		ImGui::End();


		if (m.size()&&m.size()==m0.size()) {
			B_bar.conservativeResize(Eigen::Index(m.size()), 24);
			for (int i = 0; i < 24; i++)
			{
				//std::cout << currentIndex << std::endl;
				B_bar(m.size() - 3, i) = facemodel[i].f[currentIndex].x ;
				B_bar(m.size() - 2, i) = facemodel[i].f[currentIndex].y ;
				B_bar(m.size() - 1, i) = facemodel[i].f[currentIndex].z ;
			}
			I_unit = Eigen::MatrixXd::Identity(24, 24);
			A = B_bar.transpose()*B_bar + (alpha + mio)*I_unit;
			Eigen::LDLT<Eigen::MatrixXf> solver(A);
			b = B_bar.transpose()*(m - m0) + alpha*w;
			W = solver.solve(b);
			//W = (B_bar.transpose()*B_bar + (alpha + mio)*I_unit).inverse()*(B_bar.transpose()*(m - m0)) + w;
			//std::cout << W.size() << std::endl;
			for (int i = 0; i < 24; i++) {
				if (W(i, 0) > 1)
					W(i, 0) = 1;
				if (W(i, 0) < 0)
					W(i, 0) = 0;
			}
			w = W;
		}

		F = f0 + B * w;
		for (int i = 0; i < 28284 * 2; i += 2) {
			int j = 3 * (i / 2);
			face.f[i].x = F(j, 0);
			face.f[i].y = F(j + 1, 0);
			face.f[i].z = F(j + 2, 0);
		}

		CookTorranceShader.Bind();
		CookTorranceShader.SetUniformVec3("lightPos", glm::vec3(0.0f, 30.0f, 30.0f));
		CookTorranceShader.SetUniformVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
		CookTorranceShader.SetUniformVec3("objectColor", glm::vec3(0.8f, 0.2f, 0.3f));
		CookTorranceShader.SetUniformVec3("viewPos", cameraPos);
		CookTorranceShader.SetUniformf("roughness", 0.3);
		CookTorranceShader.SetUniformMat4f("projection", projection);
		CookTorranceShader.SetUniformMat4f("view", view);
		CookTorranceShader.SetUniformMat4f("model", model);

		//face.Draw(CookTorranceShader);
		VertexArray VA;
		IndexBuffer index(&(face.f_indices[0]), 28284);
		VertexBuffer facialVertex(&face.f[0].x, 3 * face.f.size());

		VertexBufferLayout facialLayout;
		facialLayout.Push<float>(3);
		facialLayout.Push<float>(3);
		VA.AddBuffer(facialVertex, facialLayout);
		glDrawArrays(GL_TRIANGLES, 0, 28284);

		vectorPicker(mouse_xpos, mouse_ypos, model*view, projection, face);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		//VertexBuffer facialVertex(&face.f[0].x, 3 * face.f.size());
		//std::cout << face.f_indices.size() << std::endl;
		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		//std::cout << cameraPos.x << cameraPos.y << cameraPos.z << std::endl;
		/* Poll for and process events */
		glfwPollEvents();
	}
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}