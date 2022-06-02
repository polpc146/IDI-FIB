#version 330 core

in vec3 vertex;
in vec3 color;
uniform float val;
uniform mat4 TG;
out vec3 fcolor;

void main()  {
    fcolor = color;
    gl_Position = TG * vec4 (vertex * val, 1.0);
}
