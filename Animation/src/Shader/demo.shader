#shader vertex
#version 330

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
}

#shader fragment
#version 330
out vec4 FragColor;

uniform vec3 targetColor;
void main()
{
	FragColor = vec4(targetColor, 1.0);
}


