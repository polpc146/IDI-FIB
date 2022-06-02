#version 330 core

in vec3 fcolor;
in vec4 vertexSCO;
in vec3 normSCO;
in vec3 matambF;
in vec3 matdiffF;
in vec3 matspecF;
in float matshinF;

uniform vec3 posFocus;
uniform vec3 colorFocus;

out vec4 FragColor;

// Valors per als components que necessitem del focus de llum
//vec3 colorFocus = vec3(0.8, 0.8, 0.8);
vec3 llumAmbient = vec3(0.2, 0.2, 0.2);
//vec3 posFocus = vec3(1, 0, 1);  // en SCA

vec3 Ambient() {
    return llumAmbient * matambF;
}

vec3 Difus (vec3 NormSCO, vec3 L, vec3 colFocus) 
{
    // Fixeu-vos que SOLS es retorna el terme difús
    // S'assumeix que els vectors que es reben com a paràmetres estan normalitzats
    vec3 colRes = vec3(0);
    // Càlcul component difusa, si n'hi ha
    if (dot (L, NormSCO) > 0)
      colRes = colFocus * matdiffF * dot (L, NormSCO);
    return (colRes);
}

vec3 Especular (vec3 NormSCO, vec3 L, vec4 vertSCO, vec3 colFocus) 
{
    // Fixeu-vos que SOLS es retorna el terme especular!
    // Assumim que els vectors estan normalitzats
    vec3 colRes = vec3 (0);
    // Si la llum ve de darrera o el material és mate no fem res
    if ((dot(NormSCO,L) < 0) || (matshinF == 0))
      return colRes;  // no hi ha component especular

    // Calculem R i V
    vec3 R = reflect(-L, NormSCO); // equival a: 2.0*dot(NormSCO,L)*NormSCO - L;
    vec3 V = normalize(-vertSCO.xyz); // perquè la càmera està a (0,0,0) en SCO

    if (dot(R, V) < 0)
      return colRes;  // no hi ha component especular
    
    float shine = pow(max(0.0, dot(R, V)), matshinF);
    return (matspecF * colFocus * shine); 
}

void main()
{	
    vec4 posFocusSCO = vec4 (posFocus, 1.0);
    vec3 L = normalize(posFocusSCO.xyz - vertexSCO.xyz);
    
    vec3 NnormSCO = normalize(normSCO);

	FragColor = vec4(Ambient() + Difus(NnormSCO, L, colorFocus) + Especular(NnormSCO, L, vertexSCO, colorFocus),1);	
}
