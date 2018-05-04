#version 330
#extension GL_ARB_shading_language_420pack : enable

out vec4 FragColor;

in vec2 v_TexCoords;
in vec4 v_Color;

uniform sampler2D u_Texture;

layout (std140, binding = 0) uniform MatrixBlock
{
    mat4 viewMatrix;
    mat4 projectionMatrix;
}   matrices;

void main(void)
{
	vec2 texCoords = vec2(v_TexCoords.x, 1.0 - v_TexCoords.y);
	vec4 texColor = texture2D(u_Texture, texCoords);
	FragColor = /*v_Color */ texColor;
	
}
