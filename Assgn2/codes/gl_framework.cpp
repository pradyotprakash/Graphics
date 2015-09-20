#include "gl_framework.hpp"

extern GLuint pressed1, pressed2, pressed3, pressed4;

namespace csX75
{
  //! Initialize GL State
  void initGL(void)
  {
    //Set framebuffer clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //Set depth buffer furthest depth
    glClearDepth(1.0);
    //Set depth test to less-than
    glDepthFunc(GL_LESS);
    //Enable depth testing
    glEnable(GL_DEPTH_TEST);
  }
  
  //!GLFW Error Callback
  void error_callback(int error, const char* description)
  {
    std::cerr<<description<<std::endl;
  }
  
  //!GLFW framebuffer resize callback
  void framebuffer_size_callback(GLFWwindow* window, int width, int height)
  {
    //!Resize the viewport to fit the window size - draw to entire window
    glViewport(0, 0, width, height);
  }
  
  //!GLFW keyboard callback
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
    pressed1 = 0; pressed2 = 0; pressed3 = 0; pressed4 = 0; 
    
    //!Close the window if the ESC key was pressed
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);
    else if (key == GLFW_KEY_1 && action == GLFW_PRESS){
      pressed1 = 1;
    }
    else if (key == GLFW_KEY_2 && action == GLFW_PRESS){
      pressed2 = 1;
    }
    else if (key == GLFW_KEY_3 && action == GLFW_PRESS){
      pressed3 = 1;
    }
    else if (key == GLFW_KEY_4 && action == GLFW_PRESS){
      pressed4 = 1;
    } 
  }
};