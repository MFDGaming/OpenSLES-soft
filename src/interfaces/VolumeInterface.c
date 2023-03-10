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

#include "VolumeInterface.h"
#include <stdlib.h>

struct SLVolumeItf_ volumeInterfaceFuncArray = {
    volumeInterfaceSetVolumeLevel,
    volumeInterfaceGetVolumeLevel,
    volumeInterfaceGetMaxVolumeLevel,
    volumeInterfaceSetMute,
    volumeInterfaceGetMute,
    volumeInterfaceEnableStereoPosition,
    volumeInterfaceIsEnabledStereoPosition,
    volumeInterfaceSetStereoPosition,
    volumeInterfaceGetStereoPosition
};

struct VolumeInterfaceEntry *volumeInterfaces = NULL;

pthread_mutex_t volumeInterfacesLock = PTHREAD_MUTEX_INITIALIZER;

SLresult volumeInterfaceCreate(VolumeInterface_t **interface) {
    pthread_mutex_lock(&volumeInterfacesLock);
    struct VolumeInterfaceEntry *entry = (struct VolumeInterfaceEntry *)malloc(sizeof(struct VolumeInterfaceEntry));
    if (entry != NULL) {
        entry->interface.self = &volumeInterfaceFuncArray;
        entry->next = volumeInterfaces;
        volumeInterfaces = entry;
        *interface = &entry->interface;
        pthread_mutex_unlock(&volumeInterfacesLock);
        return SL_RESULT_SUCCESS;
    }
    pthread_mutex_unlock(&volumeInterfacesLock);
    return SL_RESULT_MEMORY_FAILURE;
}

SLresult volumeInterfaceSetVolumeLevel(SLVolumeItf self, SLmillibel level) {
    pthread_mutex_lock(&volumeInterfacesLock);
    struct VolumeInterfaceEntry *currentVolumeInterface = volumeInterfaces;
    while (currentVolumeInterface != NULL) {
        if (self == (SLVolumeItf)&currentVolumeInterface->interface.self) {
            currentVolumeInterface->interface.level = level;
            return SL_RESULT_SUCCESS;
        }
        currentVolumeInterface = currentVolumeInterface->next;
    }
    return SL_RESULT_IO_ERROR;
}

SLresult volumeInterfaceGetVolumeLevel(SLVolumeItf self, SLmillibel *pLevel) {
    pthread_mutex_lock(&volumeInterfacesLock);
    struct VolumeInterfaceEntry *currentVolumeInterface = volumeInterfaces;
    while (currentVolumeInterface != NULL) {
        if (self == (SLVolumeItf)&currentVolumeInterface->interface.self) {
            *pLevel = currentVolumeInterface->interface.level;
            pthread_mutex_unlock(&volumeInterfacesLock);
            return SL_RESULT_SUCCESS;
        }
        currentVolumeInterface = currentVolumeInterface->next;
    }
    pthread_mutex_unlock(&volumeInterfacesLock);
    return SL_RESULT_IO_ERROR;
}

SLresult volumeInterfaceGetMaxVolumeLevel(SLVolumeItf self, SLmillibel *pMaxLevel) {
    pthread_mutex_lock(&volumeInterfacesLock);
    struct VolumeInterfaceEntry *currentVolumeInterface = volumeInterfaces;
    while (currentVolumeInterface != NULL) {
        if (self == (SLVolumeItf)&currentVolumeInterface->interface.self) {
            *pMaxLevel = currentVolumeInterface->interface.maxLevel;
            pthread_mutex_unlock(&volumeInterfacesLock);
            return SL_RESULT_SUCCESS;
        }
        currentVolumeInterface = currentVolumeInterface->next;
    }
    pthread_mutex_unlock(&volumeInterfacesLock);
    return SL_RESULT_IO_ERROR;
}

SLresult volumeInterfaceSetMute(SLVolumeItf self, SLboolean mute) {
    pthread_mutex_lock(&volumeInterfacesLock);
    struct VolumeInterfaceEntry *currentVolumeInterface = volumeInterfaces;
    while (currentVolumeInterface != NULL) {
        if (self == (SLVolumeItf)&currentVolumeInterface->interface.self) {
            currentVolumeInterface->interface.muteOn = mute;
            pthread_mutex_unlock(&volumeInterfacesLock);
            return SL_RESULT_SUCCESS;
        }
        currentVolumeInterface = currentVolumeInterface->next;
    }
    pthread_mutex_unlock(&volumeInterfacesLock);
    return SL_RESULT_IO_ERROR;
}

SLresult volumeInterfaceGetMute(SLVolumeItf self, SLboolean *pMute) {
    pthread_mutex_lock(&volumeInterfacesLock);
    struct VolumeInterfaceEntry *currentVolumeInterface = volumeInterfaces;
    while (currentVolumeInterface != NULL) {
        if (self == (SLVolumeItf)&currentVolumeInterface->interface.self) {
            *pMute = currentVolumeInterface->interface.muteOn;
            pthread_mutex_unlock(&volumeInterfacesLock);
            return SL_RESULT_SUCCESS;
        }
        currentVolumeInterface = currentVolumeInterface->next;
    }
    pthread_mutex_unlock(&volumeInterfacesLock);
    return SL_RESULT_IO_ERROR;
}

SLresult volumeInterfaceEnableStereoPosition(SLVolumeItf self, SLboolean enable) {
    pthread_mutex_lock(&volumeInterfacesLock);
    struct VolumeInterfaceEntry *currentVolumeInterface = volumeInterfaces;
    while (currentVolumeInterface != NULL) {
        if (self == (SLVolumeItf)&currentVolumeInterface->interface.self) {
            currentVolumeInterface->interface.enableStereoPosition = enable;
            pthread_mutex_unlock(&volumeInterfacesLock);
            return SL_RESULT_SUCCESS;
        }
        currentVolumeInterface = currentVolumeInterface->next;
    }
    pthread_mutex_unlock(&volumeInterfacesLock);
    return SL_RESULT_IO_ERROR;
}

SLresult volumeInterfaceIsEnabledStereoPosition(SLVolumeItf self, SLboolean *pEnable) {
    pthread_mutex_lock(&volumeInterfacesLock);
    struct VolumeInterfaceEntry *currentVolumeInterface = volumeInterfaces;
    while (currentVolumeInterface != NULL) {
        if (self == (SLVolumeItf)&currentVolumeInterface->interface.self) {
            *pEnable = currentVolumeInterface->interface.enableStereoPosition;
            pthread_mutex_unlock(&volumeInterfacesLock);
            return SL_RESULT_SUCCESS;
        }
        currentVolumeInterface = currentVolumeInterface->next;
    }
    pthread_mutex_unlock(&volumeInterfacesLock);
    return SL_RESULT_IO_ERROR;
}

SLresult volumeInterfaceSetStereoPosition(SLVolumeItf self, SLpermille stereoPosition) {
    pthread_mutex_lock(&volumeInterfacesLock);
    struct VolumeInterfaceEntry *currentVolumeInterface = volumeInterfaces;
    while (currentVolumeInterface != NULL) {
        if (self == (SLVolumeItf)&currentVolumeInterface->interface.self) {
            currentVolumeInterface->interface.stereoPosition = stereoPosition;
            pthread_mutex_unlock(&volumeInterfacesLock);
            return SL_RESULT_SUCCESS;
        }
        currentVolumeInterface = currentVolumeInterface->next;
    }
    pthread_mutex_unlock(&volumeInterfacesLock);
    return SL_RESULT_IO_ERROR;
}

SLresult volumeInterfaceGetStereoPosition(SLVolumeItf self, SLpermille *pStereoPosition) {
    pthread_mutex_lock(&volumeInterfacesLock);
    struct VolumeInterfaceEntry *currentVolumeInterface = volumeInterfaces;
    while (currentVolumeInterface != NULL) {
        if (self == (SLVolumeItf)&currentVolumeInterface->interface.self) {
            *pStereoPosition = currentVolumeInterface->interface.stereoPosition;
            pthread_mutex_unlock(&volumeInterfacesLock);
            return SL_RESULT_SUCCESS;
        }
        currentVolumeInterface = currentVolumeInterface->next;
    }
    pthread_mutex_unlock(&volumeInterfacesLock);
    return SL_RESULT_IO_ERROR;
}

#ifdef __cplusplus
}
#endif