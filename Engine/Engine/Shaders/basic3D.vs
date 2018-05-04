
// INPUTS du Vertex Shader

// note: lorsqu'il n'y a qu'un seul 'attribute'
// on sait qu'il aura le 'location' 0

// le GPU rempli automatiquement les valeurs manquantes
// d'un attribute par 0.0 pour x,y,z et 1.0 pour w

#version 330




in vec4 a_Position; // x,y,z,?
in vec2 a_TexCoords;
in vec3 a_Normal;



out VertexDataOut 
{
	 vec2 v_TexCoords;
	 vec3 v_Normal;
	 vec3 v_Diffuse;
	 vec3 v_Specular;
	 vec3 v_Ambient;
	 float v_Attenuation;
	 vec4 v_Color;

} OUT;


layout(std140) uniform MatrixBlock
{
	mat4 viewMatrix;
	mat4 projectionMatrix;
	
	
}	matrices;


uniform mat4 worldMatrix;

const vec3 lightPos = vec3(-1.41, 0.0, 0.0);
const vec3 camPos = vec3(0.0, 0.0, 10.0);
float shininess = 10.0;

const vec3 specularLightColor = vec3(1.0, 1.0, 0.0);
const vec3 specularMaterialColor = vec3(0.0, 1.0, 0.0);
const vec3 ambientColor = vec3(0.0, 0.0, 1.0);
float ambiantI = 1.0;
float lightAttenuation = 0.1;


void CalculateDiffuseLight(vec3 actualNormal, vec3 lightDir);
void CalculateSpecularLight(vec3 actualNormal, vec3 lightDir);
void CalculateAmbientLight();



void CalculateDiffuseLight(vec3 actualNormal, vec3 lightDir)
{
	float cosTheta = dot(actualNormal, lightDir);
	float I = max(cosTheta, 0.0);
	OUT.v_Diffuse = I * vec3(0.0, 1.0, 1.0);
}

void CalculateSpecularLight(vec3 actualNormal, vec3 lightDir)
{
	vec3 camDir = normalize(camPos - worldMatrix[3].xyz);
	vec3 R = reflect(-lightDir, actualNormal);
	float frontFacing = (dot(actualNormal, lightDir) > 0.0) ? 1.0 : 0.0;

	OUT.v_Specular = specularLightColor * specularMaterialColor * frontFacing * pow(max(dot(camDir, R),0) , shininess);
}

void CalculateAmbientLight()
{
	OUT.v_Ambient = ambientColor * ambiantI;
}


void main(void)
{
	OUT.v_Color = abs(a_Position);
	OUT.v_TexCoords = a_TexCoords;
	
	vec4 newNormal = worldMatrix * vec4(a_Normal.xyz, 0.0);
	vec3 actualNormal = normalize(vec3(newNormal.xyz));
	vec3 lightDir = normalize(lightPos - worldMatrix[3].xyz);
	float distanceToLigth = length(lightPos - worldMatrix[3].xyz);
	float attenuation = 1.0/(1.0 + lightAttenuation * pow(distanceToLigth, 2.0));
	OUT.v_Attenuation = attenuation;
	CalculateDiffuseLight(actualNormal, lightDir);
	CalculateSpecularLight(actualNormal, lightDir);
	CalculateAmbientLight();
	//v_Normal = a_Normal;


	// variable predefinie OBLIGATOIRE en OUTPUT
	// varying vec4 gl_Position


	gl_Position = /*matrices.projectionMatrix  * matrices.viewMatrix * worldMatrix **/  a_Position;// * test;
}
