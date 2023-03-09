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

#include "EngineInterface.h"
#include <stdio.h>
#include <stdlib.h>

struct SLEngineItf_ engineInterfaceFuncArray = {
    engineInterfaceCreateLEDDevice,
    engineInterfaceCreateVibraDevice,
    engineInterfaceCreateAudioPlayer,
    engineInterfaceCreateAudioRecorder,
    engineInterfaceCreateMidiPlayer,
    engineInterfaceCreateListener,
    engineInterfaceCreate3DGroup,
    engineInterfaceCreateOutputMix,
    engineInterfaceCreateMetadataExtractor,
    engineInterfaceCreateExtensionObject,
    engineInterfaceQueryNumSupportedInterfaces,
    engineInterfaceQuerySupportedInterfaces,
    engineInterfaceQueryNumSupportedExtensions,
    engineInterfaceQuerySupportedExtension,
    engineInterfaceIsExtensionSupported
};

struct EngineInterfaceEntry *engineInterfaces = NULL;

pthread_mutex_t engineInterfacesLock = PTHREAD_MUTEX_INITIALIZER;

SLresult engineInterfaceCreate(EngineInterface_t **interface) {
    pthread_mutex_lock(&engineInterfacesLock);
    struct EngineInterfaceEntry *entry = (struct EngineInterfaceEntry *)malloc(sizeof(struct EngineInterfaceEntry));
    if (entry != NULL) {
        entry->interface.self = &engineInterfaceFuncArray;
        entry->next = engineInterfaces;
        engineInterfaces = entry;
        *interface = &entry->interface;
        pthread_mutex_unlock(&engineInterfacesLock);
        return SL_RESULT_SUCCESS;
    }
    pthread_mutex_unlock(&engineInterfacesLock);
    return SL_RESULT_MEMORY_FAILURE;
}

SLresult engineInterfaceCreateLEDDevice(SLEngineItf self, SLObjectItf *pDevice, SLuint32 deviceID, SLuint32 numInterfaces, const SLInterfaceID *pInterfaceIds, const SLboolean *pInterfaceRequired) {
    puts("engineInterfaceCreateLEDDevice");
    return SL_RESULT_SUCCESS;
}

SLresult engineInterfaceCreateVibraDevice(SLEngineItf self, SLObjectItf *pDevice, SLuint32 deviceID, SLuint32 numInterfaces,const SLInterfaceID *pInterfaceIds, const SLboolean *pInterfaceRequired) {
    puts("engineInterfaceCreateVibraDevice");
    return SL_RESULT_SUCCESS;
}

SLresult engineInterfaceCreateAudioPlayer(SLEngineItf self, SLObjectItf *pPlayer, SLDataSource *pAudioSrc, SLDataSink *pAudioSnk, SLuint32 numInterfaces, const SLInterfaceID *pInterfaceIds, const SLboolean *pInterfaceRequired) {
    puts("engineInterfaceCreateAudioPlayer");
    return SL_RESULT_SUCCESS;
}

SLresult engineInterfaceCreateAudioRecorder(SLEngineItf self, SLObjectItf *pRecorder, SLDataSource *pAudioSrc, SLDataSink *pAudioSnk, SLuint32 numInterfaces, const SLInterfaceID *pInterfaceIds, const SLboolean *pInterfaceRequired) {
    puts("engineInterfaceCreateAudioRecorder");
    return SL_RESULT_SUCCESS;
}

SLresult engineInterfaceCreateMidiPlayer(SLEngineItf self, SLObjectItf *pPlayer, SLDataSource *pMIDISrc, SLDataSource *pBankSrc, SLDataSink *pAudioOutput, SLDataSink *pVibra, SLDataSink *pLEDArray, SLuint32 numInterfaces, const SLInterfaceID *pInterfaceIds, const SLboolean *pInterfaceRequired) {
    puts("engineInterfaceCreateMidiPlayer");
    return SL_RESULT_SUCCESS;
}

SLresult engineInterfaceCreateListener(SLEngineItf self, SLObjectItf *pListener, SLuint32 numInterfaces, const SLInterfaceID *pInterfaceIds, const SLboolean *pInterfaceRequired) {
    puts("engineInterfaceCreateListener");
    return SL_RESULT_SUCCESS;
}

SLresult engineInterfaceCreate3DGroup(SLEngineItf self, SLObjectItf *pGroup, SLuint32 numInterfaces, const SLInterfaceID *pInterfaceIds, const SLboolean *pInterfaceRequired) {
    puts("engineInterfaceCreate3DGroup");
    return SL_RESULT_SUCCESS;
}

SLresult engineInterfaceCreateOutputMix(SLEngineItf self, SLObjectItf *pMix, SLuint32 numInterfaces, const SLInterfaceID *pInterfaceIds, const SLboolean *pInterfaceRequired) {
    puts("engineInterfaceCreateOutputMix");
    return SL_RESULT_SUCCESS;
}

SLresult engineInterfaceCreateMetadataExtractor(SLEngineItf self, SLObjectItf *pMetadataExtractor, SLDataSource *pDataSource, SLuint32 numInterfaces, const SLInterfaceID *pInterfaceIds, const SLboolean *pInterfaceRequired) {
    puts("engineInterfaceCreateMetadataExtractor");
    return SL_RESULT_SUCCESS;
}

SLresult engineInterfaceCreateExtensionObject(SLEngineItf self, SLObjectItf *pObject, void *pParameters, SLuint32 objectID, SLuint32 numInterfaces, const SLInterfaceID *pInterfaceIds, const SLboolean *pInterfaceRequired) {
    puts("engineInterfaceCreateExtensionObject");
    return SL_RESULT_SUCCESS;
}

SLresult engineInterfaceQueryNumSupportedInterfaces(SLEngineItf self, SLuint32 objectID, SLuint32 *pNumSupportedInterfaces) {
    puts("engineInterfaceQueryNumSupportedInterfaces");
    return SL_RESULT_SUCCESS;
}

SLresult engineInterfaceQuerySupportedInterfaces(SLEngineItf self, SLuint32 objectID, SLuint32 index, SLInterfaceID *pInterfaceId) {
    puts("engineInterfaceQuerySupportedInterfaces");
    return SL_RESULT_SUCCESS;
}

SLresult engineInterfaceQueryNumSupportedExtensions(SLEngineItf self, SLuint32 *pNumExtensions) {
    puts("engineInterfaceQueryNumSupportedExtensions");
    return SL_RESULT_SUCCESS;
}

SLresult engineInterfaceQuerySupportedExtension(SLEngineItf self, SLuint32 index, SLchar *pExtensionName, SLint16 *pNameLength) {
    puts("engineInterfaceQuerySupportedExtension");
    return SL_RESULT_SUCCESS;
}

SLresult engineInterfaceIsExtensionSupported(SLEngineItf self, const SLchar *pExtensionName, SLboolean *pSupported) {
    puts("engineInterfaceIsExtensionSupported");
    return SL_RESULT_SUCCESS;
}

#ifdef __cplusplus
}
#endif