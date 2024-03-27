#pragma once

#include "Wrappers/graphicWrapper.h"

class PickingTexture
{
private:
    GLuint m_fbo = 0;
    GLuint m_pickingTexture = 0;
    GLuint m_depthTexture = 0;

public:
    PickingTexture();

    ~PickingTexture();

    void Init(unsigned int WindowWidth, unsigned int WindowHeight);

    void EnableWriting();

    void DisableWriting();

    struct PixelInfo 
    {
        int ObjectID = 0;
        int DrawID = 0;
        int PrimID = 0;

        void Print()
        {
            printf("Object %d draw %d prim %d\n", ObjectID, DrawID, PrimID);
        }
    };

    PixelInfo ReadPixel(unsigned int x, unsigned int y);
};