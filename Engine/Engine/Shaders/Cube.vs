#version 330
#extension GL_ARB_shading_language_420pack : enable

in vec3 a_Position;
in vec2 a_TexCoords;
in vec2 a_NormCoords;

out vec4 v_Color;

out vec2 v_TexCoords;
out vec2 v_NormCoords;

layout(std140, binding = 0) uniform CameraMatrices
{
	mat4 WorldMatrix;
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
} camera;

//layout(location = 0) uniform	WorldObjectMatrix[0];

void main (void)
{
	v_Color = vec4(0.0, 1.0, 0.0, 1.0);
	v_TexCoords = a_Position.xy * 0.5+0.5;//a_TexCoords;
	//v_NormCoords = a _TexCoords;

	// variable predefinie OBLIGATOIRE en OUTPUT
	// varying vec4 gl_Position


	gl_Position = (camera.ProjectionMatrix * camera.ViewMatrix * camera.WorldMatrix) * vec4(a_Position, 1.0);
}