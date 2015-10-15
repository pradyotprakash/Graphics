#version 330

in vec4 tex;
out vec4 frag_color;
uniform samplerCube skybox;

void main () 
{
  vec3 x = vec3(tex);
  frag_color = texture(skybox, x);
}
