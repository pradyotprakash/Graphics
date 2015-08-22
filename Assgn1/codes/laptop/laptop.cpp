#include "laptop.hpp"
#include <utility>
#include <fstream>

#define pvec4 std::pair<glm::vec4, glm::vec4>

const int glmVec4Size = sizeof(glm::vec4);

GLuint shaderProgram;
GLuint vbo, vao;

unsigned int numOfPoints;

glm::mat4 transformation_matrix;
glm::mat4 ortho_matrix;
glm::mat4 modelview_matrix;
GLuint uModelViewMatrix;

glm::mat4 translation_matrix;

std::string vs_file = "vs.glsl";
std::string fs_file = "fs.glsl";

std::vector<glm::vec4> v_positions_triangle;
std::vector<glm::vec4> v_colors_triangle;

std::vector<glm::vec4> v_colors_line;
std::vector<glm::vec4> v_positions_line;

std::vector<glm::vec4> distinct_vertices;
glm::vec4 vertex_sum;

bool vec4equal(const glm::vec4 &vecA, const glm::vec4 &vecB) 
{ 
   const double epsilion = 0.00001;  // choose something apprpriate.

   return fabs(vecA[0] -vecB[0]) < epsilion   
          && fabs(vecA[1] -vecB[1]) < epsilion   
          && fabs(vecA[2] -vecB[2]) < epsilion; 
} 





std::vector<pvec4> vertices;
void initial_image(){

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

  numOfPoints = vertices.size();
  
  for(int i=0;i<numOfPoints;++i){
    distinct_vertices.push_back(vertices[i].first);

    vertex_sum.x += distinct_vertices[i].x;
    vertex_sum.y += distinct_vertices[i].y;
    vertex_sum.z += distinct_vertices[i].z;
  }
}

void line(int a, int b){
  v_colors_line.push_back(vertices[a].second); v_positions_line.push_back(vertices[a].first);
  v_colors_line.push_back(vertices[b].second); v_positions_line.push_back(vertices[b].first);
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
}

void initBuffersGL(void)
{
  if(!file_load)
    laptop();

  glGenVertexArrays (1, &vao);
  glBindVertexArray (vao);

  glGenBuffers (1, &vbo);
  glBindBuffer (GL_ARRAY_BUFFER, vbo);

  int triangle_pos = v_positions_triangle.size()*glmVec4Size;
  int triangle_color = v_colors_triangle.size()*glmVec4Size;
  int line_pos = v_positions_line.size()*glmVec4Size;
  int line_color = v_colors_line.size()*glmVec4Size;

  int totalSpace = triangle_pos + triangle_color + line_pos + line_color;

  glBufferData (GL_ARRAY_BUFFER, totalSpace, NULL, GL_STATIC_DRAW);
  glBufferSubData( GL_ARRAY_BUFFER, 0, triangle_pos, &v_positions_triangle[0] );
  glBufferSubData( GL_ARRAY_BUFFER, triangle_pos, triangle_color, &v_colors_triangle[0] );
  glBufferSubData( GL_ARRAY_BUFFER, triangle_pos+triangle_color, line_pos, &v_positions_line[0] );
  glBufferSubData( GL_ARRAY_BUFFER, triangle_pos+triangle_color+line_pos, line_color, &v_colors_line[0] );

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

bool load_file(){
    std::string file_name;
    std::string s;

    std::cout<<"Enter file name: ";
    getline(std::cin, file_name);

    std::ifstream inp(file_name.c_str());

    std::vector<glm::vec4> coor;
    std::vector<glm::vec4> color;
    GLfloat a, b, c, d, e, f;

    distinct_vertices.clear();
    vertex_sum = glm::vec4(0,0,0,0);
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
    
    swap(coor, v_positions_triangle);
    swap(color, v_colors_triangle);

    inp.close();

    initBuffersGL();
    file_load = 0;
}

void renderGL(void)
{
  if(file_write){
    std::string file_name;
    
    std::cout << "Enter file name: ";
    getline(std::cin, file_name);
    
    std::ofstream out(file_name.c_str());
    
    for(int i=0;i<v_positions_triangle.size();++i){
      out<<v_positions_triangle[i].x<<" "<<v_positions_triangle[i].y<<" "<<v_positions_triangle[i].z<<" ";
      out<<v_colors_triangle[i].x<<" "<<v_colors_triangle[i].y<<" "<<v_colors_triangle[i].z<<"\n";
    }
    out.close();
    file_write = 0;
  }

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  transformation_matrix = glm::rotate(glm::mat4(1.0f), xrot, glm::vec3(1.0f,0.0f,0.0f));
  transformation_matrix = glm::rotate(transformation_matrix, yrot, glm::vec3(0.0f,1.0f,0.0f));
  transformation_matrix = glm::rotate(transformation_matrix, zrot, glm::vec3(0.0f,0.0f,1.0f));
  ortho_matrix = glm::ortho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);



  modelview_matrix = ortho_matrix * transformation_matrix;

  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));

  // Draw 
  glDrawArrays(GL_TRIANGLES, 0, v_positions_triangle.size());
  // glDrawArrays(GL_LINES, 0, v_positions_line.size());
  
}

int main(int argc, char** argv)
{

  numOfPoints = 0;

  vertex_sum.x = vertex_sum.y = vertex_sum.z = 0.0f;

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
  window = glfwCreateWindow(512, 512, "Laptop", NULL, NULL);
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
        load_file();
       }
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

