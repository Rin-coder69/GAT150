/*
#include "AudioSource.h"
#include "Audio/AudioClip.h"
#include "Enging.h"

namespace gaia{
FACTORY_REGISTER(AudioSource)
void AudioSource::Update(float dt){
}
void AudioSource::Play(){
auto audioClip = Resources(). Get<AudioClip>(audioClipName, GetEngine().Get

if(audioClip){
GetEngine().GetAudio().PlaySound(*audioClip);
}
}
}*/