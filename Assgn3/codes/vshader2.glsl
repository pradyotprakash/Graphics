#version 130 

in vec4 vPosition;
in vec4 vColor;
in vec3 vNormal;

out vec4 color;
uniform mat4 uModelViewMatrix;
uniform mat3 normalMatrix;
uniform mat4 viewMatrix;

void main (void) 
{
 // Defining Materials
  vec4 diffuse = vec4(0.5, 0.5, 0.5, 1.0); 
  vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
  vec4 specular = vec4(0.5, 0.5, 0.5, 1.0);
  float shininess = 0.05;
  vec4 spec1 = vec4(0.0), spec2 = vec4(0.0); 
  
  vec3 n = normalize(normalMatrix * normalize(vNormal));


  gl_Position = uModelViewMatrix*vPosition;
    
 

  // Defining Light1 
  vec4 light1Pos = vec4(0.0, 0.0, 10.0, 0.0);
  vec3 light1Dir = vec3(viewMatrix * light1Pos); 
  light1Dir = normalize(light1Dir);  
  float dotProduct1 = dot(n, light1Dir);
  float intensity1 =  max( dotProduct1, 0.0);
    // Compute specular component only if light falls on vertex
  if(intensity1 > 0.0)
  {
	vec3 eye1 = normalize( vec3(-gl_Position));
	vec3 h1 = normalize(light1Dir + eye1 );
   	float intSpec1 = max(dot(h1,n), 0.0);	
        spec1 = specular * pow(intSpec1, shininess);
  }  	
 

  // Defining Light2 
  vec4 light2Pos = vec4(-10.0, 10.0, 10.0, 1.0);
  vec3 light2Dir = vec3(viewMatrix * light2Pos); 
  light2Dir = normalize(light2Dir);  
  float dotProduct2 = dot(n, light2Dir);
  float intensity2 =  max( dotProduct2, 0.0);
    // Compute specular component only if light falls on vertex
  if(intensity2 > 0.0)
  {
	vec3 eye2 = normalize( vec3(-gl_Position));
	vec3 h2 = normalize(light2Dir + eye2 );
   	float intSpec2 = max(dot(h2,n), 0.0);	
        spec2 = specular * pow(intSpec2, shininess);
  }  	

//spotlight
   
vec4  lightPositionOC = vec4(1.0,1.0,1.0,1.0);   // in object coordinates
vec3  spotDirectionOC = vec3(viewMatrix * lightPositionOC);   // in object coordinates
float spotCutoff = 10.0;        // in degrees

   vec3 lightPosition = vec3(1.0,1.0,1.0);;
   vec3 spotDirection;// = -lightPosition;
   vec3 lightDirection;
   float angle;

    // Transforms light position and direction into eye coordinates
    lightPosition  = (lightPositionOC * uModelViewMatrix).xyz;
    spotDirection  = normalize(spotDirectionOC*normalMatrix);

    // Calculates the light vector (vector from light position to vertex)
    vec4 vertex = uModelViewMatrix * vPosition;
    lightDirection = normalize(vertex.xyz - lightPosition.xyz);

    // Calculates the angle between the spot light direction vector and the light vector
    angle = dot( normalize(spotDirection),
                -normalize(lightDirection));
    //angle = max(angle,0);   

   // Test whether vertex is located in the cone
  // if(acos(angle) < radians(spotCutoff))
    //  color = vec4(1,1,0,1); // lit (yellow)
   //else
  		color = max(((intensity1 * diffuse  + spec1) )*vColor  , ambient); // All
}
