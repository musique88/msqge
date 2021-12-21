#version 330 core
out vec4 FragColor;
  
uniform vec4 color; // we set this variable in the OpenGL code.

void main()
{
    FragColor = color;
}