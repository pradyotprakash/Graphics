#include "laptop.hpp"
#include <utility>
#include <fstream>

#define pvec4 std::pair<glm::vec4, glm::vec4>

const int glmVec4Size = sizeof(glm::vec4);
const int window_x = 512;
const int window_y = 512;

GLuint shaderProgram;
GLuint vbo, vao;

unsigned int numOfPoints;

glm::mat4 transformation_matrix;
glm::mat4 ortho_matrix;
glm::mat4 modelview_matrix;
GLuint uModelViewMatrix;

std::string vs_file = "vs.glsl";
std::string fs_file = "fs.glsl";

std::vector<glm::vec4> v_positions_triangle;
std::vector<glm::vec4> v_colors_triangle;

std::vector<glm::vec4> v_added_position;
std::vector<glm::vec4> v_positions_line;

std::vector<glm::vec4> distinct_vertices;
glm::vec3 vertex_sum;
glm::vec3 centroid;

bool vec4equal(const glm::vec4 &vecA, const glm::vec4 &vecB) 
{ 
 const double epsilion = 0.00001;  // choose something apprpriate.

 return fabs(vecA[0] -vecB[0]) < epsilion   
	      && fabs(vecA[1] -vecB[1]) < epsilion   
	      && fabs(vecA[2] -vecB[2]) < epsilion; 
} 


std::vector<pvec4> vertices;
void initial_image(){



// vertices.push_back(pvec4(glm::vec4(-0.5, -0.5, 0.5, 1.0),glm::vec4(1,0,0,1)));
// vertices.push_back(pvec4(glm::vec4(-0.5, 0.5, 0.5, 1.0),glm::vec4(1,0,0,1)));
// vertices.push_back(pvec4(glm::vec4(0.5, 0.5, 0.5, 1.0),glm::vec4(1,0,0,1)));
// vertices.push_back(pvec4(glm::vec4(0.5, -0.5, 0.5, 1.0),glm::vec4(1,0,0,1)));
// vertices.push_back(pvec4(glm::vec4(-0.5, -0.5, -0.5, 1.0),glm::vec4(1,0,0,1)));
// vertices.push_back(pvec4(glm::vec4(-0.5, 0.5, -0.5, 1.0),glm::vec4(1,0,0,1)));
// vertices.push_back(pvec4(glm::vec4(0.5, 0.5, -0.5, 1.0),glm::vec4(1,0,0,1)));
// vertices.push_back(pvec4(glm::vec4(0.5, -0.5, -0.5, 1.0),glm::vec4(1,0,0,1)));

// outer screen
vertices.push_back(pvec4(glm::vec4(-0.75, -0.5, 0, 1), glm::vec4(0.0, 0.0, 1.0, 0.0)));
vertices.push_back(pvec4(glm::vec4(0.75, -0.5, 0, 1), glm::vec4(0.0, 0.0, 1.0, 0.0)));
vertices.push_back(pvec4(glm::vec4(0.75, 0.5, 0, 1), glm::vec4(0.0, 0.0, 1.0, 0.0)));
vertices.push_back(pvec4(glm::vec4(-0.75, 0.5, 0, 1), glm::vec4(0.0, 0.0, 1.0, 0.0)));

// on z-axis laptop

// outer rectangle
vertices.push_back(pvec4(glm::vec4(-0.75, -0.5, 0.02, 1), glm::vec4(0.0, 0.0, 0.0, 0.0)));
vertices.push_back(pvec4(glm::vec4(0.75, -0.5, 0.02, 1), glm::vec4(0.0, 0.0, 0.0, 0.0)));
vertices.push_back(pvec4(glm::vec4(0.75, 0.5, 0.02, 1), glm::vec4(0.0, 0.0, 0.0, 0.0)));
vertices.push_back(pvec4(glm::vec4(-0.75, 0.5, 0.02, 1), glm::vec4(0.0, 0.0, 0.0, 0.0)));

// inner rectangle
vertices.push_back(pvec4(glm::vec4(-0.6, -0.4, 0.02, 1), glm::vec4(1.0, 1.0, 1.0, 0.0)));
vertices.push_back(pvec4(glm::vec4(0.6, -0.4, 0.02, 1), glm::vec4(1.0, 1.0, 1.0, 0.0)));
vertices.push_back(pvec4(glm::vec4(0.6, 0.4, 0.02, 1), glm::vec4(1.0, 1.0, 1.0, 0.0)));
vertices.push_back(pvec4(glm::vec4(-0.6, 0.4, 0.02, 1), glm::vec4(1.0, 1.0, 1.0, 0.0)));

// upper base of the laptop
vertices.push_back(pvec4(glm::vec4(-0.75, -0.5 + 0.1, 1.5, 1), glm::vec4(0.5, 0.0, 1.0, 0.0)));
vertices.push_back(pvec4(glm::vec4(0.75, -0.5 + 0.1, 1.5, 1), glm::vec4(0.5, 0.0, 1.0, 0.0)));
vertices.push_back(pvec4(glm::vec4(0.75, -0.5 + 0.1, 0.02, 1), glm::vec4(0.5, 0.0, 1.0, 0.0)));
vertices.push_back(pvec4(glm::vec4(-0.75, -0.5 + 0.1, 0.02, 1), glm::vec4(0.5, 0.0, 1.0, 0.0)));

// lower base of the laptop
vertices.push_back(pvec4(glm::vec4(-0.75, -0.5, 1.5, 1), glm::vec4(.5, 0.0, 1.0, 0.0)));
vertices.push_back(pvec4(glm::vec4(0.75, -0.5, 1.5, 1), glm::vec4(.5, 0.0, 1.0, 0.0)));
vertices.push_back(pvec4(glm::vec4(0.75, -0.5, 0.02, 1), glm::vec4(.5, 0.0, 1.0, 0.0)));
vertices.push_back(pvec4(glm::vec4(-0.75, -0.5, 0.02, 1), glm::vec4(.5, 0.0, 1.0, 0.0)));

// keypad
vertices.push_back(pvec4(glm::vec4(-0.6, -0.5 + 0.1, 1.0, 1), glm::vec4(0.0, 0.0, 0.0, 0.0)));
vertices.push_back(pvec4(glm::vec4(0.6, -0.5 + 0.1, 1.0, 1), glm::vec4(0.0, 0.0, 0.0, 0.0)));
vertices.push_back(pvec4(glm::vec4(0.6, -0.5 + 0.1, 0.5, 1), glm::vec4(0.0, 0.0, 0.0, 0.0)));
vertices.push_back(pvec4(glm::vec4(-0.6, -0.5 + 0.1, 0.5, 1), glm::vec4(0.0, 0.0, 0.0, 0.0)));

// touchpad
vertices.push_back(pvec4(glm::vec4(-0.15, -0.5 + 0.1, 1.3, 1), glm::vec4(0.0, 0.0, 0.0, 0.0)));
vertices.push_back(pvec4(glm::vec4(0.15, -0.5 + 0.1, 1.3, 1), glm::vec4(0.0, 0.0, 0.0, 0.0)));
vertices.push_back(pvec4(glm::vec4(0.15, -0.5 + 0.1, 1.1, 1), glm::vec4(0.0, 0.0, 0.0, 0.0)));
vertices.push_back(pvec4(glm::vec4(-0.15, -0.5 + 0.1, 1.1, 1), glm::vec4(0.0, 0.0, 0.0, 0.0)));  

// display origin in red
// vertices.push_back(pvec4(glm::vec4(-0.01, -0.01, 0, 1), glm::vec4(0.0, 1.0, 0.0, 0.0)));
// vertices.push_back(pvec4(glm::vec4(-0.01, 0.01, 0, 1), glm::vec4(0.0, 1.0, 0.0, 0.0)));
// vertices.push_back(pvec4(glm::vec4(0.01, 0.01, 0, 1), glm::vec4(0.0, 1.0, 0.0, 0.0)));
// vertices.push_back(pvec4(glm::vec4(0.01, -0.01, 0, 1), glm::vec4(0.0, 1.0, 0.0, 0.0)));



numOfPoints = vertices.size();

for(int i=0;i<numOfPoints;++i){
	distinct_vertices.push_back(vertices[i].first);

	vertex_sum.x += distinct_vertices[i].x;
	vertex_sum.y += distinct_vertices[i].y;
	vertex_sum.z += distinct_vertices[i].z;
}

centroid = glm::vec3(vertex_sum.x/numOfPoints, vertex_sum.y/numOfPoints, vertex_sum.z/numOfPoints);
}


void quad(int a, int b, int c, int d)
{
v_colors_triangle.push_back(vertices[a].second); v_positions_triangle.push_back(vertices[a].first);
v_colors_triangle.push_back(vertices[b].second); v_positions_triangle.push_back(vertices[b].first);
v_colors_triangle.push_back(vertices[c].second); v_positions_triangle.push_back(vertices[c].first);
v_colors_triangle.push_back(vertices[a].second); v_positions_triangle.push_back(vertices[a].first);
v_colors_triangle.push_back(vertices[c].second); v_positions_triangle.push_back(vertices[c].first);
v_colors_triangle.push_back(vertices[d].second); v_positions_triangle.push_back(vertices[d].first);
}

void laptop(void)
{

initial_image();

// quad( 1, 0, 3, 2 );
//   quad( 2, 3, 7, 6 );
//   quad( 3, 0, 4, 7 );
//   quad( 6, 5, 1, 2 );
//   quad( 4, 5, 6, 7 );
//   quad( 5, 4, 0, 1 );

// back of the screen
quad(0, 1, 2, 3);

// 4 outer trapezoids of the display
quad(4, 5, 9, 9);
quad(5, 6, 9, 10);
quad(6, 7, 10, 11);
quad(7, 4, 11, 8);

// actual inner display
quad(8, 9, 10, 11);

// keypad surface
quad(12, 13, 14, 15);
// face opposite to the keypad
quad(16, 17, 18, 19);

// completing the rectangles encompassing the space between the upper
// and the lower surface
quad(12, 13, 17, 16);
quad(13, 14, 18, 17);
quad(14, 15, 19, 18);
quad(15, 12, 16, 19);

// similar thing as above for the display
quad(0, 1, 5, 4);
quad(1, 2, 6, 5);
quad(2, 3, 7, 6);
quad(3, 0, 4, 7);

// keypad
quad(20, 21, 22, 23);

// mouse
quad(24, 25, 26, 27);

// origin
// quad(8, 9, 10, 11);
}

void initBuffersGL(void)
{
if(!file_load && !centroid_translate)
	laptop();

glGenVertexArrays (1, &vao);
glBindVertexArray (vao);

glGenBuffers (1, &vbo);
glBindBuffer (GL_ARRAY_BUFFER, vbo);

int triangle_pos = v_positions_triangle.size()*glmVec4Size;
int triangle_color = v_colors_triangle.size()*glmVec4Size;

int totalSpace = triangle_pos + triangle_color;

glBufferData (GL_ARRAY_BUFFER, totalSpace, NULL, GL_STATIC_DRAW);
glBufferSubData( GL_ARRAY_BUFFER, 0, triangle_pos, &v_positions_triangle[0] );
glBufferSubData( GL_ARRAY_BUFFER, triangle_pos, triangle_color, &v_colors_triangle[0] );

// Load shaders and use the resulting shader program
std::string vertex_shader_file(vs_file);
std::string fragment_shader_file(fs_file);

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
glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(glmVec4Size*v_positions_triangle.size()) );

uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");
}

void load_from_file(){
	std::string file_name;
	std::string s;

	xpos = 0, ypos = 0, zpos = 0, xrot = 0, yrot = 0, zrot = 0;

	std::cout<<"Enter file name: ";
	getline(std::cin, file_name);

	std::ifstream inp(file_name.c_str());

	std::vector<glm::vec4> coor;
	std::vector<glm::vec4> color;
	GLfloat a, b, c, d, e, f;

	distinct_vertices.clear();
	vertex_sum = glm::vec3(0,0,0);
	numOfPoints = 0;

	while(inp>>a>>b>>c>>d>>e>>f){
	  glm::vec4 point = glm::vec4(a,b,c,1.0);
	  coor.push_back(point);
	  color.push_back(glm::vec4(d,e,f,0.0));

	  bool found = false;
	  for(int i=0;i<distinct_vertices.size();++i){
	    if(vec4equal(distinct_vertices[i], point)){
	      found = true;
	      break;
	    }
	  }

	  if(!found){
	    distinct_vertices.push_back(point);
	    vertex_sum.x += point.x, vertex_sum.y += point.y, vertex_sum.z += point.z;
	    numOfPoints++;
	  }
	}

	centroid = glm::vec3(vertex_sum.x/numOfPoints, vertex_sum.y/numOfPoints, vertex_sum.z/numOfPoints);
	
	swap(coor, v_positions_triangle);
	swap(color, v_colors_triangle);

	inp.close();

	initBuffersGL();
	file_load = 0;
}

void transform(){

glm::mat4 tr1 = glm::translate(glm::mat4(1.0f), glm::vec3(-centroid.x, -centroid.y, -centroid.z));

glm::mat4 rot1 = glm::rotate(glm::mat4(1.0f), xrot, glm::vec3(1.0f,0.0f,0.0f));
glm::mat4 rot2 = glm::rotate(glm::mat4(1.0f), yrot, glm::vec3(0.0f,1.0f,0.0f));
glm::mat4 rot3 = glm::rotate(glm::mat4(1.0f), zrot, glm::vec3(0.0f,0.0f,1.0f));

glm::mat4 tr2 = glm::translate(glm::mat4(1.0f), glm::vec3(centroid.x + xpos, centroid.y + ypos, centroid.z + zpos));
transformation_matrix = tr2*rot3*rot2*rot1*tr1; 
}

void write_to_file(){
	std::string file_name;
	
	std::cout << "Enter file name: ";
	getline(std::cin, file_name);
	
	std::ofstream out(file_name.c_str());
	
	for(int i=0;i<v_positions_triangle.size();++i){
	  glm::vec4 point = transformation_matrix*v_positions_triangle[i];
	  out<<point.x<<" "<<point.y<<" "<<point.z<<" ";
	  out<<v_colors_triangle[i].x<<" "<<v_colors_triangle[i].y<<" "<<v_colors_triangle[i].z<<"\n";
	}
	out.close();
	file_write = 0;
}

void set_centroid_as_origin(){
std::vector<glm::vec4> coor;

centroid = glm::vec3(0, 0, 0);
centroid_translate = 0; xpos = 0; ypos = 0; zpos = 0;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	  if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
	    double xpos, ypos;
	    glfwGetCursorPos(window, &xpos, &ypos); 
	    bool del = false;
	    std::cout<<xpos<<" "<<ypos<<std::endl;
	    float x,y;
	    	x= ( xpos - window_x/2)/(window_x/2);
	    	y= (ypos - window_y/2)/(window_y/2);
	    	std::cout<<x<<" "<<y<<" "<<zpos<<std::endl;
	    int state =glfwGetKey(window, GLFW_KEY_LEFT_SHIFT);
	    if( state == GLFW_PRESS)
	    {
	    del = true;	
	    }

	    if(del){
	    //	v_positions_triangle
	    }

	  }
}

void model(GLFWwindow* window){
		
	glfwSetMouseButtonCallback(window, mouse_button_callback);

}

void renderGL(void)
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

transform();

ortho_matrix = glm::ortho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);

modelview_matrix = ortho_matrix * transformation_matrix;

glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));

// Draw 
glDrawArrays(GL_TRIANGLES, 0, v_positions_triangle.size());

}

int main(int argc, char** argv)
{

numOfPoints = 0;

vertex_sum = glm::vec3(0,0,0);
centroid = glm::vec3(0,0,0);

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
window = glfwCreateWindow(window_x, window_y, "Laptop", NULL, NULL);
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
	   if(file_load){
	    load_from_file();
	   }

	   if(centroid_translate){
	    set_centroid_as_origin();
	   }
	  // Render here
	  renderGL();

	  if(file_write){
	    write_to_file();
	  }

	  if(modelling_enabled){
	    model(window);
	  }

	  // Swap front and back buffers
	  glfwSwapBuffers(window);
	  
	  // Poll for and process events
	  glfwPollEvents();
	}

glfwTerminate();
return 0;
}

