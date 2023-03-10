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

#include "ObjectInterface.h"
#include "../objects/EngineObject.h"
#include <stdlib.h>
#include <stdio.h>

struct SLObjectItf_ objectInterfaceFuncArray = {
    objectInterfaceRealize,
    objectInterfaceResume,
    objectInterfaceGetState,
    objectInterfaceGetInterface,
    objectInterfaceRegisterCallback,
    objectInterfaceAbortAsyncOperation,
    objectInterfaceDestroy,
    objectInterfaceSetPriority,
    objectInterfaceGetPriority,
    objectInterfaceSetLossOfControlInterfaces
};

struct ObjectInterfaceEntry *objectInterfaces = NULL;

pthread_mutex_t objectInterfacesLock = PTHREAD_MUTEX_INITIALIZER;

SLresult objectInterfaceCreate(InternalObjectInterfaceID_t objectID, ObjectInterface_t **interface) {
    pthread_mutex_lock(&objectInterfacesLock);
    struct ObjectInterfaceEntry *entry = (struct ObjectInterfaceEntry *)malloc(sizeof(struct ObjectInterfaceEntry));
    if (entry != NULL) {
        entry->interface.self = &objectInterfaceFuncArray;
        entry->interface.internalObjectID = objectID;
        entry->interface.interfaceIDs = NULL;
        entry->interface.interfaces = NULL;
        entry->interface.numInterfaces = 0;
        entry->interface.extraData = NULL;
        entry->next = objectInterfaces;
        objectInterfaces = entry;
        *interface = &entry->interface;
        pthread_mutex_unlock(&objectInterfacesLock);
        return SL_RESULT_SUCCESS;
    }
    pthread_mutex_unlock(&objectInterfacesLock);
    return SL_RESULT_MEMORY_FAILURE;
}

SLresult objectInterfaceRealize(SLObjectItf self, SLboolean async) {
    puts("objectRealize");
    struct ObjectInterfaceEntry *currentObjectInterface = objectInterfaces;
    while (currentObjectInterface != NULL) {
        if (self == (SLObjectItf)&currentObjectInterface->interface.self) {
            if (currentObjectInterface->interface.internalObjectID == IOID_ENGINE) {
                engineObjectRealize(&currentObjectInterface->interface, async);
                for (SLint32 i = 0; i < currentObjectInterface->interface.numInterfaces; ++i) {
                    if (currentObjectInterface->interface.interfaceIDs[i] == SL_IID_VOLUME) {

                    } else if (currentObjectInterface->interface.interfaceIDs[i] == SL_IID_BUFFERQUEUE) {

                    } 
                }
            }
        }
        currentObjectInterface = currentObjectInterface->next;
    }
    return SL_RESULT_SUCCESS;
}

SLresult objectInterfaceResume(SLObjectItf self, SLboolean async) {
    puts("objectResume");
    return SL_RESULT_SUCCESS;
}

SLresult objectInterfaceGetState(SLObjectItf self, SLuint32 *pState) {
    puts("objectGetState");
    return SL_RESULT_SUCCESS;
}

SLresult objectInterfaceGetInterface(SLObjectItf self, const SLInterfaceID iid, void *pInterface) {
    puts("objectGetInterface");
    struct ObjectInterfaceEntry *currentObjectInterface = objectInterfaces;
    while (currentObjectInterface != NULL) {
        if (self == (SLObjectItf)&currentObjectInterface->interface.self) {
            if (currentObjectInterface->interface.internalObjectID == IOID_ENGINE) {
                engineObjectInterface(&currentObjectInterface->interface, iid, pInterface);
                for (SLint32 i = 0; i < currentObjectInterface->interface.numInterfaces; ++i) {
                    if (currentObjectInterface->interface.interfaceIDs[i] == SL_IID_VOLUME) {

                    } else if (currentObjectInterface->interface.interfaceIDs[i] == SL_IID_BUFFERQUEUE) {

                    } 
                }
            }
        }
        currentObjectInterface = currentObjectInterface->next;
    }
    return SL_RESULT_SUCCESS;
}

SLresult objectInterfaceRegisterCallback(SLObjectItf self, slObjectCallback callback, void *pContext) {
    puts("objectRegisterCallback");
    return SL_RESULT_SUCCESS;
}

void objectInterfaceAbortAsyncOperation(SLObjectItf self) {
    puts("objectAbortAsyncOperation");
}

void objectInterfaceDestroy(SLObjectItf self) {
    puts("objectDestroy");
}

SLresult objectInterfaceSetPriority(SLObjectItf self, SLint32 priority, SLboolean preemptable) {
    puts("objectSetPriority");
    return SL_RESULT_SUCCESS;
}

SLresult objectInterfaceGetPriority(SLObjectItf self, SLint32 *pPriority, SLboolean *pPreemptable) {
    puts("objectGetPriority");
    return SL_RESULT_SUCCESS;
}

SLresult objectInterfaceSetLossOfControlInterfaces(SLObjectItf self, SLint16 numInterfaces, SLInterfaceID *pInterfaceIDs, SLboolean enabled) {
    puts("objectSetLossOfControlInterfaces");
    return SL_RESULT_SUCCESS;
}