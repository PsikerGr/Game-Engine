#version 330 core
out vec4 color;
in vec2 TexCoords;

uniform sampler2D screenTex;

void main()
{             
   color = vec4(texture(screenTex, TexCoords).rgb, 1.0f);
   //color = vec4(vec3(1.0f, 1.0f, 1.0f) - color.xyz, 1.0f);
   //color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}
