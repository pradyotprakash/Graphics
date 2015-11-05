#version 330

out vec4 frag_color;
in vec3 normal;
in vec4 eye;
in vec4 vPosition1;

uniform mat4 viewMatrix;
uniform mat3 normalMatrix;
uniform mat4 uModelViewMatrix;
uniform sampler2D texture;
varying vec2 tex;
uniform int light1_on, light2_on;

void main () {

    vec4 lightPos1 = vec4(1.0, 1.0, 1.0, 0.0);
    vec4 lightPos2 = vec4(-1.0, 1.0, 1.0, 0.0);
    
    vec4 texColor = texture2D(texture, tex);

    vec4 spec = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 ambient = vec4(0.3, 0.3, 1.0, 1.0);
    float intensity = 0.0;
    float shininess = 0.05;
   
        if(light1_on != 0) {
            float myDot = dot(normalize(vec3(lightPos1 - vPosition1)), normalize(normal));
            intensity = intensity + max(myDot, 0);
            
            if (myDot > 0) {
                spec = spec + pow(max(dot(normalize(vec3(eye - vPosition1) + vec3(lightPos1 - vPosition1)), normalize(normal)),0), shininess);
            }
        }

        if(light2_on != 0) {
            float myDot = dot(normalize(vec3(lightPos2 - vPosition1)), normalize(normal));
            intensity = intensity + max(myDot, 0);
            
            if (myDot > 0) {
                spec = spec + pow(max(dot(normalize(vec3(eye - vPosition1) + vec3(lightPos2 - vPosition1)), normalize(normal)),0), shininess);
            }
        }
    frag_color = vec4(vec3(ambient)/2 + vec3(texColor*intensity)/2 + vec3(spec)/2, 1.0);
}

// void main () 
// {
//   // Defining Materials
//   vec4 tex_col = texture2D(texture, tex);
//   vec4 diffuse = vec4(0.0, 0.5, 0.0, 1.0); 
//   vec4 ambient1 = vec4(0.3, 0.3, 0.3, 1.0);
//   vec4 ambient2 = vec4(0.2, 0.2, 0.2, 1.0);
//   //vec4 ambient = vec4(normalize(vec3(ambient1) + vec3(ambient2)), 1.0);

//   vec4 specular = vec4(0.0, 0.5, 0.5, 1.0);
//   float shininess = 0.05;
//   vec4 spec1 = vec4(0.0); 
//   vec4 spec2 = vec4(0.0); 

//   // // Defining Light 
//   vec4 lightPos1 = vec4(1.0, 1.0, 1.0, 0.0);
//   vec3 lightDir1 = normalize(vec3(viewMatrix * lightPos1));

//   vec4 lightPos2 = vec4(-1.0, 1.0, 1.0, 0.0);
//   vec3 lightDir2 = normalize(vec3(viewMatrix * lightPos2));

//   // lightDir1 = normalize( vec3(lightDir1));  
//   // lightDir2 = normalize( vec3(lightDir2));  
  
//   //Diffuse
//   vec3 n = normalize(vec3(normal));       
//   float dotProduct1 = dot(n, lightDir1);
//   float intensity1 =  max( dotProduct1, 0.0);

//   float dotProduct2 = dot(n, lightDir2);
//   float intensity2 =  max( dotProduct2, 0.0);

//   if(intensity1 > 0.0)
//   {
//  vec3 e = normalize(vec3(eye));
//  vec3 h = normalize(lightDir1 + e );
//      float intSpec1 = max(dot(h,n), 0.0);  
//         spec1 = specular * pow(intSpec1, shininess);
//   }

//   if(intensity2 > 0.0)
//   {
//  vec3 e = normalize(vec3(eye));
//  vec3 h = normalize(lightDir2 + e );
//      float intSpec2 = max(dot(h,n), 0.0);  
//         spec2 = specular * pow(intSpec2, shininess);
//   }

//   if(light2_on == 1 && light1_on == 1){
//    //frag_color = (intensity1 * diffuse  + spec1 + ambient1)*tex_col + (intensity2 * diffuse  + spec1 + ambient2)*tex_col;
//    frag_color = 0.5*(ambient1+ambient2)*tex_col;
//   }
//   else if(light2_on == 1 && light1_on == 0){
//        frag_color = (spec2+ambient2)*tex_col;
//      }
//   else if(light2_on == 0 && light1_on == 1){
//  frag_color = (ambient1+spec1)*tex_col;
//  }
//   else{
//    frag_color = tex_col;
//   }
// }