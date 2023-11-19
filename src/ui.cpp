#include <memory>

#include "play_music.h"

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Slider.H>
#include <FL/Fl_Value_Slider.H>

MusicPlayer musicPlayer = MusicPlayer();

Fl_Menu_Bar* makeMenuBar() {
// Creates menu bar

    Fl_Menu_Item menuitems[] = {
        {"&File", 0, 0, 0, FL_SUBMENU}, // File
            {"&Open File", 0},
            {"&Add File", 0},
            {"&Add Folder", 0},
            {"&New Playlist", 0},
            {"&Add Playlist", 0},
            {"&Save Playlist", 0},
            {"&Quit", 0},
            {0},
        {"&Edit", 0, 0, 0, FL_SUBMENU}, // Edit
            {"&Clear", 0},
            {"&Select all", 0},
            {"&Deselect all", 0},
            {"&Invert selection", 0},
            {"&Selection", 0},
            {"&Find", 0},
            {"&Sort by", 0},
            {"&Preferences", 0},
            {0},
        {"&View", 0, 0, 0, FL_SUBMENU}, // View
            {"&Status bar", 0},
            {"&Equalizer", 0},
            {"&Design mode", 0},
            {"&Log", 0},
            {0},
        {"&Playback", 0, 0, 0, FL_SUBMENU}, // Playback
            {"&Shuffle", 0},
            {"&Repeat", 0},
            {"&Stop after current track", 0},
            {"&Stop after current album", 0},
            {0},
        {"&Help", 0, 0, 0, FL_SUBMENU}, // Help
            {"&Help", 0},
            {"&ChangeLog", 0},
            {0},
        { 0 }
    };

    auto playerMenu = new Fl_Menu_Bar(0, 0, 500, 30);
    playerMenu->copy(menuitems);

    return playerMenu;
}

Fl_Button* makeButton(const int x, const int y, const char* label, void (*func)()) {
// Creates new buttons
    Fl_Button *button = new Fl_Button(x, y, 25, 25, label);
    button->type(FL_NORMAL_BUTTON);
    button->callback((Fl_Callback*)func);

    return button;
}

Fl_Slider* makeSeekSlider(const int x, const int y, const int w, const int h) {
// Creates seek slider
    Fl_Slider *slider = new Fl_Slider(x, y, w, h);
    slider->type(FL_HOR_NICE_SLIDER);
    slider->value(0);

    return slider;
}

void volumeMusicCb(Fl_Widget*, void*);

Fl_Slider* makeVolumeSlider(const int x, const int y, const int w, const int h) {
// Creates Volume slider
    Fl_Value_Slider *slider = new Fl_Value_Slider(x, y, w, h);
    slider->type(FL_HOR_NICE_SLIDER);
    slider->minimum(0);
    slider->maximum(100);
    slider->value(80);
    slider->callback(volumeMusicCb, slider);

    return slider;
}

/*  The following 4 functions are used just as to
    satisfy the ISO C++ constraints of:

    "ISO C++ forbids taking the address of an
    unqualified or parenthesized non-static member
    function to form a pointer to member function."  */

void stopMusicCb() {
    musicPlayer.stopMusic();
}

void pauseMusicCb() {
    musicPlayer.pauseMusic();
}

void resumeMusicCb() {
    musicPlayer.resumeMusic();
}

void volumeMusicCb(Fl_Widget*, void* v) {
    Fl_Value_Slider* slider = (Fl_Value_Slider*)v;
    musicPlayer.setVolume(slider->value());
}

void dummy() {
    std::cout << "This function is bound to do something\n";
}

int player(int argc, char** argv) {
    auto playerWindow = std::make_unique<Fl_Window>(500, 300, "Flitwick");

    Fl_Menu_Bar* playerMenu = makeMenuBar();
    
    Fl_Button* stopButton = makeButton(5, 35, "@square", &stopMusicCb);
    Fl_Button* playButton = makeButton(35, 35, "@>", &resumeMusicCb);
    Fl_Button* pauseButton = makeButton(65, 35, "@||", &pauseMusicCb);
    Fl_Button* backwardButton = makeButton(95, 35, "@<<", &dummy);
    Fl_Button* forwardButton = makeButton(125, 35, "@>>", &dummy);

    Fl_Slider* seekSlider = makeSeekSlider(155, 40, 210, 15);
    Fl_Slider* volumeSlider = makeVolumeSlider(385, 40, 110, 15);

    musicPlayer.loadMusic("/home/pranav/Music/muzik.mp3");

    playerWindow->end();
    playerWindow->show(argc, argv);

    return Fl::run();
}

int main(int argc, char** argv) {
    player(argc, argv);
    musicPlayer.freeMusicMemory();

    return 0;
}