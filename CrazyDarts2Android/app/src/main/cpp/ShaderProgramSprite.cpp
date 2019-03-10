//
//  ShaderProgramSprite.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 3/8/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "core_includes.h"
#include "ShaderProgramSprite.hpp"

ShaderProgramSprite::ShaderProgramSprite(const char *pVertexPath, const char *pFragmentPath) : ShaderProgram(pVertexPath, pFragmentPath) {
    
    mSlotTextureCoords = -1;
    mSlotTexture = -1;
    
}

void ShaderProgramSprite::Compile() {
    
    ShaderProgram::Compile();
    
    if (IsValid() == false) return;
    
    mSlotTexture = glGetUniformLocation(mProgram, "Texture");
    mSlotTextureCoords = glGetAttribLocation(mProgram, "TextureCoords");
    
    Log("*******\n");
    Log("Shader[%s] mSlotProjectionUniform = %d\n", mName.c(), mSlotProjectionUniform);
    Log("Shader[%s] mSlotModelViewUniform = %d\n", mName.c(), mSlotModelViewUniform);
    Log("Shader[%s] mSlotModulateUniform = %d\n", mName.c(), mSlotModulateUniform);
    
    Log("Shader[%s] mSlotTexture = %d\n", mName.c(), mSlotTexture);
    Log("Shader[%s] mSlotPositions = %d\n", mName.c(), mSlotPositions);
    Log("Shader[%s] mSlotTextureCoords = %d\n", mName.c(), mSlotTextureCoords);
    
    Log("*******\n");
}

void ShaderProgramSprite::BindUniform(FUniforms *pUniform) {
    
    if (pUniform && pUniform->GetType() == UNIFORM_TYPE_BASIC) {
        ShaderProgram::BindUniform(pUniform);
        
        
        
        
        
        
        //
        
        
    } else {
        printf("Uniform wrong type? [%x]\n", pUniform);
    }
}

void ShaderProgramSprite::ArrayBufferTextureCoords(int pIndex, int pOffset) {
    glBindBuffer(GL_ARRAY_BUFFER, pIndex);
    glEnableVertexAttribArray(mSlotTextureCoords);
    int aStride = 2;
    unsigned char *aOffset = NULL;
    aOffset = &(aOffset[pOffset]);
    glVertexAttribPointer(mSlotTextureCoords, 2, GL_FLOAT, GL_FALSE, (aStride << 2), aOffset);
}
