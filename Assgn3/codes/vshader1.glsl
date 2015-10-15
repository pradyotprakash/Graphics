#version 330

in vec4 vPosition;
out vec4 tex;
uniform mat4 uModelViewMatrix;

void main (void) 
{
  gl_Position = uModelViewMatrix * vPosition;
  tex = -vPosition;
}
