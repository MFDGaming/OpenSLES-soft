/*
 * Copyright (c) 2023 Alexander Argentakis
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef _OPENSLES_OBJECT_H_
#define _OPENSLES_OBJECT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "OpenSLES.h"
#include <pthread.h>

typedef enum {
    IOID_ENGINE,
    IOID_AUDIOPLAYER,
    IOID_OUTPUTMIX
} InternalObjectID_t;

typedef struct {
    struct SLObjectItf_ *self;
    InternalObjectID_t internalObjectID;
    SLInterfaceID *interfaceIDs;
    SLint16 numInterfaces;
    void **interfaces;
    void *extraData;
} Object_t;

struct ObjectEntry {
    Object_t object;
    struct ObjectEntry *next;
};

extern struct SLObjectItf_ objectFuncArray;

extern struct ObjectEntry *objects;

extern pthread_mutex_t objectsLock;

SLresult objectCreate(InternalObjectID_t objectID, Object_t **object);

SLresult objectRealize(SLObjectItf self, SLboolean async);

SLresult objectResume(SLObjectItf self, SLboolean async);

SLresult objectGetState(SLObjectItf self, SLuint32 *pState);

SLresult objectGetInterface(SLObjectItf self, const SLInterfaceID iid, void *pInterface);

SLresult objectRegisterCallback(SLObjectItf self, slObjectCallback callback, void *pContext);

void objectAbortAsyncOperation(SLObjectItf self);

void objectDestroy(SLObjectItf self);

SLresult objectSetPriority(SLObjectItf self, SLint32 priority, SLboolean preemptable);

SLresult objectGetPriority(SLObjectItf self, SLint32 *pPriority, SLboolean *pPreemptable);

SLresult objectSetLossOfControlInterfaces(SLObjectItf self, SLint16 numInterfaces, SLInterfaceID *pInterfaceIDs, SLboolean enabled);

#ifdef __cplusplus
}
#endif

#endif