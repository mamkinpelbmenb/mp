#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

class MainMenu : public QWidget {
    Q_OBJECT

public:
    MainMenu(QWidget *parent = nullptr);

signals:
    void startGame();  // Сигнал для начала игры

private slots:
    void onStartGameButtonClicked();  // Слот для обработки нажатия кнопки

private:
    QPushButton *startGameButton;
    QLabel *titleLabel;
    QVBoxLayout *layout;
};

#endif // MAINMENU_H
