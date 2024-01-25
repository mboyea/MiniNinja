#ifndef AUDIO_H
#define AUDIO_H
#pragma once

#include <SDL_mixer.h>
#include <string>
#include <cstdint>

void InitAudio(std::string filePathDefault = "", int rate = 22050, uint16_t format = AUDIO_S16SYS, int channels = 2, int buffers = 4096);

bool LoadAudio(std::string filePath);
void LoadAudioFromDirectory(std::string folderPath);
bool UnloadAudio(std::string key);
void UnloadAllAudio();
bool IsAudio(std::string key);
Mix_Chunk* GetAudio(std::string key);
std::string GetKey(Mix_Chunk* audio);
void PlayAudio(Mix_Chunk* audio);
void PlayAudio(std::string key);

#endif // !AUDIO_H