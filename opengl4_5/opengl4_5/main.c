#include "Types.h"
#include "Shaders.h"
#include "Mesh.h"

#include <SDL/SDL.h>

#include <stdio.h>

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);

	SDL_Window *gl_window;
	SDL_GLContext gl_context;

	gl_window = SDL_CreateWindow("OpenGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_OPENGL);
	gl_context = SDL_GL_CreateContext(gl_window);

	glewExperimental = GL_TRUE;
	glewInit();

	printf("Using opengl version %s.\n", glGetString(GL_VERSION));
	printf("Using glsl version %s.\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	struct ShaderPair render_pair[2] = {
		[0].shader_source = "Shaders/vert.glsl", [0].shader_type = GL_VERTEX_SHADER,
		[1].shader_source = "Shaders/frag.glsl", [1].shader_type = GL_FRAGMENT_SHADER
	};

	GLuint render_prog = Shaders_CreateShaderProgram(render_pair, 2);

	struct Vertex tri_data[3] = {
		[0].pos = { -0.5f, -0.5f, 0.0f, 1.0f }, [0].col = { 1.0f, 0.0f, 0.0f, 1.0f },
		[1].pos = {  0.5f, -0.5f, 0.0f, 1.0f }, [1].col = { 0.0f, 1.0f, 0.0f, 1.0f },
		[2].pos = {  0.0f,  0.5f, 0.0f, 1.0f }, [2].col = { 0.0f, 0.0f, 1.0f, 1.0f }
	};

	struct Vertex sqr_data[6] = {
		[0].pos = { -0.5f, -0.5f, 0.0f, 1.0f }, [0].col = { 1.0f, 0.0f, 0.0f, 1.0f },
		[1].pos = {  0.5f, -0.5f, 0.0f, 1.0f }, [1].col = { 0.0f, 1.0f, 0.0f, 1.0f },
		[2].pos = {  0.5f,  0.5f, 0.0f, 1.0f }, [2].col = { 0.0f, 0.0f, 1.0f, 1.0f },
		[3].pos = {  0.5f,  0.5f, 0.0f, 1.0f }, [3].col = { 0.0f, 0.0f, 1.0f, 1.0f },
		[4].pos = { -0.5f,  0.5f, 0.0f, 1.0f }, [4].col = { 0.0f, 1.0f, 0.0f, 1.0f },
		[5].pos = { -0.5f, -0.5f, 0.0f, 1.0f }, [5].col = { 1.0f, 0.0f, 0.0f, 1.0f }
	};

	GLuint tri_vao = Mesh_Setup(render_prog, tri_data, 3);
	GLuint sqr_vao = Mesh_Setup(render_prog, sqr_data, 6);
	GLuint num_verts = 0;

	GLuint quit = 1;
	SDL_Event event;
	GLfloat scr_col[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	while (quit)
	{
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				quit = 0;

			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_z)
				{
					glBindVertexArray(tri_vao);
					num_verts = 3;
				}

				if (event.key.keysym.sym == SDLK_x)
				{
					glBindVertexArray(sqr_vao);
					num_verts = 6;
				}
			}
		}

		glUseProgram(render_prog);

		glClearBufferfv(GL_COLOR, 0, scr_col);

		glDrawArrays(GL_TRIANGLES, 0, num_verts);

		SDL_GL_SwapWindow(gl_window);
	}

	SDL_GL_DeleteContext(gl_context);
	SDL_DestroyWindow(gl_window);

	return 0;
}