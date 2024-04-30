#pragma once

#include <glad/glad.h>
#include <string>

#include "dll.h"

#define OPENGL_MAJOR_VERSION GLFW_CONTEXT_VERSION_MAJOR
#define OPENGL_MINOR_VERSION GLFW_CONTEXT_VERSION_MINOR

#pragma region Shader macros
#define SHADER_COMPILE_STATUS GL_COMPILE_STATUS
#define SHADER_LINK_STATUS GL_LINK_STATUS
#define SHADER_TYPE GL_VERTEX_SHADER
#define FRAGMENT_SHADER_TYPE GL_FRAGMENT_SHADER
#pragma endregion Shader macros

class Vector2;
class Vector3;
class Vector4;
class Matrix4;

class GOLEM_ENGINE_API GraphicWrapper
{
private:
	static unsigned int m_vao;
	static unsigned int m_vbo;
	static unsigned int m_rbo;
	static unsigned int m_fbo;
	static unsigned int m_textureId;
	static int m_width;
	static int m_height;

private:
	// Private constructors and destructor to make static class
	GraphicWrapper() = delete;
	GraphicWrapper(GraphicWrapper& _other) = delete;
	GraphicWrapper(GraphicWrapper&& _other) = delete;
	GraphicWrapper& operator=(GraphicWrapper& _other) = delete;
	GraphicWrapper& operator=(GraphicWrapper&& _other) = delete;
	void operator=(const GraphicWrapper&) = delete;
	~GraphicWrapper() = delete;

public:
	// Initialize library
	static int Init();
	// Used to CREATE the scene in a framebuffer to be used as a texture. We do this in order to pass the texture to an ImGUI window so it can display it. 
	static void CreateFramebuffer(unsigned int _format, int _width, int _height);

	static void AttachTexture(unsigned int _format, int _width, int _heigh, unsigned int _attachment, unsigned int _id);

	static void CreateRenderBuffer(int _width, int _height);
	// Used to clear a buffer for the next draw
	static void ClearBuffer();
	// Used to BIND the scene in a framebuffer to be used as a texture. We do this in order to pass the texture to an ImGUI window so it can display it. 
	// The result is that we get a movable viewport in an ImGUI window.
	static void BindFramebuffer();
	// Used to UNBIND the scene from a framebuffer to free the framebuffer. 
	static void UnbindFramebuffer();
	// Enable a feature of OpenGl
	static void EnableDepth();

	static int ReadPixel(uint32_t _attachmentIndex, int _x, int _y);

	// This function is used to retrieve the texture of a framebuffer to use in the viewport to show the scene as a texture.
	static unsigned int GetTextureId();

	// Used to set the background color of a buffer. Color is in the form of rgba vector. 
	static void SetBackgroundColor(Vector4 _color);
	// Used to set the viewport that will be used
	static void SetViewport(GLint _xMin, GLint _yMin, GLsizei _xMax, GLsizei _yMax);

	static unsigned int GetFbo();

#pragma region Shader functions
	// These functions should only be used through the Shader class and not through this GraphicWrapper class

	// Get parameters of the shader
	static void GetShaderIv(GLuint _shader, GLenum _pName, GLint* _params);
	// Get info log of shader
	static void GetShaderLog(GLuint _shader, GLsizei _bufSize, GLsizei* _length, GLchar* _infoLog);
	// Create shader
	static GLuint CreateShader(GLenum _shaderType);
	// Set the source code of the shader
	static void SetShaderSourceCode(GLuint _shader, GLsizei _count, const GLchar** _string, const GLint* _length);
	// Compile shader
	static void CompileShader(GLuint _shader);
	// Create and return the program to set, use and manage shaders
	static GLuint CreateShaderProgram();
	// Attach shader to the program
	static void AttachShaderToProgram(GLuint _program, GLuint _shader);
	// Link the shader program
	static void LinkProgram(GLuint _program);
	// Delete the shader object
	static void DeleteShaderObject(GLuint _shader);
	// Use shader
	static void UseShader(GLuint _program);

	static void SetShaderBool(GLuint _program, const std::string& _name, bool _value);
	static void SetShaderInt(GLuint _program, const std::string& _name, int _value);
	static void SetShaderFloat(GLuint _program, const std::string& _name, float _value);
	static void SetShaderVec2(GLuint _program, const std::string& _name, const Vector2& _value);
	static void SetShaderVec2(GLuint _program, const std::string& _name, float _x, float _y);
	static void SetShaderVec3(GLuint _program, const std::string& _name, const Vector3& _value);
	static void SetShaderVec3(GLuint _program, const std::string& _name, float _x, float _y, float _z);
	static void SetShaderVec4(GLuint _program, const std::string& _name, const Vector4& _value);
	static void SetShaderVec4(GLuint _program, const std::string& _name, float _x, float _y, float _z, float _w);
	static void SetShaderMat4(GLuint _program, const std::string& _name, const Matrix4& _mat);
	static void SetShaderViewPos(GLuint _program, Vector3& _viewPos);

#pragma endregion Shader functions
};