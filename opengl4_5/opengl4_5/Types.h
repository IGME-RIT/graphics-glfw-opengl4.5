#ifndef __Types__
#define __Types__

#include <GL/glew.h>

struct ShaderPair
{
	GLchar const *shader_source;
	GLenum shader_type;
};

struct Vertex
{
	GLfloat pos[4];
	GLfloat col[4];
};

#endif