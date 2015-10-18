#include "starwars.hpp"
#include "texture.hpp"
#define PI 3.1415926

class Starwars{
public:
	GLuint shaderProgram1, shaderProgram2;

	glm::mat4 rotation_matrix;
	glm::mat4 projection_matrix;
	glm::mat4 c_rotation_matrix;
	glm::mat4 lookat_matrix;

	glm::mat4 model_matrix;
	glm::mat4 view_matrix;

	glm::mat4 modelview_matrix;

	std::vector<GLuint> vao_array, vbo_array;
	std::vector<int> num_vertices;
	std::vector<glm::vec2> t_coords;
	bool flag;
	GLfloat depth;

	Starwars(){
		humanoid = new Humanoid();
		camera = new Camera();

		t_coords.push_back(glm::vec2( 0.0, 0.0));
		t_coords.push_back(glm::vec2( 0.0, 1.0));
		t_coords.push_back(glm::vec2( 1.0, 0.0));
		t_coords.push_back(glm::vec2( 1.0, 1.0));

		flag = false;
		depth = 15.0f;
	}

	void make_pyramid(GLfloat height, GLfloat width, std::vector<glm::vec4> &v_positions, std::vector<glm::vec4> &v_colors, glm::vec4 object_color ){
		float x = depth;//15.0f;
		std::vector<glm::vec4> positions;
		
		positions.push_back( glm::vec4(0.0, -height, 0.0-x, 1.0));
		positions.push_back(glm::vec4(width/2, 0.0, width/2-x, 1.0));
		positions.push_back(glm::vec4(width/2, 0.0, -width/2-x, 1.0));
		positions.push_back(glm::vec4(-width/2, 0.0, width/2-x, 1.0));
		positions.push_back(glm::vec4(-width/2, 0.0, -width/2-x, 1.0));

		//RGBA colors
		v_positions.clear();
		
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

		v_colors.clear();
		for (int i = 0; i < v_positions.size(); ++i)
		{	
			v_colors.push_back(object_color);
			/* code */
		}
	}

	void make_triangle(float height, float width, float angle, std::vector<glm::vec4> &v_positions, std::vector<glm::vec4> &v_colors, glm::vec4 object_color){
		angle = angle*PI/180;
		float x = depth;//15.0f;
		v_positions.clear();
		v_positions.push_back(glm::vec4(width/2,0, 0.0-x, 1.0));
		v_positions.push_back(glm::vec4(height*cos(angle),height*sin(angle), 0.0-x, 1.0));
		v_positions.push_back(glm::vec4(-width/2,0, 0.0-x, 1.0));		

		v_colors.clear();
		for (int i = 0; i < v_positions.size(); ++i)
		{	
			v_colors.push_back(object_color);
			/* code */
		}
	}

	void draw_cylinder(float length, float radius, float radius1, int numSteps,std::vector<glm::vec4> &v_positions, std::vector<glm::vec4> &v_colors, glm::vec4 object_color) {
 		float hl = length;
 		float a = 0.0f;
 		float step = 2.0f * PI / (float)numSteps;
		float z = 0.0;
		float x = depth;//15.0f;
		v_positions.clear();

	 	for (int i = 0; i < numSteps; ++i)
		{
	 		float x1 = cosf(a) * radius;
	 		float y1 = sinf(a) * radius;
			float x2 = cosf(a) * radius1;
			float y2 = sinf(a) * radius1;
			float next_x1 = cosf(a + step)*radius;
			float next_y1 = sinf(a + step)*radius;
			float next_x2 = cosf(a + step)*radius1;
			float next_y2 = sinf(a + step)*radius1;
	 		v_positions.push_back(glm::vec4(x2, y2, hl-x, 1.0));
	 		v_positions.push_back(glm::vec4(x1, y1, 0.0-x, 1.0));
			v_positions.push_back(glm::vec4(next_x2,next_y2, hl-x, 1.0));
			v_positions.push_back(glm::vec4(next_x2, next_y2, hl-x, 1.0));
			v_positions.push_back(glm::vec4(next_x1, next_y1, 0-x, 1.0));
			v_positions.push_back(glm::vec4(x1, y1, 0-x, 1.0));
	 		a += step;
		}
		
		v_colors.clear();
		for (int i = 0; i < v_positions.size(); ++i)
		{	
			v_colors.push_back(object_color);
			/* code */
		}
	}

	void create_humanoid(){

		std::vector<glm::vec4> v_positions, v_colors;
		csX75::HNode* curr;
		
		// hip
		curr = humanoid->create_elem(v_positions, v_colors, 1);

		// torso
		make_pyramid(3, 1, v_positions, v_colors, glm::vec4(1,0,0,1));
		curr = humanoid->create_elem(v_positions, v_colors, 15);
		curr->change_parameters(0.0,1.0,0.0,0.0,0.0,0.0);
		
		// upper left leg
		make_pyramid(2.5, 0.8, v_positions, v_colors, glm::vec4(0,1,0,1));
		curr = humanoid->create_elem(v_positions, v_colors, 8);
		curr->change_parameters(-0.43,-2.75,0.0,0.0,0.0,-30);

		// left knee
		make_pyramid(0, 0, v_positions, v_colors, glm::vec4(0,0,0,1));
		curr = humanoid->create_elem(v_positions, v_colors, KNEE_LEFT);
		curr->change_parameters(0,-2.5,0,0,0,0);

		// lower left leg
		make_pyramid(2, 0.7, v_positions, v_colors, glm::vec4(0,0,1,1));
		curr = humanoid->create_elem(v_positions, v_colors, 10);
		curr->change_parameters(0.95,-1.6,0.0,0.0,0.0,30+180);

		// left leg foot
		make_triangle(1, 1, 90, v_positions, v_colors, glm::vec4(0.5,0.3,0.2,1));
		curr = humanoid->create_elem(v_positions, v_colors, 12);
		curr->change_parameters(0,0,0.5,90,0,0);

		// upper right leg
		make_pyramid(2.5, 0.8, v_positions, v_colors, glm::vec4(0,1,0,1));
		curr = humanoid->create_elem(v_positions, v_colors, 9);
		curr->change_parameters(0.43,-2.75,0.0,0.0,0.0,30);

		// right knee
		make_pyramid(0, 0, v_positions, v_colors, glm::vec4(0,0,0,1));
		curr = humanoid->create_elem(v_positions, v_colors, KNEE_RIGHT);
		curr->change_parameters(0,-2.5,0,0,0,0);

		// lower right leg
		make_pyramid(2, 0.7, v_positions, v_colors, glm::vec4(0,0,1,1));
		curr = humanoid->create_elem(v_positions, v_colors, 11);
		curr->change_parameters(-0.95,-1.6,0.0,0.0,0.0,-30+180);

		// right leg foot
		make_triangle(1, 1,90, v_positions, v_colors, glm::vec4(0.5,0.3,0.2,1));
		curr = humanoid->create_elem(v_positions, v_colors, 13);
		curr->change_parameters(0,0,0.5,270,0,180);		

		// shoulder
		make_pyramid(0, 0, v_positions, v_colors, glm::vec4(1,1,0.2,1));
		curr = humanoid->create_elem(v_positions, v_colors, 14);

		// neck
		make_pyramid(0, 0, v_positions, v_colors, glm::vec4(1,1,0.2,1));
		curr = humanoid->create_elem(v_positions, v_colors, 16);

		// head
		make_pyramid(1, 1, v_positions, v_colors, glm::vec4(0.7,0.2,0.4,1));
		curr = humanoid->create_elem(v_positions, v_colors, 17);
		curr->change_parameters(0,1,0,0,0,0);

		// left upper arm
		make_pyramid(1.8, 0.7, v_positions, v_colors, glm::vec4(1,0.2,0.4,1));
		curr = humanoid->create_elem(v_positions, v_colors, 2);
		curr->change_parameters(-0.5,0,0,0,0,-50);

		// left elbow
		make_pyramid(0, 0, v_positions, v_colors, glm::vec4(0,0,0,1));
		curr = humanoid->create_elem(v_positions, v_colors, ELBOW_LEFT);
		curr->change_parameters(0,-1.8,0,0,0,0);

		// left lower arm
		make_pyramid(1.8, 0.5, v_positions, v_colors, glm::vec4(0.3,0.8,0.7,1));
		curr = humanoid->create_elem(v_positions, v_colors, 4);
		curr->change_parameters(-1.55,-0.9,0,0,0,120);

		// left  wrist
		make_triangle(0.7, 0.5, 45,v_positions, v_colors, glm::vec4(0.5,0.3,0.2,1));
		curr = humanoid->create_elem(v_positions, v_colors, 6);
		curr->change_parameters(0,0,0,0,0,0);		

		// right upper arm
		make_pyramid(1.8, 0.7, v_positions, v_colors, glm::vec4(1,0.2,0.4,1));
		curr = humanoid->create_elem(v_positions, v_colors, 3);
		curr->change_parameters(0.5,0,0,0,0,50);

		// right elbow
		make_pyramid(0, 0, v_positions, v_colors, glm::vec4(0,0,0,1));
		curr = humanoid->create_elem(v_positions, v_colors, ELBOW_RIGHT);
		curr->change_parameters(0,-1.8,0,0,0,0);

		// right lower arm
		make_pyramid(1.8, 0.5, v_positions, v_colors, glm::vec4(0.3,0.8,0.7,1));
		curr = humanoid->create_elem(v_positions, v_colors, 5);
		curr->change_parameters(1.55,-0.9,0,0,0,-120);

		// right  wrist
		make_triangle(0.7, 0.5, 135,v_positions, v_colors, glm::vec4(0.5,0.3,0.2,1));
		curr = humanoid->create_elem(v_positions, v_colors, 7);
		curr->change_parameters(0,0,0,0,0,0);		

		//left lightsaber
		draw_cylinder(3.7,0.1,0.1,300,v_positions,v_colors,glm::vec4(0.7,0.3,0.2,1));
		curr = humanoid->create_elem(v_positions, v_colors, 18);
		curr->change_parameters(0,0.1,0,0,90,0);

		//RIGHT lightsaber
		draw_cylinder(3.7,0.1,0.1,300,v_positions,v_colors,glm::vec4(0.7,0.3,0.2,1));
		curr = humanoid->create_elem(v_positions, v_colors, 19);
		curr->change_parameters(0,0.1,0,0,-90,0);

		curr_node = humanoid->get_root();
	}

	void create_static_object(GLfloat *a_vertices){

		GLuint vao, vbo;
		glGenVertexArrays (1, &vao);
		glGenBuffers (1, &vbo);
		
		num_vertices.push_back(36);
		vao_array.push_back(vao);
		vbo_array.push_back(vbo);
		
		glBindVertexArray (vao);
		glBindBuffer (GL_ARRAY_BUFFER, vbo);

		glBufferData (GL_ARRAY_BUFFER, 36*4*sizeof(GLfloat), NULL, GL_STATIC_DRAW);
		glBufferSubData( GL_ARRAY_BUFFER, 0, 36*4*sizeof(GLfloat), a_vertices);

		//setup the vertex array as per the shader
		glEnableVertexAttribArray( vPosition1 );
		glVertexAttribPointer( vPosition1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
	}

	void initBuffersGL(void)
	{
		{
			std::string vertex_shader_file("vshader1.glsl");
			std::string fragment_shader_file("fshader1.glsl");

			std::vector<GLuint> shaderList;
			shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
			shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

			shaderProgram1 = csX75::CreateProgramGL(shaderList);
			glUseProgram( shaderProgram1 );

			// getting the attributes from the shader program
			vPosition1 = glGetAttribLocation( shaderProgram1, "vPosition" );
			uModelViewMatrix1 = glGetUniformLocation( shaderProgram1, "uModelViewMatrix");

			GLfloat skyboxVertices[] = {
			  -20.0f,  20.0f, -20.0f, 1.0f,
			  -20.0f, -20.0f, -20.0f, 1.0f,
			   20.0f, -20.0f, -20.0f, 1.0f,
			   20.0f, -20.0f, -20.0f, 1.0f,
			   20.0f,  20.0f, -20.0f, 1.0f,
			  -20.0f,  20.0f, -20.0f, 1.0f,
			  
			  -20.0f, -20.0f,  20.0f, 1.0f,
			  -20.0f, -20.0f, -20.0f, 1.0f,
			  -20.0f,  20.0f, -20.0f, 1.0f,
			  -20.0f,  20.0f, -20.0f, 1.0f,
			  -20.0f,  20.0f,  20.0f, 1.0f,
			  -20.0f, -20.0f,  20.0f, 1.0f,
			  
			   20.0f, -20.0f, -20.0f, 1.0f,
			   20.0f, -20.0f,  20.0f, 1.0f,
			   20.0f,  20.0f,  20.0f, 1.0f,
			   20.0f,  20.0f,  20.0f, 1.0f,
			   20.0f,  20.0f, -20.0f, 1.0f,
			   20.0f, -20.0f, -20.0f, 1.0f,
			   
			  -20.0f, -20.0f,  20.0f, 1.0f,
			  -20.0f,  20.0f,  20.0f, 1.0f,
			   20.0f,  20.0f,  20.0f, 1.0f,
			   20.0f,  20.0f,  20.0f, 1.0f,
			   20.0f, -20.0f,  20.0f, 1.0f,
			  -20.0f, -20.0f,  20.0f, 1.0f,
			  
			  -20.0f,  20.0f, -20.0f, 1.0f,
			   20.0f,  20.0f, -20.0f, 1.0f,
			   20.0f,  20.0f,  20.0f, 1.0f,
			   20.0f,  20.0f,  20.0f, 1.0f,
			  -20.0f,  20.0f,  20.0f, 1.0f,
			  -20.0f,  20.0f, -20.0f, 1.0f,
			  
			  -20.0f, -20.0f, -20.0f, 1.0f,
			  -20.0f, -20.0f,  20.0f, 1.0f,
			   20.0f, -20.0f, -20.0f, 1.0f,
			   20.0f, -20.0f, -20.0f, 1.0f,
			  -20.0f, -20.0f,  20.0f, 1.0f,
			   20.0f, -20.0f,  20.0f, 1.0f
			};			
			create_static_object(skyboxVertices);
			std::vector<const char*> faces;
			faces.push_back("images/right.bmp");
			faces.push_back("images/left.bmp");
			faces.push_back("images/bottom.bmp");
			faces.push_back("images/top.bmp");
			faces.push_back("images/back.bmp");
			faces.push_back("images/front.bmp");

			GLuint cubemapTexture = LoadTexture(faces, 2048, 2048);
	  		glDepthMask(GL_FALSE);

			glBindVertexArray(vao_array[0]);
			glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			glBindVertexArray(0);
			glDepthMask(GL_TRUE);
		}	

		{
			std::string vertex_shader_file("vshader2.glsl");
			std::string fragment_shader_file("fshader2.glsl");

			std::vector<GLuint> shaderList;
			shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
			shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

			shaderProgram2 = csX75::CreateProgramGL(shaderList);
			glUseProgram( shaderProgram2 );

			// getting the attributes from the shader program
			vPosition2 = glGetAttribLocation( shaderProgram2, "vPosition" );
			vColor2 = glGetAttribLocation( shaderProgram2, "vColor" );
			uModelViewMatrix2 = glGetUniformLocation( shaderProgram2, "uModelViewMatrix");

			create_humanoid();
		}
	}

	void draw_buffer(int i){
		glBindVertexArray(vao_array[i]);
		glDrawArrays(GL_TRIANGLES, 0, num_vertices[i]);
	}

	void renderGL(void)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		matrixStack.clear();

		lookat_matrix = camera->get_lookat_matrix();

		//creating the projection matrix
		if(enable_perspective){
			//projection_matrix = glm::frustum(-20.0, 20.0, -20.0, 20.0, 1.0, 5.0);
			projection_matrix = glm::infinitePerspective(360.0f, 1000.0f/750.0f, 3.0f);
		}
		else{
			projection_matrix = glm::ortho(-20.0, 20.0, -20.0, 20.0, -20.0, 20.0);
		}

		view_matrix = projection_matrix*lookat_matrix;

		glUniformMatrix4fv(uModelViewMatrix2, 1, GL_FALSE, glm::value_ptr(view_matrix));
		glUseProgram(shaderProgram2);
		matrixStack.push_back(view_matrix);
		matrixStack.push_back(glm::translate(glm::mat4(1.0f),glm::vec3(0.0f,0.0f,-depth)));
		humanoid->get_root()->render_tree(depth);

		glm::mat4 skybox_view_matrix = glm::mat4(glm::mat3(lookat_matrix));
		glUniformMatrix4fv(uModelViewMatrix1, 1, GL_FALSE, glm::value_ptr(projection_matrix*skybox_view_matrix));
		glUseProgram(shaderProgram1);
		for(int i=0;i<vao_array.size();++i){
			draw_buffer(i);
		}		
	}
};

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
	window = glfwCreateWindow(1000, 750, "Star Wars", NULL, NULL);
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
	Starwars *starwars = new Starwars();
	starwars->initBuffersGL();

	// Loop until the user closes the window
	while (glfwWindowShouldClose(window) == 0)
	{

		// Render here
		starwars->renderGL();

		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}