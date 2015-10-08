#include "07_hierarchical_modelling.hpp"

GLuint shaderProgram;

glm::mat4 rotation_matrix;
glm::mat4 projection_matrix;
glm::mat4 c_rotation_matrix;
glm::mat4 lookat_matrix;

glm::mat4 model_matrix;
glm::mat4 view_matrix;


glm::mat4 modelview_matrix;

GLuint uModelViewMatrix;
const int num_vertices = 36;


//-----------------------------------------------------------------

//Eight vertices in homogenous coordinates
//elongated cuboid , basic arm in the hierarchy;

void make_pyramid(GLfloat height, GLfloat width, std::vector<glm::vec4> &v_positions, std::vector<glm::vec4> &v_colors ){

	glm::vec4 positions[5] = {
			glm::vec4(0.0, -height, 0.0, 1.0),
			glm::vec4(width/2, 0.0, width/2, 1.0),
			glm::vec4(width/2, 0.0, -width/2, 1.0),
			glm::vec4(-width/2, 0.0, width/2, 1.0),
			glm::vec4(-width/2, 0.0, -width/2, 1.0)
	};

	//RGBA colors

	v_positions.push_back(positions[0]);
	v_positions.push_back(positions[2]);
	v_positions.push_back(positions[1]);

	v_positions.push_back(positions[0]);
	v_positions.push_back(positions[1]);
	v_positions.push_back(positions[3]);

	v_positions.push_back(positions[0]);
	v_positions.push_back(positions[3]);
	v_positions.push_back(positions[4]);

	v_positions.push_back(positions[0]);
	v_positions.push_back(positions[4]);
	v_positions.push_back(positions[2]);

	v_positions.push_back(positions[3]);
	v_positions.push_back(positions[1]);
	v_positions.push_back(positions[2]);

	v_positions.push_back(positions[3]);
	v_positions.push_back(positions[2]);
	v_positions.push_back(positions[4]);


	for (int i = 0; i < v_positions.size(); ++i)
	{	
		v_colors.push_back(1.0,1.0,1.0,1.0);
		/* code */
	}

}


//-----------------------------------------------------------------

void initBuffersGL(void)
{

	// Load shaders and use the resulting shader program
	std::string vertex_shader_file("07_vshader.glsl");
	std::string fragment_shader_file("07_fshader.glsl");

	std::vector<GLuint> shaderList;
	shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
	shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

	shaderProgram = csX75::CreateProgramGL(shaderList);
	glUseProgram( shaderProgram );

	// getting the attributes from the shader program
	vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
	vColor = glGetAttribLocation( shaderProgram, "vColor" ); 
	uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");

	make_pyramid();

	note that the buffers are initialized in the respective constructors
	HNode::HNode(HNode* a_parent, GLuint num_v, glm::vec4* a_vertices, glm::vec4* a_colours, std::size_t v_size, std::size_t c_size){
	node1 = new csX75::HNode(NULL,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
	node2 = new csX75::HNode(node1,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
	node2->change_parameters(2.0,0.0,0.0,0.0,0.0,0.0);
	node3 = new csX75::HNode(node2,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
	node3->change_parameters(2.0,0.0,0.0,0.0,0.0,0.0);
	root_node = curr_node = node3;

}

void renderGL(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	matrixStack.clear();

	//Creating the lookat and the up vectors for the camera
	c_rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(c_xrot), glm::vec3(1.0f,0.0f,0.0f));
	c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_yrot), glm::vec3(0.0f,1.0f,0.0f));
	c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_zrot), glm::vec3(0.0f,0.0f,1.0f));

	glm::vec4 c_pos = glm::vec4(c_xpos,c_ypos,c_zpos, 1.0)*c_rotation_matrix;
	glm::vec4 c_up = glm::vec4(c_up_x,c_up_y,c_up_z, 1.0)*c_rotation_matrix;
	//Creating the lookat matrix
	lookat_matrix = glm::lookAt(glm::vec3(c_pos),glm::vec3(0.0),glm::vec3(c_up));

	//creating the projection matrix
	if(enable_perspective)
		projection_matrix = glm::frustum(-7.0, 7.0, -7.0, 7.0, 1.0, 7.0);
	//projection_matrix = glm::perspective(glm::radians(90.0),1.0,0.1,5.0);
	else
		projection_matrix = glm::ortho(-7.0, 7.0, -7.0, 7.0, -5.0, 5.0);

	view_matrix = projection_matrix*lookat_matrix;

	matrixStack.push_back(view_matrix);

	node1->render_tree();

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
	window = glfwCreateWindow(512, 512, "CS475/CS675 Tutorial 7: Hierarchical Modelling", NULL, NULL);
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

