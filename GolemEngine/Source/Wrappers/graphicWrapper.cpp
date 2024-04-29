#include "Wrappers/graphicWrapper.h"
#include "Core/gameobject.h"

#include <iostream>
#include <GLFW/glfw3.h>
#include <Image/stb_image.h>

#include "Resource/tools.h"
#include "Debug/log.h"
#include "vector2.h"
#include "vector3.h"
#include "vector4.h"
#include "matrix4.h"

unsigned int GraphicWrapper::m_vao;
unsigned int GraphicWrapper::m_vbo;
unsigned int GraphicWrapper::m_rbo;
unsigned int GraphicWrapper::m_fbo;
unsigned int GraphicWrapper::m_textureId;

unsigned int GraphicWrapper::m_vaoPlayer;
unsigned int GraphicWrapper::m_vboPlayer;
unsigned int GraphicWrapper::m_rboPlayer;
unsigned int GraphicWrapper::m_fboPlayer;
unsigned int GraphicWrapper::m_playerSceneId;
unsigned int GraphicWrapper::m_cubemapId;
unsigned int GraphicWrapper::m_skyboxVAO;
unsigned int GraphicWrapper::m_skyboxVBO;

int GraphicWrapper::Init()
{
    return gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

void GraphicWrapper::CreateFramebuffer(unsigned int _format, int _width, int _height)
{
    #pragma region viewport textureid
    // Create framebuffer
    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

    // Create texturebuffer
    glGenTextures(1, &m_textureId);
    glBindTexture(GL_TEXTURE_2D, m_textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureId, 0);
    AttachTexture(_format, _width, _height, 0, m_textureId);

    CreateRenderBuffer(_width, _height);

    // Check framebuffer completeness
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "Framebuffer is not complete." << std::endl;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);   // Unbind framebuffer
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);   // Unbind framebuffer
    glBindTexture(GL_TEXTURE_2D, 0);    // Unbind texture
    glBindRenderbuffer(GL_RENDERBUFFER, 0); // Unbind renderbuffer
    #pragma endregion viewport textureid
    
    #pragma region playscene textureid
    // Create PlayScene framebuffer
    glGenFramebuffers(1, &m_fboPlayer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fboPlayer);

    // Create PlayScene texturebuffer
    glGenTextures(1, &m_playerSceneId);
    glBindTexture(GL_TEXTURE_2D, m_playerSceneId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_playerSceneId, 0);
    AttachTexture(_format, _width, _height, 0, m_playerSceneId);

    CreateRenderBuffer(_width, _height);

    // Check PlayScene framebuffer completeness
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "Framebuffer is not complete." << std::endl;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);   // Unbind framebuffer
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);   // Unbind framebuffer
    glBindTexture(GL_TEXTURE_2D, 0);    // Unbind texture
    glBindRenderbuffer(GL_RENDERBUFFER, 0); // Unbind renderbuffer
    #pragma endregion playscene textureid
}

void GraphicWrapper::AttachTexture(unsigned int _format, int _width, int _height, unsigned int _attachment, unsigned int _id)
{
    glBindTexture(GL_TEXTURE_2D, _id);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + _attachment, GL_TEXTURE_2D, _id, 0);
}

void GraphicWrapper::CreateRenderBuffer(int _width, int _height)
{
    // Create renderbuffer
    glGenRenderbuffers(1, &m_rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, _width, _height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);

    // Create renderbuffer
    glGenRenderbuffers(1, &m_rboPlayer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_rboPlayer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, _width, _height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rboPlayer);
}

int GraphicWrapper::ReadPixel(uint32_t _attachmentIndex, int _x, int _y)
{
    glReadBuffer(GL_COLOR_ATTACHMENT0 + _attachmentIndex);
    int pixelData;
    glReadPixels(_x, _y, 1, 1, GL_RED, GL_INT, &pixelData);
    return pixelData;
}

void GraphicWrapper::ClearBuffer()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GraphicWrapper::BindFramebuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
}

void GraphicWrapper::BindPlaySceneFrambuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_fboPlayer);
}

void GraphicWrapper::UnbindFramebuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GraphicWrapper::EnableDepth()
{
    glEnable(GL_DEPTH_TEST);
}

unsigned int GraphicWrapper::GetTextureId()
{
    return m_textureId;
}

unsigned int GraphicWrapper::GetPlayerSceneId()
{
    return m_playerSceneId;
}

unsigned int GraphicWrapper::GetSkyboxId()
{
    return m_cubemapId;
}

unsigned int GraphicWrapper::GetSkyboxVAO()
{
    return m_skyboxVAO;
}

void GraphicWrapper::SetBackgroundColor(Vector4 _color)
{
    glClearColor(_color.x, _color.y, _color.z, _color.w);
}

void GraphicWrapper::SetViewport(GLint _xMin, GLint _yMin, GLsizei _xMax, GLsizei _yMax)
{
    glViewport(_xMin, _yMin, _xMax, _yMax);
}


#pragma region Shader functions

void GraphicWrapper::GetShaderIv(GLuint _shader, GLenum _pName, GLint* _params)
{
    glGetShaderiv(_shader, _pName, _params);
}

void GraphicWrapper::GetShaderLog(GLuint _shader, GLsizei _bufSize, GLsizei* _length, GLchar* _infoLog)
{
    glGetShaderInfoLog(_shader, _bufSize, _length, _infoLog);
}

GLuint GraphicWrapper::CreateShader(GLenum _shaderType)
{
    return glCreateShader(_shaderType);
}

void GraphicWrapper::SetShaderSourceCode(GLuint _shader, GLsizei _count, const GLchar** _string, const GLint* _length)
{
    glShaderSource(_shader, _count, _string, _length);
}

void GraphicWrapper::CompileShader(GLuint _shader)
{
    glCompileShader(_shader);
}

GLuint GraphicWrapper::CreateShaderProgram()
{
    return glCreateProgram();
}

void GraphicWrapper::AttachShaderToProgram(GLuint _program, GLuint _shader)
{
    glAttachShader(_program, _shader);
}

void GraphicWrapper::LinkProgram(GLuint _program)
{
    glLinkProgram(_program);
}

void GraphicWrapper::DeleteShaderObject(GLuint _shader)
{
    glDeleteShader(_shader);
}

void GraphicWrapper::UseShader(GLuint _program)
{
    glUseProgram(_program);
}

unsigned int GraphicWrapper::GetFbo()
{
    return m_fbo;
}

unsigned int GraphicWrapper::LoadCubemap(std::vector<std::string> faces)
{
    float skyboxVertices[] = {
        // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

    // skybox VAO
    
    glGenVertexArrays(1, &m_skyboxVAO);
    glGenBuffers(1, &m_skyboxVBO);
    glBindVertexArray(m_skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}

void GraphicWrapper::SetSkybox()
{
    std::vector<std::string> faces
    {
        Tools::FindFile("skybox_right.jpg"),
        Tools::FindFile("skybox_left.jpg"),
        Tools::FindFile("skybox_top.jpg"),
        Tools::FindFile("skybox_bottom.jpg"),
        Tools::FindFile("skybox_front.jpg"),
        Tools::FindFile("skybox_back.jpg"),
    };

    m_cubemapId = LoadCubemap(faces);
}

void GraphicWrapper::SetShaderBool(GLuint _program, const std::string& _name, bool _value)
{
    glUniform1i(glGetUniformLocation(_program, _name.c_str()), (int)_value);
}

void GraphicWrapper::SetShaderInt(GLuint _program, const std::string& _name, int _value)
{
    glUniform1i(glGetUniformLocation(_program, _name.c_str()), _value);
}

void GraphicWrapper::SetShaderFloat(GLuint _program, const std::string& _name, float _value)
{
    glUniform1f(glGetUniformLocation(_program, _name.c_str()), _value);
}

void GraphicWrapper::SetShaderVec2(GLuint _program, const std::string& _name, const Vector2& _value)
{
    glUniform2fv(glGetUniformLocation(_program, _name.c_str()), 1, &_value.x);
}

void GraphicWrapper::SetShaderVec2(GLuint _program, const std::string& _name, float _x, float _y)
{
    glUniform2f(glGetUniformLocation(_program, _name.c_str()), _x, _y);
}

void GraphicWrapper::SetShaderVec3(GLuint _program, const std::string& _name, const Vector3& _value)
{
    glUniform3fv(glGetUniformLocation(_program, _name.c_str()), 1, &_value.x);
}

void GraphicWrapper::SetShaderVec3(GLuint _program, const std::string& _name, float _x, float _y, float _z)
{
    glUniform3f(glGetUniformLocation(_program, _name.c_str()), _x, _y, _z);
}

void GraphicWrapper::SetShaderVec4(GLuint _program, const std::string& _name, const Vector4& _value)
{
    glUniform4fv(glGetUniformLocation(_program, _name.c_str()), 1, &_value.x);
}

void GraphicWrapper::SetShaderVec4(GLuint _program, const std::string& _name, float _x, float _y, float _z, float _w)
{
    glUniform4f(glGetUniformLocation(_program, _name.c_str()), _x, _y, _z, _w);
}

void GraphicWrapper::SetShaderMat4(GLuint _program, const std::string& _name, const Matrix4& _mat)
{
    glUniformMatrix4fv(glGetUniformLocation(_program, _name.c_str()), 1, GL_TRUE, &_mat.data[0][0]);
}

void GraphicWrapper::SetShaderViewPos(GLuint _program, Vector3& _viewPos)
{
    SetShaderVec3(_program, "viewPos", _viewPos);
}
#pragma endregion Shader functions