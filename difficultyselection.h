#ifndef DIFFICULTYSELECTION_H
#define DIFFICULTYSELECTION_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class DifficultySelection : public QWidget {
    Q_OBJECT

public:
    DifficultySelection(QWidget *parent = nullptr);

signals:
    void difficultySelected(int delay);

private:
    QPushButton *easyButton;
    QPushButton *mediumButton;
    QPushButton *hardButton;
    QPushButton *impossibleButton;
};

#endif // DIFFICULTYSELECTION_H
