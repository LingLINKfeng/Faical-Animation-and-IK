#pragma once
#include <GL/glew.h>
#include<vector>
#include<glm/gtx/vector_angle.hpp>
#include<glm/gtc/matrix_transform.hpp>

class VertexBuffer {
private:
	GLuint m_RendererID;
	GLuint numVertices;
public:
	VertexBuffer(GLfloat vertices[], GLfloat colors[], GLfloat coords[], GLint numVertices);
	VertexBuffer(GLfloat vertices[], GLfloat colors[], GLint numVertices);
	VertexBuffer(GLfloat vertices[], GLint size);
	VertexBuffer(std::vector<glm::vec3> *vertices, GLint size);
	~VertexBuffer();

	void Bind()const;
	void Unbind()const;
};