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
    struct SLEngineItf_ *self;
    SLuint32 audioPlayerCount;
    struct SLObjectItf_ **audioPlayerObjs;
    SLuint32 outputMixCount;
    struct SLObjectItf_ **outputMixQueueObjs;
} EngineInterface_t;

struct EngineInterfaceEntry {
    EngineInterface_t interface;
    struct EngineInterfaceEntry *next;
};

extern struct SLEngineItf_ engineInterfaceFuncArray;

extern struct EngineInterfaceEntry *engineInterfaces;

extern pthread_mutex_t engineInterfacesLock;

SLresult engineInterfaceCreate(EngineInterface_t **interface);

SLresult engineInterfaceCreateLEDDevice(SLEngineItf self, SLObjectItf *pDevice, SLuint32 deviceID, SLuint32 numInterfaces, const SLInterfaceID *pInterfaceIds, const SLboolean *pInterfaceRequired);

SLresult engineInterfaceCreateVibraDevice(SLEngineItf self, SLObjectItf *pDevice, SLuint32 deviceID, SLuint32 numInterfaces,const SLInterfaceID *pInterfaceIds, const SLboolean *pInterfaceRequired);

SLresult engineInterfaceCreateAudioPlayer(SLEngineItf self, SLObjectItf *pPlayer, SLDataSource *pAudioSrc, SLDataSink *pAudioSnk, SLuint32 numInterfaces, const SLInterfaceID *pInterfaceIds, const SLboolean *pInterfaceRequired);

SLresult engineInterfaceCreateAudioRecorder(SLEngineItf self, SLObjectItf *pRecorder, SLDataSource *pAudioSrc, SLDataSink *pAudioSnk, SLuint32 numInterfaces, const SLInterfaceID *pInterfaceIds, const SLboolean *pInterfaceRequired);

SLresult engineInterfaceCreateMidiPlayer(SLEngineItf self, SLObjectItf *pPlayer, SLDataSource *pMIDISrc, SLDataSource *pBankSrc, SLDataSink *pAudioOutput, SLDataSink *pVibra, SLDataSink *pLEDArray, SLuint32 numInterfaces, const SLInterfaceID *pInterfaceIds, const SLboolean *pInterfaceRequired);

SLresult engineInterfaceCreateListener(SLEngineItf self, SLObjectItf *pListener, SLuint32 numInterfaces, const SLInterfaceID *pInterfaceIds, const SLboolean *pInterfaceRequired);

SLresult engineInterfaceCreate3DGroup(SLEngineItf self, SLObjectItf *pGroup, SLuint32 numInterfaces, const SLInterfaceID *pInterfaceIds, const SLboolean *pInterfaceRequired);

SLresult engineInterfaceCreateOutputMix(SLEngineItf self, SLObjectItf *pMix, SLuint32 numInterfaces, const SLInterfaceID *pInterfaceIds, const SLboolean *pInterfaceRequired);

SLresult engineInterfaceCreateMetadataExtractor(SLEngineItf self, SLObjectItf *pMetadataExtractor, SLDataSource *pDataSource, SLuint32 numInterfaces, const SLInterfaceID *pInterfaceIds, const SLboolean *pInterfaceRequired);

SLresult engineInterfaceCreateExtensionObject(SLEngineItf self, SLObjectItf *pObject, void *pParameters, SLuint32 objectID, SLuint32 numInterfaces, const SLInterfaceID *pInterfaceIds, const SLboolean *pInterfaceRequired);

SLresult engineInterfaceQueryNumSupportedInterfaces(SLEngineItf self, SLuint32 objectID, SLuint32 *pNumSupportedInterfaces);

SLresult engineInterfaceQuerySupportedInterfaces(SLEngineItf self, SLuint32 objectID, SLuint32 index, SLInterfaceID *pInterfaceId);

SLresult engineInterfaceQueryNumSupportedExtensions(SLEngineItf self, SLuint32 *pNumExtensions);

SLresult engineInterfaceQuerySupportedExtension(SLEngineItf self, SLuint32 index, SLchar *pExtensionName, SLint16 *pNameLength);

SLresult engineInterfaceIsExtensionSupported(SLEngineItf self, const SLchar *pExtensionName, SLboolean *pSupported);

#ifdef __cplusplus
}
#endif

#endif