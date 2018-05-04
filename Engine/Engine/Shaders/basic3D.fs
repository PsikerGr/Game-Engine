
// INPUTS du Fragment Shader = OUTPUTS du Vertex Shader

#version 330

in FragmentDataIn
{
     vec2 v_TexCoords;
     vec3 v_Normal;
     vec3 v_Diffuse;
     vec3 v_Specular;
     vec3 v_Ambient;
     float v_Attenuation;
     vec4 v_Color;
}IN;

uniform sampler2D u_Texture;


const vec3 lightDiffuseColor = vec3(1.0, 0.0, 1.0);
const vec3 lightMaterialColor = vec3(0.0, 1.0 , 1.0);


out vec4 FragColor;

void main(void)
{
    
    vec2 texCoords = vec2(IN.v_TexCoords.x, 1.0 - IN.v_TexCoords.y);
    vec4 texColor = texture2D(u_Texture, texCoords);
    vec4 finalColor =   texColor * vec4(IN.v_Ambient, 0.0) + IN.v_Attenuation * (vec4(IN.v_Diffuse, 0.0) + vec4(IN.v_Specular, 0.0)) ;



//    float norm = sqrt((v_NormCoords.x * v_NormCoords.x + v_NormCoords.y * v_NormCoords.y + v_NormCoords.z * v_NormCoords.z));
//    vec3 normalize = vec3((v_NormCoords.x / norm), (v_NormCoords.y / norm), (v_NormCoords.z / norm));
//    float I = max(dot(lightDirection, normalize), 0.0);
//    vec3 diffuseColor = I * lightDiffuseColor;

    // variable predefinies OBLIGATOIRE en OUTPUT
    // vec4 gl_FragColor

    
     FragColor = finalColor;
}
