#ifndef GBUFFER_HPP
#define GBUFFER_HPP

#include "Camera.hpp"
#include <GL/glew.h>
#include <glm\glm.hpp>

class GBuffer
{

public:

	bool init(int width, int height);

	void bindDraw();
	void bindShadow();
	void bindRead();
	void bindLightRead();

	void update(int width, int height);
	void setProjectionAndView(void * proj, void * view);
	void setLightView(void* v);
	void draw();

	GLuint lightShader;
	GLuint combineShader;
	GLuint compShader;
	GLuint shadowShader;

	void streamLights(void*, int nrObj, int objSize);

private:

	GLuint lightVbo;
	GLuint lightVao;

	bool setTextures(int width, int height);
	void genQuad();

	GLuint fbo;
	GLuint diffuseTexture;
	GLuint normalTexture;
	GLuint worldPosTexture;
	GLuint depthTexture;

	GLuint shadowFbo;
	GLuint shadowTexture;

	void *lightVP;

	struct LightBuffer
	{
		GLuint fbo;
		GLuint lightTexture;
		int nrLights;
		//GLuint frustum;
		GLuint lightInfo;
		void *proj;
		void *view;
		//GLuint lightdetails;
		//GLuint atomicBuffer;

	}
	lightBuffer;


	int width;
	int height;
	int frame;

};

#endif