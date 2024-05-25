#include "mainmenu.h"

MainMenu::MainMenu(QWidget *parent) : QWidget(parent) {
    // Создаем заголовок
    titleLabel = new QLabel("The SNAKE", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(32);
    titleLabel->setFont(titleFont);

    // Создаем кнопку начала игры
    startGameButton = new QPushButton("Начать игру", this);
    QFont buttonFont = startGameButton->font();
    buttonFont.setPointSize(16);
    startGameButton->setFont(buttonFont);

    // Создаем компоновку и добавляем элементы
    layout = new QVBoxLayout(this);
    layout->addWidget(titleLabel);
    layout->addStretch();
    layout->addWidget(startGameButton, 0, Qt::AlignCenter);
    layout->addStretch();

    // Подключаем сигнал нажатия кнопки к слоту
    connect(startGameButton, &QPushButton::clicked, this, &MainMenu::onStartGameButtonClicked);
}

void MainMenu::onStartGameButtonClicked() {
    emit startGame();  // Излучаем сигнал начала игры
}
