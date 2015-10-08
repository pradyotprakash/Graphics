#include "starwars.hpp"

class Starwars{
public:
	GLuint shaderProgram;

	glm::mat4 rotation_matrix;
	glm::mat4 projection_matrix;
	glm::mat4 c_rotation_matrix;
	glm::mat4 lookat_matrix;

	glm::mat4 model_matrix;
	glm::mat4 view_matrix;


	glm::mat4 modelview_matrix;

	GLuint uModelViewMatrix;

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
			v_colors.push_back(glm::vec4(1.0,1.0,1.0,1.0));
			/* code */
		}

	}

	void create_humanoid(){
		
		std::vector<glm::vec4> v_positions, v_colors;
		
		// make_pyramid(height, width, v_positions, v_colors);
		csX75::HNode* curr;

		curr = humanoid->create_elem(v_positions, v_colors, 1);

		// curr->change_parameters(2.0,0.0,0.0,0.0,0.0,0.0);
		
		curr_node = humanoid->get_root();
	}

	void initBuffersGL(void)
	{

		// Load shaders and use the resulting shader program
		std::string vertex_shader_file("vshader.glsl");
		std::string fragment_shader_file("fshader.glsl");

		std::vector<GLuint> shaderList;
		shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
		shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

		shaderProgram = csX75::CreateProgramGL(shaderList);
		glUseProgram( shaderProgram );

		// getting the attributes from the shader program
		vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
		vColor = glGetAttribLocation( shaderProgram, "vColor" ); 
		uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");

		create_humanoid();

	}

	void renderGL(void)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		matrixStack.clear();

		lookat_matrix = camera->get_lookat_matrix();

		//creating the projection matrix
		if(enable_perspective)
			projection_matrix = glm::frustum(-7.0, 7.0, -7.0, 7.0, 1.0, 7.0);
		else
			projection_matrix = glm::ortho(-7.0, 7.0, -7.0, 7.0, -5.0, 5.0);

		view_matrix = projection_matrix*lookat_matrix;

		matrixStack.push_back(view_matrix);

		humanoid->get_root()->render_tree();

	}
};