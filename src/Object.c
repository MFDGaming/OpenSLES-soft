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

#ifdef __cplusplus
extern "C" {
#endif

#include "Object.h"
#include "./objects/EngineObject.h"
#include <stdlib.h>
#include <stdio.h>

struct SLObjectItf_ objectFuncArray = {
    objectRealize,
    objectResume,
    objectGetState,
    objectGetInterface,
    objectRegisterCallback,
    objectAbortAsyncOperation,
    objectDestroy,
    objectSetPriority,
    objectGetPriority,
    objectSetLossOfControlInterfaces
};

struct ObjectEntry *objects = NULL;

pthread_mutex_t objectsLock = PTHREAD_MUTEX_INITIALIZER;

SLresult objectCreate(InternalObjectID_t objectID, Object_t **object) {
    pthread_mutex_lock(&objectsLock);
    struct ObjectEntry *entry = (struct ObjectEntry *)malloc(sizeof(struct ObjectEntry));
    if (entry != NULL) {
        entry->object.self = &objectFuncArray;
        entry->object.internalObjectID = objectID;
        entry->object.interfaceIDs = NULL;
        entry->object.interfaces = NULL;
        entry->object.numInterfaces = 0;
        entry->object.extraData = NULL;
        entry->next = objects;
        objects = entry;
        *object = &entry->object;
        pthread_mutex_unlock(&objectsLock);
        return SL_RESULT_SUCCESS;
    }
    pthread_mutex_unlock(&objectsLock);
    return SL_RESULT_MEMORY_FAILURE;
}

SLresult objectRealize(SLObjectItf self, SLboolean async) {
    puts("objectRealize");
    struct ObjectEntry *current_object = objects;
    while (current_object != NULL) {
        if (self == (SLObjectItf)&current_object->object.self) {
            if (current_object->object.internalObjectID == IOID_ENGINE) {
                engineObjectRealize(&current_object->object, async);
            }
            for (SLint32 i = 0; i < current_object->object.numInterfaces; ++i) {
                if (current_object->object.interfaceIDs[i] == SL_IID_VOLUME) {

                } else if (current_object->object.interfaceIDs[i] == SL_IID_BUFFERQUEUE) {

                } 
            }
        }
        current_object = current_object->next;
    }
    return SL_RESULT_SUCCESS;
}

SLresult objectResume(SLObjectItf self, SLboolean async) {
    puts("objectResume");
    return SL_RESULT_SUCCESS;
}

SLresult objectGetState(SLObjectItf self, SLuint32 *pState) {
    puts("objectGetState");
    return SL_RESULT_SUCCESS;
}

SLresult objectGetInterface(SLObjectItf self, const SLInterfaceID iid, void *pInterface) {
    puts("objectGetInterface");
    struct ObjectEntry *current_object = objects;
    while (current_object != NULL) {
        if (self == (SLObjectItf)&current_object->object.self) {
            if (current_object->object.internalObjectID == IOID_ENGINE) {
                engineObjectInterface(&current_object->object, iid, pInterface);
            }
            for (SLint32 i = 0; i < current_object->object.numInterfaces; ++i) {
                if (current_object->object.interfaceIDs[i] == SL_IID_VOLUME) {

                } else if (current_object->object.interfaceIDs[i] == SL_IID_BUFFERQUEUE) {
                    
                } 
            }
        }
        current_object = current_object->next;
    }
    return SL_RESULT_SUCCESS;
}

SLresult objectRegisterCallback(SLObjectItf self, slObjectCallback callback, void *pContext) {
    puts("objectRegisterCallback");
    return SL_RESULT_SUCCESS;
}

void objectAbortAsyncOperation(SLObjectItf self) {
    puts("objectAbortAsyncOperation");
}

void objectDestroy(SLObjectItf self) {
    puts("objectDestroy");
}

SLresult objectSetPriority(SLObjectItf self, SLint32 priority, SLboolean preemptable) {
    puts("objectSetPriority");
    return SL_RESULT_SUCCESS;
}

SLresult objectGetPriority(SLObjectItf self, SLint32 *pPriority, SLboolean *pPreemptable) {
    puts("objectGetPriority");
    return SL_RESULT_SUCCESS;
}

SLresult objectSetLossOfControlInterfaces(SLObjectItf self, SLint16 numInterfaces, SLInterfaceID *pInterfaceIDs, SLboolean enabled) {
    puts("objectSetLossOfControlInterfaces");
    return SL_RESULT_SUCCESS;
}