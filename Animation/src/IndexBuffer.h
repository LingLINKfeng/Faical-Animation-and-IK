#pragma once
#include<GL/glew.h>
#include<vector>
class IndexBuffer
{
public:
	IndexBuffer(GLuint* data, GLuint count);
	IndexBuffer(std::vector<GLuint>* data, GLuint count);
	~IndexBuffer();
	void Bind() const;
	void Unbind();
	unsigned int GetCount()const;
private:
	GLuint m_RendererID;
	GLuint m_Count;
};

