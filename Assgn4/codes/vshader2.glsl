#version 130

in vec4 vPosition;
in vec2 texCoord;
in vec3 vNormal;
uniform int light1_on, light2_on;

out vec3 normal;
out vec4 eye;
out vec4 vPosition1;

out vec2 tex;
uniform mat4 uModelViewMatrix;
uniform mat3 normalMatrix;
uniform mat4 viewMatrix;

void main (void)
{
  gl_Position = uModelViewMatrix * vPosition;
  vPosition1 = gl_Position;
  tex = texCoord;
  normal = (normalMatrix * normalize(vNormal)); 
  eye = - (uModelViewMatrix * gl_Position);
}