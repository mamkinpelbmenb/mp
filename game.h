#ifndef GAME_H
#define GAME_H

#include <QtGlobal>
#include <QWidget>
#include <QVector>
#include <QPoint>
#include <QKeyEvent>
#include <deque>
#include <QElapsedTimer>

class Game : public QWidget {
    Q_OBJECT

public:
    Game();
    static int getFieldWidth();
    static int getFieldHeight();
    static const int DOT_WIDTH = 20;
    static const int DOT_HEIGHT = 20;

    void initGame(int delay);  // Изменили сигнатуру
    void restartGame(int delay);
    int getScore() const;  // Новый метод для получения количества очков

signals:
    void gameOverConfirmed();  // Новый сигнал

protected:
    void timerEvent(QTimerEvent*) override;
    void keyPressEvent(QKeyEvent*) override;
    void paintEvent(QPaintEvent *event) override;

private:
    static const int FIELD_WIDTH = 20;
    static const int FIELD_HEIGTH = 20;
    int Delay;  // Убрали static

    void doDrawing();
    void localeApple();
    void move();
    void check_field();
    void gameOver();
    void check_apple();

    int m_timerId;
    QPoint m_apple;

    enum Directions {
        left, right, up, down
    };

    Directions m_dir;
    std::deque<Directions> m_dirs;
    bool m_inGame;
    QVector<QPoint> m_dots;

    int m_score;
    QElapsedTimer m_elapsedTimer;

    QPixmap m_head_left;
    QPixmap m_head_right;
    QPixmap m_head_up;
    QPixmap m_head_down;

    QPixmap m_tail_left;
    QPixmap m_tail_right;
    QPixmap m_tail_up;
    QPixmap m_tail_down;

    QPixmap m_background;
};

#endif // GAME_H
