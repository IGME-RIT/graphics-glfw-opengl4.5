#include "Mesh.h"

#include <stddef.h>

GLuint Mesh_Setup(GLuint shader_prog, struct Vertex *verts, GLuint num_verts)
{
	GLuint vao;
	glCreateVertexArrays(1, &vao);

	GLuint pos_attrib_loc = glGetAttribLocation(shader_prog, "pos");
	GLuint col_attrib_loc = glGetAttribLocation(shader_prog, "col");

	glVertexArrayAttribFormat(vao, pos_attrib_loc, 3, GL_FLOAT, GL_FALSE, (GLuint)offsetof(struct Vertex, pos));
	glVertexArrayAttribFormat(vao, col_attrib_loc, 4, GL_FLOAT, GL_FALSE, (GLuint)offsetof(struct Vertex, col));

	glVertexArrayAttribBinding(vao, pos_attrib_loc, 0);
	glVertexArrayAttribBinding(vao, col_attrib_loc, 0);

	glEnableVertexArrayAttrib(vao, pos_attrib_loc);
	glEnableVertexArrayAttrib(vao, col_attrib_loc);

	GLuint vbo;
	glCreateBuffers(1, &vbo);
	glNamedBufferStorage(vbo, sizeof(struct Vertex) * num_verts, verts, 0);

	glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(struct Vertex));
	return vao;
}