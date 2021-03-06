#include "modeller.hpp"
#include <utility>
#include <fstream>
#include <map>

#define pvec4 std::pair<glm::vec4, glm::vec4>
#define pvec4i std::pair<glm::vec4, int>

struct vec4less{
	bool operator()(const glm::vec4 &vecA, const glm::vec4 &vecB){ 
		const double epsilion = 0.00001;  // choose something apprpriate.

		if(vecA.x < vecB.x)
			return true;
		else if(vecA.x == vecB.x){
			if(vecA.y < vecB.y)
				return true;
			else if(vecA.y == vecB.y){
				if(vecA.z < vecB.z)
				return true;
			}
		}
		return false;
	}
};

const int glmVec4Size = sizeof(glm::vec4);
const int window_x = 512;
const int window_y = 512;

const std::string vs_file = "vs.glsl";
const std::string fs_file = "fs.glsl";

unsigned int numOfPoints, newPointsAdded;
bool del = false;

glm::mat4 transformation_matrix;
glm::mat4 ortho_matrix;
glm::mat4 modelview_matrix;
GLuint uModelViewMatrix;

GLuint shaderProgram;
GLuint vao, vbo;

std::vector<glm::vec4> v_positions_original;
std::vector<glm::vec4> v_colors_original;
std::vector<glm::vec4> v_positions_temp;
std::vector<glm::vec4> v_colors_temp;

std::map<glm::vec4, int, vec4less> distinct_vertices;

glm::vec3 vertex_sum;
glm::vec3 centroid;
pvec4 first_inserted, last_inserted;

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
		distinct_vertices.insert(pvec4i(vertices[i].first, 1));

		vertex_sum.x += vertices[i].first.x;
		vertex_sum.y += vertices[i].first.y;
		vertex_sum.z += vertices[i].first.z;
	}

	centroid = glm::vec3(vertex_sum.x/numOfPoints, vertex_sum.y/numOfPoints, vertex_sum.z/numOfPoints);
}


void quad(int a, int b, int c, int d){
	v_colors_original.push_back(vertices[a].second); v_positions_original.push_back(vertices[a].first);
	v_colors_original.push_back(vertices[b].second); v_positions_original.push_back(vertices[b].first);
	v_colors_original.push_back(vertices[c].second); v_positions_original.push_back(vertices[c].first);
	v_colors_original.push_back(vertices[a].second); v_positions_original.push_back(vertices[a].first);
	v_colors_original.push_back(vertices[c].second); v_positions_original.push_back(vertices[c].first);
	v_colors_original.push_back(vertices[d].second); v_positions_original.push_back(vertices[d].first);
}

void laptop(void){

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

void createShader(){
	std::string vertex_shader_file(vs_file);
	std::string fragment_shader_file(fs_file);

	std::vector<GLuint> shaderList;
	shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
	shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

	shaderProgram = csX75::CreateProgramGL(shaderList);

	// Load shaders and use the resulting shader program
	glUseProgram( shaderProgram );
}

void load_onto_buffer(std::vector<glm::vec4> &v_position_data, std::vector<glm::vec4> &v_color_data){
	
	glBindBuffer (GL_ARRAY_BUFFER, vbo);

	int vertex_array_size = v_position_data.size()*glmVec4Size;
	int color_array_size = v_color_data.size()*glmVec4Size;

	int totalSpace = vertex_array_size + color_array_size;

	glBufferData (GL_ARRAY_BUFFER, totalSpace, NULL, GL_STATIC_DRAW);
	glBufferSubData( GL_ARRAY_BUFFER, 0, vertex_array_size, &v_position_data[0] );
	glBufferSubData( GL_ARRAY_BUFFER, vertex_array_size, color_array_size, &v_color_data[0] );

	// set up vertex arrays
	GLuint vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
	glEnableVertexAttribArray( vPosition );
	glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

	GLuint vColor = glGetAttribLocation( shaderProgram, "vColor" ); 
	glEnableVertexAttribArray( vColor );
	glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(v_position_data.size()*glmVec4Size) );
}

void setup_buffer(){
	std::vector<glm::vec4> positions_added;
	positions_added.reserve(v_positions_original.size() + v_positions_temp.size());
	positions_added.insert(positions_added.end(), v_positions_original.begin(), v_positions_original.end());
	positions_added.insert(positions_added.end(), v_positions_temp.begin(), v_positions_temp.end());

	std::vector<glm::vec4> colors_added;
	colors_added.reserve(v_colors_original.size() + v_colors_temp.size());
	colors_added.insert(colors_added.end(), v_colors_original.begin(), v_colors_original.end());
	colors_added.insert(colors_added.end(), v_colors_temp.begin(), v_colors_temp.end());

	load_onto_buffer(positions_added, colors_added);
}

void initBuffersGL(){

	if(!file_load && !centroid_translate){
		laptop();
	}

	glGenVertexArrays (1, &vao);
	glBindVertexArray (vao);
	
	glGenBuffers (1, &vbo);

	setup_buffer();
	
	uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");
}

void load_from_file(){
	std::string file_name;
	std::string s;

	modelling_enabled = 0;

	xpos = 0, ypos = 0, zpos = 0, xrot = 0, yrot = 0, zrot = 0;

	std::cout<<"Enter file name: ";
	getline(std::cin, file_name);

	std::ifstream inp(file_name.c_str());

	GLfloat a, b, c, d, e, f;

	distinct_vertices.clear();
	vertex_sum = glm::vec3(0,0,0);
	centroid = glm::vec3(0,0,0);
	numOfPoints = 0;
	newPointsAdded = 0;	


	v_positions_original.clear();
	v_positions_temp.clear();
	v_colors_original.clear();
	v_colors_temp.clear();

	while(inp>>a>>b>>c>>d>>e>>f){
		glm::vec4 point = glm::vec4(a,b,c,1.0);
		v_positions_original.push_back(point);
		v_colors_original.push_back(glm::vec4(d,e,f,0.0));
		
		std::map<glm::vec4, int>::iterator it = distinct_vertices.find(point);
		if(it == distinct_vertices.end()){

			// not found
			distinct_vertices.insert(pvec4i(point,1));
			vertex_sum.x += point.x;
			vertex_sum.y += point.y;
			vertex_sum.z += point.z;
			numOfPoints++;
		}
		else{
			it->second = it->second + 1;
		}
	}

	if(numOfPoints)
		centroid = glm::vec3(vertex_sum.x/numOfPoints, vertex_sum.y/numOfPoints, vertex_sum.z/numOfPoints);

	inp.close();

	file_load = 0;
	setup_buffer();

	std::cout<<"File loaded successfully\n";
	
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
	//file_name = ".models/" + file_name;
	std::ofstream out(file_name.c_str());

	for(int i=0;i<v_positions_original.size();++i){
		glm::vec4 point = transformation_matrix*v_positions_original[i];
		out<<point.x<<" "<<point.y<<" "<<point.z<<" ";
		out<<v_colors_original[i].x<<" "<<v_colors_original[i].y<<" "<<v_colors_original[i].z<<"\n";
	}

	for(int i=0;i<v_positions_temp.size();++i){
		glm::vec4 point = transformation_matrix*v_positions_temp[i];
		out<<point.x<<" "<<point.y<<" "<<point.z<<" ";
		out<<v_colors_temp[i].x<<" "<<v_colors_temp[i].y<<" "<<v_colors_temp[i].z<<"\n";
	}

	out.close();
	file_write = 0;
	std::cout<<"File written successfully\n";
}

void inverse_transform(glm::mat4 &inv){
	glm::mat4 tr2 = glm::translate(glm::mat4(1.0f), glm::vec3(-1*(centroid.x + xpos), -1*(centroid.y + ypos), -1*(centroid.z + zpos)));
	glm::mat4 rot3 = glm::rotate(glm::mat4(1.0f), -1*zrot, glm::vec3(0.0f,0.0f,1.0f));
	glm::mat4 rot2 = glm::rotate(glm::mat4(1.0f), -1*yrot, glm::vec3(0.0f,1.0f,0.0f));
	glm::mat4 rot1 = glm::rotate(glm::mat4(1.0f), -1*xrot, glm::vec3(1.0f,0.0f,0.0f));

	glm::mat4 tr1 = glm::translate(glm::mat4(1.0f), glm::vec3(centroid.x, centroid.y, centroid.z));

	inv = tr1*rot1*rot2*rot3*tr2;

}

void set_centroid_as_origin(){
	std::vector<glm::vec4> coor;

	centroid = glm::vec3(0, 0, 0);
	centroid_translate = 0; xpos = 0; ypos = 0; zpos = 0;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){

	if(modelling_enabled){
		if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos); 
			
			
			float normalized_x, normalized_y;
			normalized_x = 2*( xpos - window_x/2)/(window_x/2);
			normalized_y = -2*(ypos - window_y/2)/(window_y/2);
			
			int state = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT);
			
			if( state == GLFW_PRESS){
				del = !del;
				if(del)
					std::cout<<"Deletion mode activated\n";
				else std::cout<<"Insertion mode activated\n";
			}

			if(del){
				
				if(numOfPoints){
					glm::vec4 popped_point = v_positions_temp[v_positions_temp.size()-1];

					if(newPointsAdded == 3){
						last_inserted.first = v_positions_temp[v_positions_temp.size()-2];
						last_inserted.second = v_colors_temp[v_colors_temp.size()-2];
					}
					else if(newPointsAdded > 3){
						last_inserted.first = v_positions_temp[v_positions_temp.size()-4];
						last_inserted.second = v_colors_temp[v_colors_temp.size()-4];
					}

					if(newPointsAdded >= 3){
						for(int i=0;i<3;++i){
							v_positions_temp.pop_back();
							v_colors_temp.pop_back();
						}
					}

					--newPointsAdded;

					std::map<glm::vec4, int>::iterator it = distinct_vertices.find(popped_point);
					
					if(it->second >= 2){
						it->second = it->second - 1;
					}
					else{
						distinct_vertices.erase(it);
						--numOfPoints;

						// recalculate centroid
						vertex_sum.x -= popped_point.x;
						vertex_sum.y -= popped_point.y;
						vertex_sum.z -= popped_point.z;
						
						centroid = glm::vec3(vertex_sum.x/numOfPoints, vertex_sum.y/numOfPoints, vertex_sum.z/numOfPoints);

					}

					std::cout<<"Last point deleted is ("<<popped_point.x<<","<<popped_point.y<<","<<popped_point.z<<")\n";
				}
			}
			else{
				glm::vec4 newPoint = glm::vec4(normalized_x, normalized_y, zpos, 1);
				glm::mat4 inv;
				inverse_transform(inv);
				
				newPoint = inv*newPoint;
				// add color of point
				std::cout<<"Enter color in R G B A format: ";
				GLfloat r, g, b, a;
				std::cin>>r>>g>>b>>a;
				glm::vec4 newPointColor = glm::vec4(r,g,b,a);
				newPointsAdded++;

				if(newPointsAdded == 1)
					first_inserted = pvec4(newPoint, newPointColor);
				
				if(newPointsAdded >= 3){
					v_positions_temp.push_back(first_inserted.first);
					v_positions_temp.push_back(last_inserted.first);
					v_positions_temp.push_back(newPoint);

					v_colors_temp.push_back(first_inserted.second);
					v_colors_temp.push_back(last_inserted.second);
					v_colors_temp.push_back(newPointColor);
				}

				if(newPointsAdded >= 2)
					last_inserted = pvec4(newPoint, newPointColor);

				std::map<glm::vec4, int>::iterator it = distinct_vertices.find(newPoint);
				if(it == distinct_vertices.end()){
					// not found
					
					vertex_sum.x += newPoint.x;
					vertex_sum.y += newPoint.y;
					vertex_sum.z += newPoint.z;
					numOfPoints++;
					distinct_vertices.insert(pvec4i(newPoint,1));

					centroid = glm::vec3(vertex_sum.x/numOfPoints, vertex_sum.y/numOfPoints, vertex_sum.z/numOfPoints);

					std::cout<<"Last point added at ("<<newPoint.x<<","<<newPoint.y<<","<<newPoint.z<<")\n";
				}
				else{
					// found
					it->second = it->second + 1;
				}				   	
			}

			setup_buffer();
		}
	}
}

void model(GLFWwindow* window){	
	glfwSetMouseButtonCallback(window, mouse_button_callback);
}

void renderGL(void){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	transform();

	ortho_matrix = glm::ortho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);

	modelview_matrix = ortho_matrix * transformation_matrix;

	glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));

	// Draw 
	glDrawArrays(GL_TRIANGLES, 0, v_positions_original.size() + v_positions_temp.size());

}

int main(int argc, char** argv){

	newPointsAdded = 0;
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
	initBuffersGL();

	// Loop until the user closes the window
	while (glfwWindowShouldClose(window) == 0){
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
		else{
			newPointsAdded = 0;
		}

		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}