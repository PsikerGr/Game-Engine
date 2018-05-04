
#version 330

layout (triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in VertexDataOut
{
	 vec2 v_TexCoords;
     vec3 v_NormCoords;
     vec3 v_Diffuse;
     vec3 v_Specular;
     vec3 v_Ambient;
     float v_Attenuation;
     vec4 v_Color;

}IN[];

out FragmentDataIn
{
     vec2 v_TexCoords;
     vec3 v_NormCoords;
     vec3 v_Diffuse;
     vec3 v_Specular;
     vec3 v_Ambient;
     float v_Attenuation;
     vec4 v_Color;
}OUT;

void main(void)
{
	for (int i = 0; i < IN.length(); i++)
	{
		gl_Position = gl_in[i].gl_Position;
		OUT.v_TexCoords = IN[i].v_TexCoords;
		OUT.v_NormCoords = IN[i].v_NormCoords;
		OUT.v_Diffuse = IN[i].v_Diffuse;
		OUT.v_Specular = IN[i].v_Specular;
		OUT.v_Ambient = IN[i].v_Ambient;
		OUT.v_Attenuation = IN[i].v_Attenuation;
		OUT.v_Color = IN[i].v_Color;
		EmitVertex();
	}


}