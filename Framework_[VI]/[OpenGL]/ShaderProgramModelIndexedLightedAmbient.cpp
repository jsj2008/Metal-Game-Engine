//
//  ShaderProgramModelIndexedLightedAmbientLightedAmbient.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 3/15/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "core_includes.h"
#include "os_core_graphics.h"
#include "ShaderProgramModelIndexedLightedAmbient.hpp"

ShaderProgramModelIndexedLightedAmbient::ShaderProgramModelIndexedLightedAmbient(const char *pVertexPath, const char *pFragmentPath) : ShaderProgram(pVertexPath, pFragmentPath) {
    mDataOffset = 0;
    
    mSlotTexture = -1;
    mSlotTextureCoords = -1;
    mSlotAmbient = -1;
}

void ShaderProgramModelIndexedLightedAmbient::Compile() {
    
    ShaderProgram::Compile();
    
    if (IsValid() == false) return;
    
    //mSlotColors = glGetAttribLocation(mProgram, "Colors");
    mSlotTexture = glGetUniformLocation(mProgram, "Texture");
    mSlotAmbient = glGetUniformLocation(mProgram, "Ambient");
    
    mSlotTextureCoords = glGetAttribLocation(mProgram, "TextureCoords");

    
    
    Log("*******\n");
    Log("Shader[%s] mSlotProjectionUniform = %d\n", mName.c(), mSlotProjectionUniform);
    Log("Shader[%s] mSlotModelViewUniform = %d\n", mName.c(), mSlotModelViewUniform);
    Log("Shader[%s] mSlotModulateUniform = %d\n", mName.c(), mSlotModulateUniform);
    Log("Shader[%s] mSlotPositions = %d\n", mName.c(), mSlotPositions);
    Log("Shader[%s] mSlotTextureCoords = %d\n", mName.c(), mSlotTextureCoords);
    Log("Shader[%s] mSlotTexture = %d\n", mName.c(), mSlotTexture);
    Log("Shader[%s] mSlotAmbient = %d\n", mName.c(), mSlotAmbient);
    
    Log("*******\n");
}

void ShaderProgramModelIndexedLightedAmbient::BindUniform(FUniforms *pUniform) {
    if (pUniform && pUniform->GetType() == UNIFORM_TYPE_LIGHT_AMBIENT) {
        
        FUniformsLightAmbient *aUniform = (FUniformsLightAmbient *)pUniform;
        
        
        ShaderProgram::BindUniform(pUniform);
        
        //glUniformMatrix4fv(mSlotProjectionUniform, 1, 0, pUniform->mProjection.m);
        //glUniformMatrix4fv(mSlotModelViewUniform, 1, 0, pUniform->mModelView.m);
        glUniform4f(mSlotAmbient, aUniform->mLight.mRed, aUniform->mLight.mGreen, aUniform->mLight.mBlue,aUniform->mLight.mAmbientIntensity);
        
    } else {
        Log("Uniform wrong type? [%x]\n", pUniform);
    }
}

void ShaderProgramModelIndexedLightedAmbient::ArrayBufferData(int pIndex, int pOffset) {
    if (pIndex != -1) if (pIndex != -1) { glBindBuffer(GL_ARRAY_BUFFER, pIndex); }
    glEnableVertexAttribArray(mSlotPositions);
    int aStride = 3 + 3 + 3;
    unsigned char *aOffset = NULL;
    aOffset = &(aOffset[pOffset]);
    glVertexAttribPointer(mSlotPositions, 3, GL_FLOAT, GL_FALSE, (aStride << 2), aOffset);
    mDataOffset = pOffset;
}

void ShaderProgramModelIndexedLightedAmbient::ArrayBufferPositions(int pIndex, int pOffset) {
    if (pIndex != -1) if (pIndex != -1) { glBindBuffer(GL_ARRAY_BUFFER, pIndex); }
    glEnableVertexAttribArray(mSlotPositions);
    int aStride = 3 + 3 + 3;
    unsigned char *aOffset = NULL;
    aOffset = &(aOffset[pOffset + mDataOffset]);
    glVertexAttribPointer(mSlotPositions, 3, GL_FLOAT, GL_FALSE, (aStride << 2), aOffset);
}

void ShaderProgramModelIndexedLightedAmbient::ArrayBufferTextureCoords(int pIndex, int pOffset) {
    if (pIndex != -1) if (pIndex != -1) { glBindBuffer(GL_ARRAY_BUFFER, pIndex); }
    glEnableVertexAttribArray(mSlotTextureCoords);
    int aStride = 3 + 3 + 3;
    unsigned char *aOffset = NULL;
    aOffset = &(aOffset[pOffset + mDataOffset]);
    glVertexAttribPointer(mSlotTextureCoords, 3, GL_FLOAT, GL_FALSE, (aStride << 2), aOffset);
}

