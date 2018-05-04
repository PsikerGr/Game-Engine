#version 330
#extension GL_ARB_shading_language_420pack : enable

in vec4 v_Color;

in vec2 v_TexCoords;

out vec4 FragColor;

uniform float u_Time;

uniform sampler2D u_Texture;

layout (std140, binding = 0) uniform CameraMatrices
{
    mat4 WorldMatrix;
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
} camera;

void main (void)
{
    vec2 texCoords = vec2(v_TexCoords.x,  v_TexCoords.y);
    vec4 texColor = texture2D(u_Texture, texCoords);

    
    FragColor = texColor;
}