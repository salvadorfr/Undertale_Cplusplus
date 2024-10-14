#ifndef BONE_H
#define BONE_H

#include <QRect>
#include <QPainter>
#include <QRandomGenerator64>
#include <QTimer>

#include "mapping.h"
#include "matrix.h"
#include "heart.h"

class Bone
{
public:
    Bone();
    void initializeBone();
    void draw(QPainter *);
    void attack();
    void damagePlayer(Heart player, QTimer *hurtAnim, QTimer *invinc, QTimer *scoreTim);

    QRect* getHitBox();

    void reset();

    void move(int x, int y);


private:
    float bone[23][3];
    float boneAux[23][3];
    QRect *hitBox;
};

#endif // BONE_H
