#version 330

in vec4 vPosition;
in uint light1_on, light2_on;
flat out uint light1_on_o, light2_on_o;
out vec4 tex;

uniform mat4 uModelViewMatrix;

void main (void) 
{
  gl_Position = uModelViewMatrix * vPosition;
  tex = -vPosition;
  light1_on_o = light1_on;
  light2_on_o = light2_on;

}
