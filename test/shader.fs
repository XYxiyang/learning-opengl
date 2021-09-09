#version 330 core
out vec4 Fragcolor;
in vec3 ourColor;
void main()
{
   Fragcolor=vec4(ourColor,1.0) ;
}