#include <iostream>
#include <cstdio>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

int main() {
    const char* filename = "/home/pranav/Music/muzik.mp3";

    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return -1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
        std::cerr << "SDL_mixer initialization failed: " << Mix_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    Mix_Music* music = Mix_LoadMUS(filename);
    if (!music) {
        std::cerr << "Failed to load music: " << Mix_GetError() << std::endl;
        Mix_CloseAudio();
        SDL_Quit();
        return -1;
    }

    if (Mix_PlayMusic(music, 0) == -1) {
        std::cerr << "Failed to play music: " << Mix_GetError() << std::endl;
        Mix_FreeMusic(music);
        Mix_CloseAudio();
        SDL_Quit();
        return -1;
    }

    //102 seconds is the length of the currently loaded music
     //SDL_Delay(102000);

    char ch;
    bool playing = true;
    while ((ch = getchar()) != 'q') {
        switch(ch) {
            case 'p':
            case 'P':
                if (playing)
                    Mix_PauseMusic();
                else
                    Mix_ResumeMusic();
                playing = !playing;
                break;
        } 
    }

    Mix_FreeMusic(music);
    Mix_CloseAudio();
    SDL_Quit();

    return 0;
}

