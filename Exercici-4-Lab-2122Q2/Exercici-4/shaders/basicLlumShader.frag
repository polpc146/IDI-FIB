#version 330 core

in vec3  fmatamb;
in vec3  fmatdiff;
in vec3  fmatspec;
in float fmatshin;
in vec3  fvertex;
in vec3  fnormal;

const vec3 llumAmbient = vec3(0.2, 0.2, 0.2);

uniform vec3 posFocusEsc;
const vec3 colorFocusEsc = vec3(0.9, 0.9, 0.9);
uniform vec3 posFocusCam;
const vec3 colorFocusCam = vec3(0.9, 0.0, 0.9);
uniform vec3 posFocusMod;
const vec3 colorFocusMod = vec3(0.9, 0.9, 0.2);

uniform mat4 TG;
uniform mat4 Proj;
uniform mat4 View;

out vec4 FragColor;


vec3 Ambient() {
  return llumAmbient*fmatamb;
}

vec3 Difus (vec3 NormSCO, vec3 L, vec3 colFocus)
{
  // Fixeu-vos que SOLS es retorna el terme de Lambert!
  // S'assumeix que els vectors que es reben com a paràmetres estan normalitzats
  vec3 colRes = vec3(0);
  if (dot (L, NormSCO) > 0)
    colRes = colFocus * fmatdiff * dot (L, NormSCO);
  return (colRes);
}

vec3 Especular (vec3 NormSCO, vec3 L, vec3 vertSCO, vec3 colFocus)
{
  // Fixeu-vos que SOLS es retorna el terme especular!
  // Assumim que els vectors estan normalitzats
  vec3 colRes = vec3 (0);
  // Si la llum ve de darrera o el material és mate no fem res
  if ((dot(NormSCO,L) < 0) || (fmatshin == 0))
    return colRes;  // no hi ha component especular

  vec3 R = reflect(-L, NormSCO); // equival a: 2.0*dot(NormSCO,L)*NormSCO - L;
  vec3 V = normalize(-vertSCO); // perquè la càmera està a (0,0,0) en SCO

  if (dot(R, V) < 0)
    return colRes;  // no hi ha component especular

  float shine = pow(max(0.0, dot(R, V)), fmatshin);
  return (colRes + fmatspec * colFocus * shine);
}

void main()
{

    vec4 posFocusEscSCO = View * vec4(posFocusEsc, 1.0);
    vec3 LEsc = normalize(posFocusEscSCO.xyz - fvertex);
    
    vec3 LCam = normalize(posFocusCam - fvertex);
    
    vec4 posFocusModSCO = View * TG * vec4(posFocusMod, 1.0);
    vec3 LMod = normalize(posFocusMod.xyz - fvertex);
    
    vec3 color;
    
    color = Ambient() + Difus(normalize(fnormal), LEsc, colorFocusEsc) + Difus(normalize(fnormal), LCam, colorFocusCam) + Difus(normalize(fnormal), LMod, colorFocusMod) + Especular(normalize(fnormal), LEsc, normalize(fvertex), colorFocusEsc) + Especular(normalize(fnormal), LCam, normalize(fvertex), colorFocusCam) + Especular(normalize(fnormal), LMod, normalize(fvertex), colorFocusMod);
    
    FragColor = vec4(color, 1.0);
}
