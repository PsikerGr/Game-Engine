#version 330 core

//layout (location = 0) in vec3 position;
out vec3 TexCoords;

layout (location = 0) in vec4 a_Position;


layout(std140) uniform MatrixBlock
{
	mat4 viewMatrix;
	mat4 projectionMatrix;
	mat4 model;
	
	
}	matrices;


// S'assurer que le cube 


void main(void)
{


	// variable predefinie OBLIGATOIRE en OUTPUT
	// varying vec4 gl_Position
	vec3 position = a_Position.xyz;
	vec4 pos = matrices.projectionMatrix  * matrices.viewMatrix * vec4(a_Position.xyz, 0.0);
	gl_Position = pos.xyww;
	TexCoords = position;
}

// out vec4 gl_Position -> Rasterizer

//[Vertex Shader]
//		|
//[Perspective Divide]
//		|
//Position3D = gl_Position.xyz / gl_Position.w;
//		|
//[Primitive Assembly] // si GL_TRIANGLE, on attends 3 vertex
//		|
//		Position2D = Position3D.xy / Position3D.z;
//[Rasterizer]

//glEnable(GL_DEPTH_TEST);

//glDepthFunc(GL_LESS) // la fonction de comparaison de depth test

//Par default, la fonction de test est inferieur strict (less)

//glDepthFunc();


//glDepthMask(false)
//drawCubeMap
//glDepthMask(true)