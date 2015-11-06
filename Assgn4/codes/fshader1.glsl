#version 330

in vec4 tex;
out vec4 frag_color;
uniform samplerCube skybox;

uniform int light1_on, light2_on;
uvec2 comp = uvec2(0, 1);
void main () 
{
  vec3 x = vec3(tex);
  vec4 ambient1 = vec4(1.0, 1.0, 1.0, 1.0);
  vec4 ambient2 = vec4(1.0, 1.0, 1.0, 1.0);
  vec4 ambient = vec4(normalize(vec3(ambient1) + vec3(ambient2)), 1.0);
  vec4 tex_col = texture(skybox, x);
  
  vec4 fc = vec4(ambient.x*tex_col.x, ambient.y*tex_col.y, ambient.z*tex_col.z, 1.0);
  vec4 fc1 = vec4(ambient1.x*tex_col.x, ambient1.y*tex_col.y, ambient1.z*tex_col.z, 1.0);
  vec4 fc2 = vec4(ambient2.x*tex_col.x, ambient2.y*tex_col.y, ambient2.z*tex_col.z, 1.0);

  if(light2_on == 1 && light1_on == 1){
    frag_color = fc;
  }
  else if(light2_on == 1 && light1_on == 0){
   frag_color = fc2;
  }
  else if(light2_on == 0 && light1_on == 1){
  frag_color = fc1;
  }
  else{
    frag_color = tex_col;
  }
}