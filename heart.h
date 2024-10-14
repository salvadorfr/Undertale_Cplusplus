#ifndef HEART_H
#define HEART_H

#include <QRect>
#include <QPainter>
#include <QTimer>

#include "mapping.h"
#include "matrix.h"

class Heart
{
public:
    Heart();

    void initializeHeart();

    void kill();
    void draw(QPainter *);
    void move(int x, int y);
    void rotate(double, double, double);
    void reset();
    void setInvincibility(bool);
    void makeDamage(int);
    void hurtAnimation(QTimer *, QTimer *);

    QRect* getHitBox();
    int getHp();

    bool isDead();
    bool isInvincible();

private:

    float heart[37][3];
    float heartAux[37][3];

    int hp = 4;
    int hurtAnimCount = 4;

    bool playerDead = false;
    bool invincible = false;

    QTimer *invincibilityTimer;

    QRect *hitBox;
};

#endif // HEART_H
