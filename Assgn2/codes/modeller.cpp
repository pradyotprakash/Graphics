#include "modeller.hpp"
#include <utility>
#include <fstream>
#include <map>
#include <sstream>

void drawBuffer(int);

const int glmVec4Size = sizeof(glm::vec4);
const int window_x = 512;
const int window_y = 512;

const std::string vs_file = "vs.glsl";
const std::string fs_file = "fs.glsl";

glm::mat4 transformation_matrix;
glm::mat4 ortho_matrix;
glm::mat4 modelview_matrix;

glm::vec3 eye, lookat, up, u, v, n;
glm::mat4 Awv, Avc, Acn, And;

GLfloat L, R, T, B, N, F;
GLuint shaderProgram;
GLuint uModelViewMatrix;

std::vector<GLuint> vao;
std::vector<std::vector<GLuint> > vbo;
std::vector<int> sizeOfModels;

void getnVaos(int n){
	glGenVertexArrays(n, &vao[0]);
}

void get2Vbos(int i){
	glGenBuffers(2, &vbo[i][0]);
}

void createShader(){
	std::string vertex_shader_file(vs_file);
	std::string fragment_shader_file(fs_file);

	std::vector<GLuint> shaderList;
	shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
	shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

	shaderProgram = csX75::CreateProgramGL(shaderList);

	// Load shaders and use the resulting shader program
	glUseProgram( shaderProgram );

	uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");
}

void load_onto_buffer(std::vector<glm::vec4> &vertex_data, std::vector<glm::vec4> &color_data, int i){
	
	glBindVertexArray(vao[i]);
	get2Vbos(i);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[i][0]);
	glBufferData(GL_ARRAY_BUFFER, vertex_data.size()*glmVec4Size, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertex_data.size()*glmVec4Size, &vertex_data[0]);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[i][1]);
	glBufferData(GL_ARRAY_BUFFER, color_data.size()*glmVec4Size, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, color_data.size()*glmVec4Size, &color_data[0]);
}

void findScalingMatrix(std::string s, glm::mat4 &scale){
	std::stringstream ss;
	ss<<s;
	GLfloat a, b, c;
	ss>>a>>b>>c;

	GLfloat temp[16] = {a, 0, 0, 0,
						0, b, 0, 0,
						0, 0, c, 0,
						0, 0, 0, 1.0};
	
	scale = glm::make_mat4(temp);
}

void findRotationMatrix(std::string s, glm::mat4 &rotate){
	std::stringstream ss;
	ss<<s;
	GLfloat a, b, c;
	ss>>a>>b>>c;

	a *= 3.1415/180;
	b *= 3.1415/180;
	c *= 3.1415/180;

	glm::mat4 rot1 = glm::rotate(glm::mat4(1.0f), a, glm::vec3(1.0f,0.0f,0.0f));
	glm::mat4 rot2 = glm::rotate(glm::mat4(1.0f), b, glm::vec3(0.0f,1.0f,0.0f));
	glm::mat4 rot3 = glm::rotate(glm::mat4(1.0f), c, glm::vec3(0.0f,0.0f,1.0f));
	
	rotate = rot1*rot2*rot3;
}

void findTranslationMatrix(std::string s, glm::mat4 &translate){
	std::stringstream ss;
	ss<<s;
	GLfloat a, b, c;
	ss>>a>>b>>c;

	GLfloat temp[16] = {1, 0, 0, 0,
						0, 1, 0, 0,
						0, 0, 1, 0,
						a, b, c, 1};
	
	translate = glm::make_mat4(temp);
}

void load_data_from_file(std::string file_name){
	std::string s;

	std::ifstream inp(file_name.c_str());
	int models_loaded = 0;

	while(getline(inp, s)){
		if(s[0] == '#' || s[0] == ' ' || s.length() == 0)
			continue;

		if(models_loaded < 3){
			std::ifstream model_file(s.c_str());

			std::vector<glm::vec4> vertex_data;
			std::vector<glm::vec4> color_data;

			glm::mat4 scale, rotate, translate;
			
			getline(inp, s);
			findScalingMatrix(s, scale);

			getline(inp, s);
			findRotationMatrix(s, rotate);

			getline(inp, s);
			findTranslationMatrix(s, translate);

			glm::mat4 model_transform_matrix = translate*rotate*scale;

			GLfloat a, b, c, d, e, f;
			glm::vec4 vertex, color;
			
			while(model_file>>a>>b>>c>>d>>e>>f){
				vertex = glm::vec4(a,b,c,1.0);
				vertex = model_transform_matrix * vertex;
				color = glm::vec4(d,e,f,0.0);

				vertex_data.push_back(vertex);
				color_data.push_back(color);
			}

			load_onto_buffer(vertex_data, color_data, models_loaded);
			sizeOfModels.push_back(vertex_data.size());

			++models_loaded;
		}
		else if(models_loaded == 3){
			std::stringstream ss;
			
			ss<<s;
			GLfloat a, b, c;
			ss>>a>>b>>c;
			eye = glm::vec3(a, b, c);

			getline(inp, s);
			ss<<s;
			ss>>a>>b>>c;
			lookat = glm::vec3(a, b, c);

			getline(inp, s);
			ss<<s;
			ss>>a>>b>>c;
			up = glm::vec3(a, b, c);
			models_loaded++;
		}
		else if(models_loaded == 4){
			std::stringstream ss;
			getline(inp, s);
			ss<<s;
			ss>>L>>R>>T>>B;
			L = -L; B = -B;

			getline(inp, s);
			ss<<s;
			ss>>N>>F;
		}
	}
}

void findAwv(){
	
	n = glm::normalize(eye - lookat);
	u = glm::normalize(glm::cross(up, n));
	v = glm::cross(n, u);

	GLfloat temp[16] = {u.x, v.x, n.x, 0.0,
						u.y, v.y, n.y, 0.0,
						u.z, v.z, n.z, 0.0,
						-glm::dot(u, eye), -glm::dot(v, eye), -glm::dot(n, eye), 1};

	Awv = glm::make_mat4(temp);
}

void findAvc(){
	
	GLfloat temp[16] = {2*N/(R-L), 0, 0, 0,
						0, 2*N/(T-B), 0, 0,
						(R+L)/(R-L), (T+B)/(T-B), (F+N)/(N-F), -1.0,
						0, 0, 2*F*N/(N-F), 0};

	Avc = glm::make_mat4(temp);
}

void create_fustum(){

}

void initialize(){
	vao.resize(4);
	getnVaos(4);

	vbo.resize(4);
	for(int i=0;i<4;++i){
		vbo[i].resize(2);
	}

	load_data_from_file("random");
	create_fustum();
}

void transform(){

	// change transformation matrix here
	if(pressed1){
		transformation_matrix = Awv;
	}
	else if(pressed2){
		transformation_matrix = Avc * Awv;
	}
	else if(pressed3){

	}
	else if(pressed4){

	}
	else{
		transformation_matrix = glm::mat4();
	}
}

void drawBuffer(int i){
	
	glBindVertexArray(vao[i]);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo[i][0]);
	GLuint vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
	glEnableVertexAttribArray( vPosition );
	glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

	glBindBuffer(GL_ARRAY_BUFFER, vbo[i][1]);
	GLuint vColor = glGetAttribLocation( shaderProgram, "vColor" ); 
	glEnableVertexAttribArray( vColor );
	glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

	glDrawArrays(GL_TRIANGLES, 0, sizeOfModels[i]);
}

void renderGL(void){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	transform();

	ortho_matrix = glm::ortho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);

	modelview_matrix = ortho_matrix * transformation_matrix;

	glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));

	for(int i=0;i<sizeOfModels.size();++i){
		drawBuffer(i);
	}
}

int main(int argc, char** argv){

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
	if (!window){
		glfwTerminate();
		return -1;
	}

	//! Make the window's context current 
	glfwMakeContextCurrent(window);

	//Initialize GLEW
	//Turn this on to get Shader based OpenGL
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err){
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

	createShader();
	initialize();

	// Loop until the user closes the window
	while (glfwWindowShouldClose(window) == 0){
		
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