#version 330

in vec4 tex;
out vec4 frag_color;
uniform samplerCube skybox;

flat in uint light1_on_o, light2_on_o;
uvec2 comp = uvec2(0, 1);
void main () 
{
  vec3 x = vec3(tex);
  vec4 ambient1 = vec4(0.0, 0.0, 0.0, 1.0);
  vec4 ambient2 = vec4(1.0, 1.0, 1.0, 1.0);
  vec4 ambient = vec4(normalize(vec3(ambient1) + vec3(ambient2)), 1.0);
  vec4 tex_col = texture(skybox, x);
  
  vec4 fc = vec4(ambient.x*tex_col.x, ambient.y*tex_col.y, ambient.z*tex_col.z, 1.0);
  vec4 fc1 = vec4(ambient1.x*tex_col.x, ambient1.y*tex_col.y, ambient1.z*tex_col.z, 1.0);
  vec4 fc2 = vec4(ambient2.x*tex_col.x, ambient2.y*tex_col.y, ambient2.z*tex_col.z, 1.0);

  if(light2_on_o == comp.y && light1_on_o == comp.y){
	  frag_color = fc;
  }
  else if(light2_on_o == comp.y && light1_on_o == comp.x){
   frag_color = fc2;
  }
  else if(light2_on_o == comp.x && light1_on_o == comp.y){
	frag_color = fc1;
  }
  else{
  	frag_color = 1*tex_col;
  }
}
