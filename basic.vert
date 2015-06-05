#version 330

layout (location = 0) in vec3 a_Position; 
layout (location = 1) in vec2 a_TexCoord;

uniform mat4 u_ModelViewProjectionMatrix;

out vec2 v_uv;

void main()
{
	v_uv = a_TexCoord;
	gl_Position = u_ModelViewProjectionMatrix * vec4(a_Position, 1.0);
}