#version 330

out vec4 frag_color;
out vec4 color;
in vec3 normal;
in vec4 eye;

uniform mat4 viewMatrix;

uniform sampler2D texture;
varying vec2 tex;

void main () 
{
    color = texture2D(texture, tex);
    //color = vec4(0.3,0.2,0.5,1.0);
    // Defining Materials
  vec4 diffuse = vec4(1, 0.0, 0.0, 1.0); 
  vec4 ambient = vec4(0.3, 0.3, 0.3, 1.0);
  vec4 specular = vec4(0, 0, 0, 1.0);
  float shininess = 0.05;
  vec4 spec = vec4(0.0); 

  // Defining Light 
  vec4 lightPos = vec4(10.0, 10.0, 10.0, 0.0);
  vec3 lightDir = vec3(viewMatrix * lightPos);  // Transforms with camera
  lightDir = normalize( vec3(lightDir));  

  //Diffuse
  vec3 n = normalize(vec3(normal));      
  float dotProduct = dot(n, lightDir);
  float intensity =  dotProduct;
  if(intensity < 0.0){
    intensity = -intensity;
  }


  // Compute specular component only if light falls on vertex
  if(intensity > 0.0)
  {
    vec3 e = normalize(vec3(eye));
    vec3 h = normalize(lightDir + e );
    float intSpec = max(dot(h,n), 0.0); 
    spec = specular * pow(intSpec, shininess);
  }  

  //vec4 color = 
 //frag_color = (intensity * diffuse)*color; // Only Diffuse  
    frag_color=color;
//frag_color = intensity*color; // All
}





