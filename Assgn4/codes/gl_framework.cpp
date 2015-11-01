#include "gl_framework.hpp"
#include "hierarchy_node.hpp"
#include "humanoid.hpp"
#include "droid.hpp"
#include "camera.hpp"

// extern GLfloat c_xrot, c_yrot, c_zrot;
extern Humanoid* humanoid;
extern Droid* droid;
extern csX75::HNode* curr_node;
extern Camera *camera;
extern bool enable_perspective, record_keyframe, playback;
extern GLint light1_on, light2_on;
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
		else if(!playback && key == GLFW_KEY_M && action == GLFW_PRESS){
			record_keyframe = true;
		}
		else if(key == GLFW_KEY_N && action == GLFW_PRESS){
			playback = !playback;
		}
		else if (!playback && key == GLFW_KEY_Z && action == GLFW_PRESS){
			curr_node = humanoid->get_current(TORSO_JOINT);
		}
		else if (key == GLFW_KEY_G && action == GLFW_PRESS && !playback){
			curr_node = humanoid->get_current(UPPER_ARM_RIGHT);
		}
		else if (key == GLFW_KEY_T && action == GLFW_PRESS && !playback){
			curr_node = humanoid->get_current(UPPER_ARM_LEFT);
		}
		else if (key == GLFW_KEY_H && action == GLFW_PRESS && !playback){
			curr_node = humanoid->get_current(ELBOW_RIGHT);
		}
		else if (key == GLFW_KEY_Y && action == GLFW_PRESS && !playback){
			curr_node = humanoid->get_current(ELBOW_LEFT);
		}
		else if (key == GLFW_KEY_J && action == GLFW_PRESS && !playback){
			curr_node = humanoid->get_current(WRIST_RIGHT);
		}
		else if (key == GLFW_KEY_U && action == GLFW_PRESS && !playback){
			curr_node = humanoid->get_current(WRIST_LEFT);
		}
		else if (key == GLFW_KEY_K && action == GLFW_PRESS && !playback){
			curr_node = humanoid->get_current(UPPER_LEG_RIGHT);
		}
		else if (key == GLFW_KEY_I && action == GLFW_PRESS && !playback){
			curr_node = humanoid->get_current(UPPER_LEG_LEFT);
		}
		else if (key == GLFW_KEY_F && action == GLFW_PRESS && !playback){
			curr_node = humanoid->get_current(HIP_JOINT);
		}
		else if (key == GLFW_KEY_B && action == GLFW_PRESS && !playback){
			curr_node = humanoid->get_current(HIP);
		}
		else if (key == GLFW_KEY_L && action == GLFW_PRESS && !playback){
			curr_node = humanoid->get_current(KNEE_RIGHT);
		}
		else if (key == GLFW_KEY_O && action == GLFW_PRESS && !playback){
			curr_node = humanoid->get_current(KNEE_LEFT);
		}
		else if (key == GLFW_KEY_SEMICOLON && action == GLFW_PRESS && !playback){
			curr_node = humanoid->get_current(FOOT_RIGHT);
		}
		else if (key == GLFW_KEY_P && action == GLFW_PRESS && !playback){
			curr_node = humanoid->get_current(FOOT_LEFT);
		}
		else if (key == GLFW_KEY_X && action == GLFW_PRESS && !playback){
			curr_node = humanoid->get_current(NECK);
		}
		else if (key == GLFW_KEY_1 && action == GLFW_PRESS && !playback){
			curr_node = droid->get_current(D_UPPER_LEG_LEFT);
		}
		else if (key == GLFW_KEY_2 && action == GLFW_PRESS && !playback){
			curr_node = droid->get_current(D_UPPER_LEG_RIGHT);
		}
		else if (key == GLFW_KEY_3 && action == GLFW_PRESS && !playback){
			curr_node = droid->get_current(D_KNEE_LEFT);
		}
		else if (key == GLFW_KEY_4 && action == GLFW_PRESS && !playback){
			curr_node = droid->get_current(D_KNEE_RIGHT);
		}
		else if (key == GLFW_KEY_5 && action == GLFW_PRESS && !playback){
			curr_node = droid->get_current(D_TORSO);
		}
		else if (key == GLFW_KEY_6 && action == GLFW_PRESS && !playback){
			curr_node = droid->get_current(D_HEAD);
		}
		else if (key == GLFW_KEY_COMMA && action == GLFW_PRESS && !playback){
			if(light1_on == 1)
				light1_on = 0;
			else light1_on = 1;
			std::cout<<"Light 1: "<<light1_on<<std::endl;
		}
		else if (key == GLFW_KEY_SLASH && action == GLFW_PRESS && !playback){
			if(light2_on == 1)
				light2_on = 0;
			else light2_on = 1;
			std::cout<<"Light 2: "<<light2_on<<std::endl;
		}
		else if ((curr_node->ID == HIP || curr_node->ID == D_TORSO) && key == GLFW_KEY_LEFT && mods == GLFW_MOD_SHIFT && !playback)
			curr_node->dec_ty();
		else if ((curr_node->ID == HIP || curr_node->ID == D_TORSO) && key == GLFW_KEY_RIGHT && mods == GLFW_MOD_SHIFT && !playback)
			curr_node->inc_ty();
		else if ((curr_node->ID == HIP || curr_node->ID == D_TORSO) && key == GLFW_KEY_UP && mods == GLFW_MOD_SHIFT && !playback)
			curr_node->dec_tx();
		else if ((curr_node->ID == HIP || curr_node->ID == D_TORSO) && key == GLFW_KEY_DOWN && mods == GLFW_MOD_SHIFT && !playback)
			curr_node->inc_tx();
		else if ((curr_node->ID == HIP || curr_node->ID == D_TORSO) && key == GLFW_KEY_PAGE_UP && mods == GLFW_MOD_SHIFT && !playback)
			curr_node->dec_tz();
		else if ((curr_node->ID == HIP || curr_node->ID == D_TORSO) && key == GLFW_KEY_PAGE_DOWN && mods == GLFW_MOD_SHIFT && !playback)
			curr_node->inc_tz();
		else if (key == GLFW_KEY_LEFT && !playback)
			curr_node->dec_ry();
		else if (key == GLFW_KEY_RIGHT && !playback)
			curr_node->inc_ry();
		else if (key == GLFW_KEY_UP && !playback)
			curr_node->dec_rx();
		else if (key == GLFW_KEY_DOWN && !playback)
			curr_node->inc_rx();
		else if (key == GLFW_KEY_PAGE_UP && !playback)
			curr_node->dec_rz();
		else if (key == GLFW_KEY_PAGE_DOWN && !playback)
			curr_node->inc_rz();
		else if (key == GLFW_KEY_P && action == GLFW_PRESS && !playback)
			enable_perspective = !enable_perspective;
		else if (key == GLFW_KEY_A && mods == GLFW_MOD_SHIFT && !playback)
			camera->update_y(0, 2.0);
		else if (key == GLFW_KEY_A && !playback)
			camera->update_y(2.0,0);
		else if (key == GLFW_KEY_D && mods == GLFW_MOD_SHIFT && !playback)
			camera->update_y(0, -2.0);
		else if (key == GLFW_KEY_D && !playback)
			camera->update_y(-2.0,0);
		else if (key == GLFW_KEY_W  && mods == GLFW_MOD_SHIFT && !playback)
			camera->update_x(0, 2.0);
		else if (key == GLFW_KEY_W && !playback)
			camera->update_x(2.0,0);
		else if (key == GLFW_KEY_S && mods == GLFW_MOD_SHIFT && !playback)
			camera->update_x(0, -2.0);
		else if (key == GLFW_KEY_S && !playback)
			camera->update_x(-2.0,0);
		else if (key == GLFW_KEY_Q && mods == GLFW_MOD_SHIFT && !playback)
			camera->update_z(0, 2.0);
		else if (key == GLFW_KEY_Q && !playback)
			camera->update_z(2.0, 0);
		else if (key == GLFW_KEY_E  && mods == GLFW_MOD_SHIFT && !playback)
			camera->update_z(0, -2.0);
		else if (key == GLFW_KEY_E && !playback)
			camera->update_z(-2.0, 0);
	}
}; 