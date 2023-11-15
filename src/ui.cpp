#include <memory>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>

int player(int argc, char** argv) {
    auto playerWindow = std::make_unique<Fl_Window>(500, 300, "Flitwick");

    playerWindow->end();
    playerWindow->show(argc, argv);

    return Fl::run();
}

int main(int argc, char** argv) {
    player(argc, argv);

    return 0;
}