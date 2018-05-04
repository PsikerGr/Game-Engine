
// INPUTS du Fragment Shader = OUTPUTS du Vertex Shader

#version 420 core

in vec3 TexCoords;

layout(binding = 0) uniform samplerCube skybox;

const vec3 camPos = vec3(0.0, 0.0, 10.0);



out vec4 FragColor;

void main(void)
{
    



//    float norm = sqrt((v_NormCoords.x * v_NormCoords.x + v_NormCoords.y * v_NormCoords.y + v_NormCoords.z * v_NormCoords.z));
//    vec3 normalize = vec3((v_NormCoords.x / norm), (v_NormCoords.y / norm), (v_NormCoords.z / norm));
//    float I = max(dot(lightDirection, normalize), 0.0);
//    vec3 diffuseColor = I * lightDiffuseColor;

    // variable predefinies OBLIGATOIRE en OUTPUT
    // vec4 gl_FragColor

    
     FragColor = texture(skybox, TexCoords);
}
