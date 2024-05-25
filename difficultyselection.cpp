#include "difficultyselection.h"

DifficultySelection::DifficultySelection(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    easyButton = new QPushButton("Ля ты Улитка", this);
    mediumButton = new QPushButton("Нуууууууууу It's okay", this);
    hardButton = new QPushButton("Не Формула-1, но не плохо", this);
    impossibleButton = new QPushButton("КЧАУУУУУУ", this);

    layout->addWidget(easyButton);
    layout->addWidget(mediumButton);
    layout->addWidget(hardButton);
    layout->addWidget(impossibleButton);

    connect(easyButton, &QPushButton::clicked, [this]() { emit difficultySelected(200); });
    connect(mediumButton, &QPushButton::clicked, [this]() { emit difficultySelected(150); });
    connect(hardButton, &QPushButton::clicked, [this]() { emit difficultySelected(100); });
    connect(impossibleButton, &QPushButton::clicked, [this]() { emit difficultySelected(50); });
}
