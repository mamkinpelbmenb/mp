#include <QApplication>
#include <QStackedWidget>
#include "game.h"
#include "mainmenu.h"
#include "difficultyselection.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QStackedWidget stackedWidget;

    MainMenu mainMenu;
    stackedWidget.addWidget(&mainMenu);

    DifficultySelection difficultySelection;
    stackedWidget.addWidget(&difficultySelection);

    Game game;
    stackedWidget.addWidget(&game);

    QObject::connect(&mainMenu, &MainMenu::startGame, [&stackedWidget, &difficultySelection]() {
        stackedWidget.setCurrentWidget(&difficultySelection);
    });

    QObject::connect(&difficultySelection, &DifficultySelection::difficultySelected, [&stackedWidget, &game](int delay) {
        stackedWidget.setCurrentWidget(&game);
        game.restartGame(delay);  // Используем restartGame вместо initGame
    });

    QObject::connect(&game, &Game::gameOverConfirmed, [&stackedWidget, &mainMenu]() {
        stackedWidget.setCurrentWidget(&mainMenu);
    });

    stackedWidget.setCurrentWidget(&mainMenu);
    stackedWidget.resize(Game::getFieldWidth() * Game::DOT_WIDTH, Game::getFieldHeight() * Game::DOT_HEIGHT);
    stackedWidget.show();

    return app.exec();
}
