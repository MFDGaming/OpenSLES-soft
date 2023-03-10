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

#include "../OpenSLES.h"
#include <pthread.h>

typedef enum {
    IOID_ENGINE,
    IOID_AUDIOPLAYER,
    IOID_OUTPUTMIX
} InternalObjectInterfaceID_t;

typedef struct {
    struct SLObjectItf_ *self;
    InternalObjectInterfaceID_t internalObjectID;
    SLInterfaceID *interfaceIDs;
    SLint16 numInterfaces;
    void **interfaces;
    void *extraData;
} ObjectInterface_t;

struct ObjectInterfaceEntry {
    ObjectInterface_t interface;
    struct ObjectInterfaceEntry *next;
};

extern struct SLObjectItf_ objectInterfaceFuncArray;

extern struct ObjectInterfaceEntry *objectInterfaces;

extern pthread_mutex_t objectInterfacesLock;

SLresult objectInterfaceCreate(InternalObjectInterfaceID_t objectID, ObjectInterface_t **interface);

SLresult objectInterfaceRealize(SLObjectItf self, SLboolean async);

SLresult objectInterfaceResume(SLObjectItf self, SLboolean async);

SLresult objectInterfaceGetState(SLObjectItf self, SLuint32 *pState);

SLresult objectInterfaceGetInterface(SLObjectItf self, const SLInterfaceID iid, void *pInterface);

SLresult objectInterfaceRegisterCallback(SLObjectItf self, slObjectCallback callback, void *pContext);

void objectInterfaceAbortAsyncOperation(SLObjectItf self);

void objectInterfaceDestroy(SLObjectItf self);

SLresult objectInterfaceSetPriority(SLObjectItf self, SLint32 priority, SLboolean preemptable);

SLresult objectInterfaceGetPriority(SLObjectItf self, SLint32 *pPriority, SLboolean *pPreemptable);

SLresult objectInterfaceSetLossOfControlInterfaces(SLObjectItf self, SLint16 numInterfaces, SLInterfaceID *pInterfaceIDs, SLboolean enabled);

#ifdef __cplusplus
}
#endif

#endif