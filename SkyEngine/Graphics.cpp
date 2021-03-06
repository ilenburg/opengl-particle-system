#include "Graphics.h"

using namespace std;

Graphics::Graphics()
{
	screen_width = 1024;
	screen_height = 768;
	window = SDL_CreateWindow("SkyEngine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	glContext = SDL_GL_CreateContext(window);
	init();
}

Graphics::~Graphics()
{
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
}

void Graphics::init()
{
	glewExperimental = GL_TRUE;
	glewInit();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	//glClearColor(0.5, 0.5, 0.5, 1);
	set_shaders();
}

string LoadText(const string &file_name)
{
	string line, r_string;
	ifstream file (file_name);
	if (file.is_open())
	{
		while (getline (file, line))
		{
			r_string.append(line);
			r_string.append("\n");
		}
		file.close();
	}

	return r_string;

}

void Graphics::set_shaders()
{
	GLuint program = glCreateProgram();

	string vertexString = LoadText("Data/Shaders/vert.glsl");
	string fragString = LoadText("Data/Shaders/frag.glsl");

	const char *vertexChars = vertexString.c_str();
	const char *fragChars = fragString.c_str();

	GLuint vertObject = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertObject, 1, &vertexChars, NULL);
	glCompileShader(vertObject);
	glAttachShader(program, vertObject);

	GLuint fragObject = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragObject, 1, &fragChars, NULL);
	glCompileShader(fragObject);
	glAttachShader(program, fragObject);

	GLuint VERTEX_BUFFER = 0;
	GLuint COLOUR_BUFFER = 1;
	GLuint TEXTURE_BUFFER = 2;

	glBindAttribLocation(program, VERTEX_BUFFER, "position");
	glBindAttribLocation(program, COLOUR_BUFFER, "colour");
	glBindAttribLocation(program, TEXTURE_BUFFER, "texCoord");

	glLinkProgram(program);
	glUseProgram(program);

	colourVar = glGetUniformLocation(program, "colourVar");
	pFixed = glGetUniformLocation(program, "pFixed");

	//glm::mat4 project = glm::ortho(0.0f,(float)screen_width,0.0f,(float)screen_height);
	//glm::mat4 project = glm::frustum(0.0f, (float)screen_width, 0.0f, (float)screen_height,0.0f,1.0f);
	perspect = glm::perspective(45.0f, 4.0f/3.0f, 1.0f, 5000.0f);
	ortho = glm::ortho(0.0f, (float)screen_width, 0.0f, (float)screen_height);
	glm::mat4 model = glm::mat4();
	glm::mat4 view = glm::mat4();
	//glm::mat4 view = glm::translate(glm::mat4(),glm::vec3(-100.0f, 0.0f,0.0f));

	shaderModelMat = glGetUniformLocation(program, "modelMatrix");
	glUniformMatrix4fv(shaderModelMat, 1, GL_FALSE,(float*)&model);

	shaderViewMat = glGetUniformLocation(program, "viewMatrix");
	glUniformMatrix4fv(shaderViewMat, 1, GL_FALSE,(float*)&view);

	shaderProjMat = glGetUniformLocation(program, "projMatrix");
	glUniformMatrix4fv(shaderProjMat, 1, GL_FALSE, (float*)&perspect);

	glUniformMatrix4fv(glGetUniformLocation(program, "projMatrix"), 1, GL_FALSE,(float*)&perspect);
	glUniformMatrix4fv(glGetUniformLocation(program, "viewMatrix"), 1, GL_FALSE,(float*)&view);
	glUniformMatrix4fv(glGetUniformLocation(program, "modelMatrix"), 1, GL_FALSE, (float*)&model);

	GLint sampler = glGetUniformLocation(program,"tex0");
	glUniform1i(sampler,0);

}