/*
  CSX75 Tutorial 3

  A program which opens a window and draws the "color cube."

  Use the arrow keys and +/-, PgUp,PgDn, Home,End, Ins,Del 
  keys to make the cube move.

  Use w/W to toggle between wireframe and solid models
  Use c/C to toggle backface culling on/off

  Modified from An Introduction to OpenGL Programming, 
  Ed Angel and Dave Shreiner, SIGGRAPH 2013

  Written by Parag Chaudhuri, 2015
*/


#include "03_colorcube_rotate.hpp"

GLuint shaderProgram;
GLuint vbo, vao;

glm::mat4 rotation_matrix;
GLuint uRotationMatrix;

//-----------------------------------------------------------------

//6 faces, 2 triangles/face, 3 vertices/triangle
const int num_vertices = 36*3;

//Eight vertices in homogenous coordinates
glm::vec4 positions[8] = {
	glm::vec4(0.25, -0.05, 0.05, 1.0),
	glm::vec4(0.25, 0.05, 0.05, 1.0),
	glm::vec4(0.85, 0.05, 0.05, 1.0),
	glm::vec4(0.85, -0.05, 0.05, 1.0),
	glm::vec4(0.25, -0.05, -0.05, 1.0),
	glm::vec4(0.25, 0.05, -0.05, 1.0),
	glm::vec4(0.85, 0.05, -0.05, 1.0),
	glm::vec4(0.85, -0.05, -0.05, 1.0)
  
};

glm::vec4 positions1[8] = {
	glm::vec4(-0.17, 0.19, 0.05, 1.0),
	glm::vec4(-0.47, 0.71, 0.05, 1.0),
	glm::vec4(-0.38, 0.76, 0.05, 1.0),
	glm::vec4(-0.08, 0.24, 0.05, 1.0),
	glm::vec4(-0.17, 0.19, -0.05, 1.0),
	glm::vec4(-0.47, 0.71, -0.05, 1.0),
	glm::vec4(-0.38, 0.76, -0.05, 1.0),
	glm::vec4(-0.08, 0.24, -0.05, 1.0)
};

glm::vec4 positions2[8] = {
	glm::vec4(-0.17, -0.19, 0.05, 1.0),
	glm::vec4(-0.47, -0.71, 0.05, 1.0),
	glm::vec4(-0.38, -0.76, 0.05, 1.0),
	glm::vec4(-0.08, -0.24, 0.05, 1.0),
	glm::vec4(-0.17, -0.19, -0.05, 1.0),
	glm::vec4(-0.47, -0.71, -0.05, 1.0),
	glm::vec4(-0.38, -0.76, -0.05, 1.0),
	glm::vec4(-0.08, -0.24, -0.05, 1.0)
};


//RGBA colors
glm::vec4 colors[8] = {
	glm::vec4(1.0, 1.0, 1.0, 1.0),
	glm::vec4(1.0, 1.0, 1.0, 1.0),
	glm::vec4(1.0, 1.0, 1.0, 1.0),
	glm::vec4(1.0, 1.0, 1.0, 1.0),
	glm::vec4(1.0, 1.0, 1.0, 1.0),
	glm::vec4(1.0, 1.0, 1.0, 1.0),
	glm::vec4(1.0, 1.0, 1.0, 1.0),
	glm::vec4(1.0, 1.0, 1.0, 1.0)
};

int tri_idx=0;
glm::vec4 v_positions[num_vertices+4000];
std::vector<glm::vec4> v_positions1;
glm::vec4 v_colors[num_vertices+4000];
std::vector<glm::vec4> v_colors1;

// quad generates two triangles for each face and assigns colors to the vertices
void quad(int a, int b, int c, int d)
{
  /*v_colors[tri_idx] = colors[a]; v_positions[tri_idx] = positions[a]; tri_idx++;
  v_colors[tri_idx] = colors[b]; v_positions[tri_idx] = positions[b]; tri_idx++;
  v_colors[tri_idx] = colors[c]; v_positions[tri_idx] = positions[c]; tri_idx++;
  v_colors[tri_idx] = colors[a]; v_positions[tri_idx] = positions[a]; tri_idx++;
  v_colors[tri_idx] = colors[c]; v_positions[tri_idx] = positions[c]; tri_idx++;
  v_colors[tri_idx] = colors[d]; v_positions[tri_idx] = positions[d]; tri_idx++;
 */
	 v_colors1.push_back(colors[a]); v_positions1.push_back(positions[a]); tri_idx++;
	 v_colors1.push_back(colors[b]); v_positions1.push_back(positions[b]); tri_idx++;
	 v_colors1.push_back(colors[c]); v_positions1.push_back(positions[c]); tri_idx++;
	 v_colors1.push_back(colors[a]); v_positions1.push_back(positions[a]); tri_idx++;
	 v_colors1.push_back(colors[c]); v_positions1.push_back(positions[c]); tri_idx++;
	 v_colors1.push_back(colors[d]); v_positions1.push_back(positions[d]); tri_idx++;

 }

void quad1(int a, int b, int c, int d)
{
	v_colors1.push_back(colors[a]); v_positions1.push_back(positions1[a]); tri_idx++;
	v_colors1.push_back(colors[b]); v_positions1.push_back(positions1[b]); tri_idx++;
	v_colors1.push_back(colors[c]); v_positions1.push_back(positions1[c]); tri_idx++;
	v_colors1.push_back(colors[a]); v_positions1.push_back(positions1[a]); tri_idx++;
	v_colors1.push_back(colors[c]); v_positions1.push_back(positions1[c]); tri_idx++;
	v_colors1.push_back(colors[d]); v_positions1.push_back(positions1[d]); tri_idx++;
}

void quad2(int a, int b, int c, int d)
{
	v_colors1.push_back(colors[a]); v_positions1.push_back(positions2[a]); tri_idx++;
	v_colors1.push_back(colors[b]); v_positions1.push_back(positions2[b]); tri_idx++;
	v_colors1.push_back(colors[c]); v_positions1.push_back(positions2[c]); tri_idx++;
	v_colors1.push_back(colors[a]); v_positions1.push_back(positions2[a]); tri_idx++;
	v_colors1.push_back(colors[c]); v_positions1.push_back(positions2[c]); tri_idx++;
	v_colors1.push_back(colors[d]); v_positions1.push_back(positions2[d]); tri_idx++;
}

// generate 12 triangles: 36 vertices and 36 colors
void colorcube(void)
{
    quad( 1, 0, 3, 2 );
    quad( 2, 3, 7, 6 );
    quad( 3, 0, 4, 7 );
    quad( 6, 5, 1, 2 );
    quad( 4, 5, 6, 7 );
    quad( 5, 4, 0, 1 );
	std::cout << "After cube1: " << tri_idx<< std::endl;
	quad1(1, 0, 3, 2);
	quad1(2, 3, 7, 6);
	quad1(3, 0, 4, 7);
	quad1(6, 5, 1, 2);
	quad1(4, 5, 6, 7);
	quad1(5, 4, 0, 1);
	std::cout << "After cube2: " << tri_idx << std::endl;
	quad2(1, 0, 3, 2);
	quad2(2, 3, 7, 6);
	quad2(3, 0, 4, 7);
	quad2(6, 5, 1, 2);
	quad2(4, 5, 6, 7);
	quad2(5, 4, 0, 1);
	std::cout << "After cube3: " << tri_idx << std::endl;

}


void DrawCircle(float cx, float cy,float cz, float r, int num_segments)
{
	//glBegin(GL_LINE_LOOP);
	for (int ii = 0; ii < num_segments; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle

		float x = r * cosf(theta);//calculate the x component
		float y = r * sinf(theta);//calculate the y component
		v_positions1.push_back(glm::vec4(cx, cy, 0.0, 1.0));//output vertex
		v_colors1.push_back(glm::vec4(1.0, 1.0, 1.0, 1.0));
		tri_idx++;
		v_positions1.push_back(glm::vec4 (x + cx,y + cy,0.0,1.0));//output vertex
		v_colors1.push_back(glm::vec4(1.0, 1.0, 1.0, 1.0));
		tri_idx++;
	}
	std::cout << "After circle: " << tri_idx << std::endl;
	//glEnd();
}

void DrawCylinder(float length,float radius,int numSteps ) {
		float hl = length * 0.5f;
		float a = 0.0f;
		float step = 2.0f * 3.1415926f / (float)numSteps;

	//glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < numSteps; ++i)
	{
		float x = cosf(a) * radius;
		float y = sinf(a) * radius;
		v_positions1.push_back(glm::vec4(x, y, -hl,1.0));
		v_colors1.push_back(glm::vec4(1.0, 1.0, 1.0, 1.0));
		tri_idx++;
		v_positions1.push_back(glm::vec4(x, y, hl,1.0));
		v_colors1.push_back(glm::vec4(1.0, 1.0, 1.0, 1.0));
		tri_idx++;
		a += step;
	}
	//glEnd();

}


//-----------------------------------------------------------------

void initBuffersGL(void)
{
  colorcube();
  DrawCircle(0.0, 0.0, 0.075, 0.15, 1000);
  DrawCylinder(0.3, 0.15, 1000);
  //Ask GL for a Vertex Attribute Object (vao)
  glGenVertexArrays (1, &vao);
  //Set it as the current array to be used by binding it
  glBindVertexArray (vao);

  //Ask GL for a Vertex Buffer Object (vbo)
  glGenBuffers (1, &vbo);
  //Set it as the current buffer to be used by binding it
  glBindBuffer (GL_ARRAY_BUFFER, vbo);
  //Copy the points into the current buffer
  glBufferData (GL_ARRAY_BUFFER, sizeof (glm::vec4)* v_positions1.size() + sizeof(glm::vec4)* v_colors1.size(), NULL, GL_STATIC_DRAW);
  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(glm::vec4)* v_positions1.size(), &v_positions1[0] );
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(glm::vec4)* v_positions1.size(), sizeof(glm::vec4)* v_colors1.size(), &v_colors1[0] );

  // Load shaders and use the resulting shader program
  std::string vertex_shader_file("03_vshader.glsl");
  std::string fragment_shader_file("03_fshader.glsl");

  std::vector<GLuint> shaderList;
  shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
  shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

  shaderProgram = csX75::CreateProgramGL(shaderList);
  glUseProgram( shaderProgram );

  // set up vertex arrays
  GLuint vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
  glEnableVertexAttribArray( vPosition );
  glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  
  GLuint vColor = glGetAttribLocation( shaderProgram, "vColor" ); 
  glEnableVertexAttribArray( vColor );
  glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(glm::vec4)* v_positions1.size()) );

  uRotationMatrix = glGetUniformLocation( shaderProgram, "uRotationMatrix");
}

void renderGL(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  rotation_matrix = glm::rotate(glm::mat4(1.0f), xrot, glm::vec3(1.0f,0.0f,0.0f));
  rotation_matrix = glm::rotate(rotation_matrix, yrot, glm::vec3(0.0f,1.0f,0.0f));
  rotation_matrix = glm::rotate(rotation_matrix, zrot, glm::vec3(0.0f,0.0f,1.0f));
  glUniformMatrix4fv(uRotationMatrix, 1, GL_FALSE, glm::value_ptr(rotation_matrix));
  // Draw 
  glDrawArrays(GL_TRIANGLES, 0, num_vertices);
  glDrawArrays(GL_TRIANGLES, num_vertices , 2000);
  glDrawArrays(GL_TRIANGLE_STRIP, num_vertices+2000, 2000);
}

int main(int argc, char** argv)
{
  //! The pointer to the GLFW window
  GLFWwindow* window;

  //! Setting up the GLFW Error callback	
  glfwSetErrorCallback(csX75::error_callback);

  //! Initialize GLFW
  if (!glfwInit())
    return -1;

  //We want OpenGL 4.0
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  //This is for MacOSX - can be omitted otherwise
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
  //We don't want the old OpenGL 
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

  //! Create a windowed mode window and its OpenGL context
  window = glfwCreateWindow(512, 512, "CS475/CS675 Tutorial 3: Rotating  Colorcube", NULL, NULL);
  if (!window)
    {
      glfwTerminate();
      return -1;
    }
  
  //! Make the window's context current 
  glfwMakeContextCurrent(window);

  //Initialize GLEW
  //Turn this on to get Shader based OpenGL
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (GLEW_OK != err)
    {
      //Problem: glewInit failed, something is seriously wrong.
      std::cerr<<"GLEW Init Failed : %s"<<std::endl;
    }

  //Print and see what context got enabled
  std::cout<<"Vendor: "<<glGetString (GL_VENDOR)<<std::endl;
  std::cout<<"Renderer: "<<glGetString (GL_RENDERER)<<std::endl;
  std::cout<<"Version: "<<glGetString (GL_VERSION)<<std::endl;
  std::cout<<"GLSL Version: "<<glGetString (GL_SHADING_LANGUAGE_VERSION)<<std::endl;

  //Keyboard Callback
  glfwSetKeyCallback(window, csX75::key_callback);
  //Framebuffer resize callback
  glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  //Initialize GL state
  csX75::initGL();
  initBuffersGL();

  // Loop until the user closes the window
  while (glfwWindowShouldClose(window) == 0)
    {
       
      // Render here
      renderGL();

      // Swap front and back buffers
      glfwSwapBuffers(window);
      
      // Poll for and process events
      glfwPollEvents();
    }
  
  glfwTerminate();
  return 0;
}

//-------------------------------------------------------------------------

