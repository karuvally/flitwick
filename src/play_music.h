#include <iostream>
#include <cstdlib>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_mixer.h>

class MusicPlayer {
    private:
        std::string currentTrack;
        Mix_Music* music;
        int musicOpen = 0;
        int musicVolume = MIX_MAX_VOLUME;
        int looping = 0;
        SDL_AudioSpec spec;

    public:
        MusicPlayer() {
            spec.freq = 44100;
            spec.format = MIX_DEFAULT_FORMAT;
            spec.channels = MIX_DEFAULT_CHANNELS;

            // Initialize SDL library          
            if (SDL_Init(SDL_INIT_AUDIO) < 0) {
                std::cerr << "Couldn't Initialize SDL: " << SDL_GetError() << '\n';
                exit(255);
            }

            // Open Audio device
            if (Mix_OpenAudio(spec.freq, spec.format, spec.channels, 1024) < 0) {
                SDL_Log("Couldn't open audio: %s\n", SDL_GetError());
                SDL_Quit();
                exit(2);
            } else {
                Mix_QuerySpec(&spec.freq, &spec.format, (int *)&spec.channels);
                SDL_Log("Opened audio at %d Hz %d bit%s %s audio format", spec.freq,
                    (spec.format&0xFF),
                    (SDL_AUDIO_ISFLOAT(spec.format) ? " (float)" : ""),
                    (spec.channels > 2) ? "surround" : (spec.channels > 1) ? "stereo" : "mono"
                );
            }

            Mix_VolumeMusic(musicVolume);
        }

        void loadMusic(const char* filename) {
            std::cout << "Loading music " << filename << '\n';
            currentTrack = filename;

            if (musicOpen) {
                musicOpen = 0;
                Mix_FreeMusic(music);
                music = NULL;
            }
            musicOpen = 1;
            music = Mix_LoadMUS(filename);

            if (music == NULL) {
                SDL_Log("Couldn't load music file: %s\n", SDL_GetError());
            }

            // 2nd argument -1 puts the current track on a loop
            if (Mix_PlayMusic(music, -1) == -1) {
                SDL_Log("Failed to play music: %s\n", SDL_GetError());
            }
        }

        void freeMusicMemory() {
            if (music) {
                Mix_FreeMusic(music);
                music = NULL;
            }
            Mix_CloseAudio();
            SDL_Quit();

            std::cout << "Cleared all the clunky memory\n";
        }
        
        void stopMusic() {
            std::cout << "Stopping Music\n";
            musicOpen = 0;
            Mix_FreeMusic(music);
            music = NULL;

            //Mix_CloseAudio();
            //SDL_Quit();
        }

        void pauseMusic() {
            std::cout << "Music paused\n";
            if (Mix_PlayingMusic())
                Mix_PauseMusic();
        }

        void resumeMusic() {
            std::cout << "Music resumed\n";
            if (!(Mix_PausedMusic() || Mix_PlayingMusic()))
                loadMusic(currentTrack.data());
            else if (Mix_PausedMusic())
                Mix_ResumeMusic();
        }

        void setVolume(int val) {
            musicVolume = (val > 100) ? 100 : (val < 0) ? 0 : val;
            Mix_VolumeMusic(musicVolume);
            std::cout << "Music volume: " << musicVolume << '\n';
        }

        inline bool isMusicPlaying() {
            return Mix_PlayingMusic() || Mix_PausedMusic();
        }

        inline int getVolume() {
            return musicVolume;
        }

        inline void seekMusicTo(int pos) {
            Mix_SetMusicPosition(pos);
        }
};

// int main() {
//     MusicPlayer player = MusicPlayer();
//     player.loadMusic("/home/pranav/Music/muzik.mp3");
    
//     char ch;
//     int val;

//     while ((ch = getchar()) != '9') {
//         switch(ch) {
//             case 'p': case 'P':
//                 player.pauseMusic();
//                 break;
//             case 'r': case 'R':
//                 player.resumeMusic();
//                 break;
//             case 's': case 'S':
//                 player.stopMusic();
//                 break;
//             case '+':
//                 val = player.getVolume();
//                 player.setVolume(val + 10);
//                 break;
//             case '-':
//                 val = player.getVolume();
//                 player.setVolume(val - 10);
//                 break;
//             case '7':
//                 player.seekMusicTo(230);
//                 break;
//         }
//     }

//     return 0;
// }