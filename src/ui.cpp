#include <memory>

#include "play_music.h"

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Slider.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Native_File_Chooser.H>

MusicPlayer musicPlayer = MusicPlayer();
std::string fileName = "";

struct FlitWidgets {
    Fl_Button* stopButton; 
    Fl_Button* playButton; 
    Fl_Button* pauseButton;
    Fl_Button* backwardButton;
    Fl_Button* forwardButton;

    Fl_Slider* seekSlider; 
    Fl_Slider* volumeSlider;
} flitWidgets;

struct ButtonProperties {
    const char* label;
    const char shortcut;
    void (*callback) (); 
};

void dummy();
void stopMusicCb();
void pauseMusicCb();
void resumeMusicCb();
void chooseFileCb();
void seekSliderWithTimeCb(void*);
void volumeMusicCb(Fl_Widget*, void*);
void volumeMusicCb(Fl_Widget*, void*);
void seekToPositionCb(Fl_Widget*, void*);
void seekToPositionCb(Fl_Widget*, void*);

Fl_Menu_Bar* makeMenuBar();
Fl_Button* makeButton(const int, const int, const struct ButtonProperties&);
Fl_Slider* makeSeekSlider(const int, const int, const int, const int);
Fl_Slider* makeVolumeSlider(const int, const int, const int, const int);

Fl_Menu_Bar* makeMenuBar() {
// Creates menu bar

    Fl_Menu_Item menuitems[] = {
        {"&File", 0, 0, 0, FL_SUBMENU}, // File
            {"&Open File", FL_COMMAND + 'o', (Fl_Callback*)chooseFileCb},
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

Fl_Button* makeButton(const int x, const int y, const struct ButtonProperties &buttonProperties) {
// Creates new buttons
    Fl_Button *button = new Fl_Button(x, y, 25, 25, buttonProperties.label);
    button->type(FL_NORMAL_BUTTON);
    button->callback((Fl_Callback*)(buttonProperties.callback));
    button->shortcut(buttonProperties.shortcut);

    return button;
}

Fl_Slider* makeSeekSlider(const int x, const int y, const int w, const int h) {
// Creates seek slider
    Fl_Slider *slider = new Fl_Slider(x, y, w, h);
    slider->type(FL_HOR_NICE_SLIDER);
    slider->minimum(0);
    slider->maximum(100);
    slider->value(0);
    slider->callback(seekToPositionCb, slider);

    return slider;
}

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

/*  The following 7 functions are used just as to
    satisfy the ISO C++ constraints of:

    "ISO C++ forbids taking the address of an
    unqualified or parenthesized non-static member
    function to form a pointer to member function."  */

void stopMusicCb() {
    musicPlayer.stopMusic();
    flitWidgets.seekSlider->value(0);
}

void pauseMusicCb() {
    if (musicPlayer.isMusicPlaying())
        musicPlayer.pauseMusic();
}

void resumeMusicCb() {
    if (!musicPlayer.isMusicPlaying()) {
        musicPlayer.resumeMusic();
        Fl::add_timeout(1.0, seekSliderWithTimeCb);
    }
}

void volumeMusicCb(Fl_Widget*, void* v) {
    Fl_Value_Slider* slider = (Fl_Value_Slider*)v;
    musicPlayer.setVolume(slider->value());
}

void seekToPositionCb(Fl_Widget*, void* v) {
    Fl_Slider* slider = (Fl_Slider*)v;
    double length = musicPlayer.getMusicLength();
    double pos = (slider->value()/slider->maximum())*length;
    musicPlayer.seekMusicTo(pos);
}

void seekSliderWithTimeCb(void* v) {
    double pos = (musicPlayer.getMusicPosition()/musicPlayer.getMusicLength())*100;
    flitWidgets.seekSlider->value(pos);
    if (musicPlayer.isMusicPlaying())
        Fl::repeat_timeout(0.5, seekSliderWithTimeCb);
}

void dummy() {
    std::cout << "This function is bound to do something\n";
}

void chooseFileCb() {
    auto fileChooser = std::make_unique<Fl_Native_File_Chooser>();
    if (fileChooser->show() == 0) {
        fileName = fileChooser->filename();
        if (fileName.length() > 0) {
            musicPlayer.loadMusic(fileName.data());
            Fl::add_timeout(0.5, seekSliderWithTimeCb);
        }
    }
}

const struct ButtonProperties stopButtonProperties = {"@square", 's', &stopMusicCb};
const struct ButtonProperties playButtonProperties = {"@>", 'p', &resumeMusicCb};
const struct ButtonProperties pauseButtonProperties = {"@||", 'h', &pauseMusicCb};
const struct ButtonProperties backwardButtonProperties = {"@<<", '<', &dummy};
const struct ButtonProperties forwardButtonProperties= {"@>>", '>', &dummy};


int player(int argc, char** argv) {
    auto playerWindow = std::make_unique<Fl_Window>(500, 300, "Flitwick");

    Fl_Menu_Bar* playerMenu = makeMenuBar();
    
    flitWidgets.stopButton = makeButton(5, 35, stopButtonProperties);
    flitWidgets.playButton = makeButton(35, 35, playButtonProperties);
    flitWidgets.pauseButton = makeButton(65, 35, pauseButtonProperties);
    flitWidgets.backwardButton = makeButton(95, 35, backwardButtonProperties);
    flitWidgets.forwardButton = makeButton(125, 35, forwardButtonProperties);

    flitWidgets.seekSlider = makeSeekSlider(155, 40, 210, 15);
    flitWidgets.volumeSlider = makeVolumeSlider(385, 40, 110, 15);

    playerWindow->end();
    playerWindow->show(argc, argv);

    return Fl::run();
}

int main(int argc, char** argv) {
    player(argc, argv);
    musicPlayer.freeMusicMemory();

    return 0;
}