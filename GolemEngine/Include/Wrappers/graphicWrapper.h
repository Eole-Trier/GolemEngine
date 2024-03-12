#pragma once

#include <glad/glad.h>
#include <string>

#include "dll.h"

#define GRAPHIC_INTERFACE GraphicWrapper::GetInstance()

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
	// Static pointer which points to the only instance of this class
	static GraphicWrapper* m_instancePtr;

	unsigned int m_vao, m_vbo, m_rbo, m_fbo;
	unsigned int m_textureId;
	int m_width, m_height;

private:
	// Private constructor to stop intanciation
	GraphicWrapper() {}

public:
	// Returns instance of the class
	static GraphicWrapper* GetInstance();

	// Initialize library
	int Init();
	// Used to CREATE the scene in a framebuffer to be used as a texture. We do this in order to pass the texture to an ImGUI window so it can display it. 
	void CreateFramebuffer(int _width, int _height);
	// Used to clear a buffer for the next draw
	void ClearBuffer();
	// Used to BIND the scene in a framebuffer to be used as a texture. We do this in order to pass the texture to an ImGUI window so it can display it. 
	// The result is that we get a movable viewport in an ImGUI window.
	void BindFramebuffer();
	// Used to UNBIND the scene from a framebuffer to free the framebuffer. 
	void UnbindFramebuffer();
	// Enable a feature of OpenGl
	void EnableDepth();

	// This function is used to retrieve the texture of a framebuffer to use in the viewport to show the scene as a texture.
	unsigned int GetTextureId();

	// Used to set the background color of a buffer. Color is in the form of rgba vector. 
	void SetBackgroundColor(Vector4 _color);
	// Used to set the viewport that will be used
	void SetViewport(GLint _xMin, GLint _yMin, GLsizei _xMax, GLsizei _yMax);

#pragma region Shader functions
	// These functions should only be used through the Shader class and not through this GraphicWrapper class
	
	// Get parameters of the shader
	void GetShaderIv(GLuint _shader, GLenum _pName, GLint* _params);
	// Get info log of shader
	void GetShaderLog(GLuint _shader, GLsizei _bufSize, GLsizei* _length, GLchar* _infoLog);
	// Create shader
	GLuint CreateShader(GLenum _shaderType);
	// Set the source code of the shader
	void SetShaderSourceCode(GLuint _shader, GLsizei _count, const GLchar** _string, const GLint* _length);
	// Compile shader
	void CompileShader(GLuint _shader);
	// Create and return the program to set, use and manage shaders
	GLuint CreateShaderProgram();
	// Attach shader to the program
	void AttachShaderToProgram(GLuint _program, GLuint _shader);
	// Link the shader program
	void LinkProgram(GLuint _program);
	// Delete the shader object
	void DeleteShaderObject(GLuint _shader);
	// Use shader
	void UseShader(GLuint _program);

	void SetShaderBool(GLuint _program, const std::string& _name, bool _value) const;
	void SetShaderInt(GLuint _program, const std::string& _name, int _value) const;
	void SetShaderFloat(GLuint _program, const std::string& _name, float _value) const;
	void SetShaderVec2(GLuint _program, const std::string& _name, const Vector2& _value) const;
	void SetShaderVec2(GLuint _program, const std::string& _name, float _x, float _y) const;
	void SetShaderVec3(GLuint _program, const std::string& _name, const Vector3& _value) const;
	void SetShaderVec3(GLuint _program, const std::string& _name, float _x, float _y, float _z) const;
	void SetShaderVec4(GLuint _program, const std::string& _name, const Vector4& _value) const;
	void SetShaderVec4(GLuint _program, const std::string& _name, float _x, float _y, float _z, float _w) const;
	void SetShaderMat4(GLuint _program, const std::string& _name, const Matrix4& _mat) const;
	void SetShaderViewPos(GLuint _program, Vector3& _viewPos);

#pragma endregion Shader functions
};