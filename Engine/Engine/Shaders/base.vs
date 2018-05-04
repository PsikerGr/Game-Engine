#version 330
#extension GL_ARB_shading_language_420pack : enable

in vec4 a_Position; // x,y,z
in vec3 a_Normal; // x,y,z
in vec2 a_TexCoords; // u,v

uniform mat4 world;

out vec2 v_TexCoords;
out vec4 v_Color;

layout(std140, binding = 0) uniform MatrixBlock
{
	mat4 viewMatrix;
	mat4 projectionMatrix;
		
}	matrices;

layout(std140, binding = 1) uniform ColorBlock
{
	vec3 specularColor;
	vec3 ambiantColor;
	vec3 diffuseColor;
	
} colors;

void main(void)
{
	//vec3 camDir = normalize(camPos - worldMatrix[3].xyz);
	v_Color = vec4(abs(a_Normal), 1.0);//abs(a_Position);
	v_TexCoords = a_TexCoords;
	
	
	gl_Position = (matrices.projectionMatrix * matrices.viewMatrix * world) * a_Position;
	
}
