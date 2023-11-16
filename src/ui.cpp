#include <memory>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Slider.H>
#include <FL/Fl_Value_Slider.H>

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

Fl_Button* makeButton(const int x, const int y, const char* label) {
// Creates new buttons
    Fl_Button *button = new Fl_Button(x, y, 25, 25, label);
    button->type(FL_NORMAL_BUTTON);

    return button;
}

Fl_Slider* makeSeekSlider(const int x, const int y, const int w, const int h) {
// Creates seek slider
    Fl_Slider *slider = new Fl_Slider(x, y, w, h);
    slider->type(FL_HOR_NICE_SLIDER);
    slider->value(0);

    return slider;
}

Fl_Slider* makeVolumeSlider(const int x, const int y, const int w, const int h) {
// Creates Volume slider
    Fl_Value_Slider *slider = new Fl_Value_Slider(x, y, w, h);
    slider->type(FL_HOR_NICE_SLIDER);
    slider->minimum(0);
    slider->maximum(100);
    slider->value(80);

    return slider;
}

int player(int argc, char** argv) {
    auto playerWindow = std::make_unique<Fl_Window>(500, 300, "Flitwick");

    Fl_Menu_Bar* playerMenu = makeMenuBar();
    
    Fl_Button* stopButton = makeButton(5, 35, "@square");
    Fl_Button* playButton = makeButton(35, 35, "@>");
    Fl_Button* pauseButton = makeButton(65, 35, "@||");
    Fl_Button* backwardButton = makeButton(95, 35, "@<<");
    Fl_Button* forwardButton = makeButton(125, 35, "@>>");

    Fl_Slider* seekSlider = makeSeekSlider(155, 40, 210, 15);
    Fl_Slider* volumeSlider = makeVolumeSlider(385, 40, 110, 15);

    playerWindow->end();
    playerWindow->show(argc, argv);

    return Fl::run();
}

int main(int argc, char** argv) {
    player(argc, argv);

    return 0;
}