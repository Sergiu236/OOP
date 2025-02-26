#include <QApplication>
#include <QPushButton>
#include "repository.h"
#include "window.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Repository repo;

    // Create windows for each doctor
    std::vector<Window*> doctorWindows;
    for (const auto& doctor : repo.getDoctors()) {
        Window* window = new Window(repo, doctor);
        window->show();
        //doctorWindows.push_back(window);
    }

    // Connect the aboutToQuit signal to save data before the application closes
    QObject::connect(&app, &QCoreApplication::aboutToQuit, [&repo]() {
        repo.savePatientsToFile();
    });

    return app.exec();
}