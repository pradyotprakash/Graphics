#include "gl_framework.hpp"
#include "hierarchy_node.hpp"
#include "humanoid.hpp"
#include "camera.hpp"

// extern GLfloat c_xrot, c_yrot, c_zrot;
// extern bool enable_perspective;
extern Humanoid* humanoid;
extern csX75::HNode* curr_node;
extern Camera *camera;
extern bool enable_perspective;

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
		//!Close the window if the ESC key was pressed
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);
		else if (key == GLFW_KEY_Z && action == GLFW_PRESS){
			curr_node = humanoid->get_current(TORSO);
		}
		else if (key == GLFW_KEY_G && action == GLFW_PRESS){
			curr_node = humanoid->get_current(UPPER_ARM_RIGHT);
		}
		else if (key == GLFW_KEY_T && action == GLFW_PRESS){
			curr_node = humanoid->get_current(UPPER_ARM_LEFT);
		}
		else if (key == GLFW_KEY_H && action == GLFW_PRESS){
			curr_node = humanoid->get_current(LOWER_ARM_RIGHT);
		}
		else if (key == GLFW_KEY_Y && action == GLFW_PRESS){
			curr_node = humanoid->get_current(LOWER_ARM_LEFT);
		}
		else if (key == GLFW_KEY_J && action == GLFW_PRESS){
			curr_node = humanoid->get_current(WRIST_RIGHT);
		}
		else if (key == GLFW_KEY_U && action == GLFW_PRESS){
			curr_node = humanoid->get_current(WRIST_LEFT);
		}
		else if (key == GLFW_KEY_K && action == GLFW_PRESS){
			curr_node = humanoid->get_current(UPPER_LEG_RIGHT);
		}
		else if (key == GLFW_KEY_I && action == GLFW_PRESS){
			curr_node = humanoid->get_current(UPPER_LEG_LEFT);
		}
		else if (key == GLFW_KEY_L && action == GLFW_PRESS){
			curr_node = humanoid->get_current(LOWER_LEG_RIGHT);
		}
		else if (key == GLFW_KEY_O && action == GLFW_PRESS){
			curr_node = humanoid->get_current(LOWER_LEG_LEFT);
		}
		else if (key == GLFW_KEY_SEMICOLON && action == GLFW_PRESS){
			curr_node = humanoid->get_current(FOOT_RIGHT);
		}
		else if (key == GLFW_KEY_P && action == GLFW_PRESS){
			curr_node = humanoid->get_current(FOOT_LEFT);
		}
		else if (key == GLFW_KEY_X && action == GLFW_PRESS){
			curr_node = humanoid->get_current(NECK);
		}
		else if (key == GLFW_KEY_LEFT)
			curr_node->dec_ry();
		else if (key == GLFW_KEY_RIGHT)
			curr_node->inc_ry();
		else if (key == GLFW_KEY_UP)
			curr_node->dec_rx();
		else if (key == GLFW_KEY_DOWN)
			curr_node->inc_rx();
		else if (key == GLFW_KEY_PAGE_UP)
			curr_node->dec_rz();
		else if (key == GLFW_KEY_PAGE_DOWN)
			curr_node->inc_rz();
		else if (key == GLFW_KEY_P && action == GLFW_PRESS)
			enable_perspective = !enable_perspective;   
		else if (key == GLFW_KEY_A )
			camera->update_y(0, 1.0);
		else if (key == GLFW_KEY_D )
			camera->update_y(0, -1.0);
		else if (key == GLFW_KEY_W )
			camera->update_x(0, 1.0);
		else if (key == GLFW_KEY_S )
			camera->update_x(0, -1.0);
		else if (key == GLFW_KEY_Q )
			camera->update_z(0, -1.0);
		else if (key == GLFW_KEY_E )
			camera->update_z(0, 1.0);
	}
};  



