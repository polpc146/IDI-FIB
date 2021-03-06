#version 330 core

in vec3 vertex;
in vec3 normal;
in vec3 matamb;
in vec3 matdiff;
in vec3 matspec;
in float matshin;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 TG;

out vec4 vertexSCO;
out vec3 normSCO;
out vec3 matambF;
out vec3 matdiffF;
out vec3 matspecF;
out float matshinF;

void main()
{	
    vertexSCO = view * TG * vec4 (vertex, 1.0);
    
    mat3 NormalMatrix = inverse(transpose(mat3(view*TG)));
    normSCO = NormalMatrix * normal;
    
    matambF = matamb;
	matdiffF = matdiff;
	matspecF = matspec;
	matshinF = matshin;

    gl_Position = proj * view * TG * vec4 (vertex, 1.0);
}
