#include "game.h"
#include <QDebug>
#include <QPainter>
#include <QTime>
#include <QRandomGenerator>
#include <QCoreApplication>
#include <QMessageBox>

#include <QDateTime>

Game::Game() {
    this->resize(DOT_WIDTH * FIELD_WIDTH, DOT_WIDTH * FIELD_HEIGTH);
    this->setWindowTitle("Snake game");

}

int Game::getFieldWidth() {
    return FIELD_WIDTH;
}

int Game::getFieldHeight() {
    return FIELD_HEIGTH;
}

void Game::initGame(int delay) {
    Delay = delay;  // Устанавливаем задержку
    m_inGame = true;
    m_dir = right;
    m_score = 0;
    m_elapsedTimer.start();

    m_dots.resize(3);
    m_dirs.clear();
    for (int i = 0; i < m_dots.size(); ++i) {
        m_dots[i].rx() = m_dots.size() - i - 1;
        m_dots[i].ry() = 0;
        m_dirs.push_back(right);
    }

    localeApple();
    m_timerId = startTimer(Delay);

    m_score = 0; // Инициализация счётчика очков
    m_elapsedTimer.start(); // Запуск таймера
}

void Game::timerEvent(QTimerEvent * e)
{
    Q_UNUSED(e);

    if(m_inGame){
        check_apple();
        move();
        check_field();
    }

    this->repaint();
}

void Game::keyPressEvent(QKeyEvent* e)
{
    int key = e->key();
    qDebug()<<key;
    if (key == Qt::Key_Left && m_dir != Directions::right) { m_dir = Directions::left;}
    if (key == Qt::Key_Right && m_dir != Directions::left) { m_dir = Directions::right;}
    if (key == Qt::Key_Up && m_dir != Directions::down)    { m_dir = Directions::up;}
    if (key == Qt::Key_Down && m_dir != Directions::up)    { m_dir = Directions::down;}
}

void Game::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    doDrawing();

}

void Game::doDrawing()
{

    QPainter qp(this);
    QPixmap pixmap1("C:/Users/pavel/Pictures/apple.png");
    QPixmap pixmap3("C:/Users/pavel/Pictures/snake-endup.png");

    QImage straight_h("C:/Users/pavel/Pictures/snake-body1.png");
    QImage straight_v("C:/Users/pavel/Pictures/snake-body2.png");

    QImage turn_ul("C:/Users/pavel/Pictures/snake-ul.png");
    QImage turn_ur("C:/Users/pavel/Pictures/snake-ur.png");
    QImage turn_dl("C:/Users/pavel/Pictures/snake-dl.png");
    QImage turn_dr("C:/Users/pavel/Pictures/snake-dr.png");

    m_head_left = QPixmap("C:/Users/pavel/Pictures/snake-headleft.png");
    m_head_right = QPixmap("C:/Users/pavel/Pictures/snake-headright.png");
    m_head_up = QPixmap("C:/Users/pavel/Pictures/snake-headup.png");
    m_head_down = QPixmap("C:/Users/pavel/Pictures/snake-headdown.png");

    m_tail_left = QPixmap("C:/Users/pavel/Pictures/snake-endleft.png");
    m_tail_right = QPixmap("C:/Users/pavel/Pictures/snake-endright.png");
    m_tail_up = QPixmap("C:/Users/pavel/Pictures/snake-endup.png");
    m_tail_down = QPixmap("C:/Users/pavel/Pictures/snake-enddown.png");

    m_background = QPixmap("C:/Users/pavel/Pictures/grass.png");

    int size = DOT_WIDTH; // или DOT_HEIGHT, если это квадратные сегменты

    QImage scaled_straight_h = straight_h.scaled(size, size);
    QImage scaled_straight_v = straight_v.scaled(size, size);
    QImage scaled_turn_ul = turn_ul.scaled(size, size);
    QImage scaled_turn_ur = turn_ur.scaled(size, size);
    QImage scaled_turn_dl = turn_dl.scaled(size, size);
    QImage scaled_turn_dr = turn_dr.scaled(size, size);


    if (m_inGame){

        qp.drawPixmap(0, 0, width(), height(), m_background);
        qp.setBrush(Qt::red);
        qp.drawPixmap(m_apple.x() * DOT_WIDTH,m_apple.y() * DOT_HEIGHT, DOT_WIDTH,DOT_HEIGHT, pixmap1);

        for (int i = 0; i < m_dots.size(); ++i){
            if (i == 0) {
                // Используем разные изображения для головы в зависимости от направления
                switch (m_dir) {
                case left:
                    qp.drawPixmap(m_dots[i].x() * DOT_WIDTH, m_dots[i].y() * DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT, m_head_left);
                    break;
                case right:
                    qp.drawPixmap(m_dots[i].x() * DOT_WIDTH, m_dots[i].y() * DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT, m_head_right);
                    break;
                case up:
                    qp.drawPixmap(m_dots[i].x() * DOT_WIDTH, m_dots[i].y() * DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT, m_head_up);
                    break;
                case down:
                    qp.drawPixmap(m_dots[i].x() * DOT_WIDTH, m_dots[i].y() * DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT, m_head_down);
                    break;
                }

            } else if (i == m_dots.size() - 1) {
                // Используем разные изображения для хвоста в зависимости от направления
                Directions tail_dir = m_dirs[m_dirs.size() - 1];
                switch (tail_dir) {
                case left:
                    qp.drawPixmap(m_dots[i].x() * DOT_WIDTH, m_dots[i].y() * DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT, m_tail_left);
                    break;
                case right:
                    qp.drawPixmap(m_dots[i].x() * DOT_WIDTH, m_dots[i].y() * DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT, m_tail_right);
                    break;
                case up:
                    qp.drawPixmap(m_dots[i].x() * DOT_WIDTH, m_dots[i].y() * DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT, m_tail_up);
                    break;
                case down:
                    qp.drawPixmap(m_dots[i].x() * DOT_WIDTH, m_dots[i].y() * DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT, m_tail_down);
                    break;
                }
            }else {
                QImage image;


                if (m_dirs[i] == left && m_dirs[i - 1] == up) {
                    image = scaled_turn_ul;
                }else if (m_dirs[i] == right && m_dirs[i - 1] == up) {
                    image = scaled_turn_ur;
                } else if (m_dirs[i] == left && m_dirs[i - 1] == down) {
                    image = scaled_turn_dl;
                } else if (m_dirs[i] == right && m_dirs[i - 1] == down) {
                    image = scaled_turn_dr;
                } else if (m_dirs[i] == up && m_dirs[i - 1] == left) {
                    image = scaled_turn_dr;
                } else if (m_dirs[i] == up && m_dirs[i - 1] == right) {
                    image = scaled_turn_dl;
                } else if (m_dirs[i] == down && m_dirs[i - 1] == left) {
                    image = scaled_turn_ur;
                } else if (m_dirs[i] == down && m_dirs[i - 1] == right) {
                    image = scaled_turn_ul;
                } else if (m_dirs[i] == left || m_dirs[i] == right) {
                    image = scaled_straight_h;
                } else if (m_dirs[i] == up || m_dirs[i] == down) {
                    image = scaled_straight_v;
                }

                qp.drawImage(m_dots[i].x() * DOT_WIDTH, m_dots[i].y() * DOT_HEIGHT, image);
            }
        }
        // Отображение очков и времени
        QFont font("Arial", 12);
        qp.setFont(font);
        qp.setPen(Qt::black);
        qp.drawText(10, 20, QString("Score: %1").arg(m_score));

        QString scoreText = QString("Score: %1").arg(m_score);
        qp.drawText(10, 20, scoreText);


    } else {
        //gameOver();
    }
}

void Game::localeApple()
{

    QTime time = QTime::currentTime();
    qsrand((uint) time.msec());

    m_apple.ry()= qrand()% DOT_HEIGHT;
    m_apple.rx()= qrand()% DOT_WIDTH;

    qDebug() << "Apple"<< m_apple;
}

void Game::move() {

    m_dirs.push_front(m_dir);
    if (m_dirs.size() > m_dots.size()) {
        m_dirs.pop_back();
    }

    for (int i = m_dots.size() - 1; i > 0; --i) {
        m_dots[i] = m_dots[i - 1];
    }

    switch (m_dir) {
    case left: { m_dots[0].rx() -= 1; break; }
    case right: { m_dots[0].rx() += 1; break; }
    case up: { m_dots[0].ry() -= 1; break; }
    case down: { m_dots[0].ry() += 1; break; }
    default: break;
    }
}

void Game::check_field() {
    if (m_dots.size() > 4){
        for (int i = 1; i < m_dots.size(); ++i){
            if (m_dots[0] == m_dots[i]){
                m_inGame = false;
            }
        }
    }
    if(m_dots[0].x() >= FIELD_WIDTH) { m_inGame = false; }
    if(m_dots[0].x() < 0) { m_inGame = false; }
    if(m_dots[0].y() >= FIELD_HEIGTH) { m_inGame = false; }
    if(m_dots[0].y() < 0) { m_inGame = false; }

    if(!m_inGame) {
        killTimer(m_timerId);
        gameOver();
    }
}

void Game::gameOver()
{
    QMessageBox msgb;
    msgb.setText("Game Over\nScore: " + QString::number(m_score));
    connect(&msgb, &QMessageBox::finished, this, &Game::restartGame);
    msgb.exec();

    emit gameOverConfirmed();  // Отправка сигнала после закрытия сообщения

}

void Game::check_apple() {
    if (m_apple == m_dots[0]){
        m_dots.push_back(QPoint());
        m_dirs.push_back(m_dirs.back());
        m_score++; // Увеличиваем счётчик очков
        localeApple();
    }
}

void Game::restartGame(int delay)
{
    m_dots.clear();
    m_dirs.clear();
    killTimer(m_timerId);
    initGame(delay);
}

int Game::getScore() const
{
    return m_score;
}


