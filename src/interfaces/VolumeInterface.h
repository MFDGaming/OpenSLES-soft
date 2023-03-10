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

#ifndef _OPENSLES_ENGINEINTERFACE_H_
#define _OPENSLES_ENGINEINTERFACE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "../OpenSLES.h"
#include <pthread.h>

typedef struct {
    struct SLVolumeItf_ *self;
    SLmillibel level;
    SLmillibel maxLevel;
    SLboolean muteOn;
    SLboolean enableStereoPosition;
    SLpermille stereoPosition;
} VolumeInterface_t;

struct VolumeInterfaceEntry {
    VolumeInterface_t interface;
    struct VolumeInterfaceEntry *next;
};

extern struct SLVolumeItf_ volumeInterfaceFuncArray;

extern struct VolumeInterfaceEntry *volumeInterfaces;

extern pthread_mutex_t volumeInterfacesLock;

SLresult volumeInterfaceCreate(VolumeInterface_t **interface);

SLresult volumeInterfaceSetVolumeLevel(SLVolumeItf self, SLmillibel level);

SLresult volumeInterfaceGetVolumeLevel(SLVolumeItf self, SLmillibel *pLevel);

SLresult volumeInterfaceGetMaxVolumeLevel(SLVolumeItf self, SLmillibel *pMaxLevel);

SLresult volumeInterfaceSetMute(SLVolumeItf self, SLboolean mute);

SLresult volumeInterfaceGetMute(SLVolumeItf self, SLboolean *pMute);

SLresult volumeInterfaceEnableStereoPosition(SLVolumeItf self, SLboolean enable);

SLresult volumeInterfaceIsEnabledStereoPosition(SLVolumeItf self, SLboolean *pEnable);

SLresult volumeInterfaceSetStereoPosition(SLVolumeItf self, SLpermille stereoPosition);

SLresult volumeInterfaceGetStereoPosition(SLVolumeItf self, SLpermille *pStereoPosition);

#ifdef __cplusplus
}
#endif

#endif