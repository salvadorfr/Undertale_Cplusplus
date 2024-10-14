#include "heart.h"

Heart::Heart() {}

void Heart::initializeHeart()
{
    // HEART COORDINATES ------------------------------------------------------------
    // x                // y                // z
    heart [0][0]  = 18; heart [0][1]  = 0;  heart [0][2]  = 1;
    heart [1][0]  = 30; heart [1][1]  = 0;  heart [1][2]  = 1;
    heart [2][0]  = 30; heart [2][1]  = 6;  heart [2][2]  = 1;
    heart [3][0]  = 36; heart [3][1]  = 6;  heart [3][2]  = 1;
    heart [4][0]  = 36; heart [4][1]  = 12; heart [4][2]  = 1;
    heart [5][0]  = 42; heart [5][1]  = 12; heart [5][2]  = 1;
    heart [6][0]  = 42; heart [6][1]  = 18; heart [6][2]  = 1;
    heart [7][0]  = 48; heart [7][1]  = 18; heart [7][2]  = 1;
    heart [8][0]  = 48; heart [8][1]  = 36; heart [8][2]  = 1;
    heart [9][0]  = 45; heart [9][1]  = 36; heart [9][2]  = 1;
    heart [10][0] = 45; heart [10][1] = 39; heart [10][2] = 1;
    heart [11][0] = 42; heart [11][1] = 39; heart [11][2] = 1;
    heart [12][0] = 42; heart [12][1] = 42; heart [12][2] = 1;
    heart [13][0] = 36; heart [13][1] = 42; heart [13][2] = 1;
    heart [14][0] = 36; heart [14][1] = 39; heart [14][2] = 1;
    heart [15][0] = 30; heart [15][1] = 39; heart [15][2] = 1;
    heart [16][0] = 30; heart [16][1] = 36; heart [16][2] = 1;
    heart [17][0] = 27; heart [17][1] = 36; heart [17][2] = 1;
    heart [18][0] = 27; heart [18][1] = 30; heart [18][2] = 1;
    heart [19][0] = 21; heart [19][1] = 30; heart [19][2] = 1;
    heart [20][0] = 21; heart [20][1] = 36; heart [20][2] = 1;
    heart [21][0] = 18; heart [21][1] = 36; heart [21][2] = 1;
    heart [22][0] = 18; heart [22][1] = 39; heart [22][2] = 1;
    heart [23][0] = 12; heart [23][1] = 39; heart [23][2] = 1;
    heart [24][0] = 12; heart [24][1] = 42; heart [24][2] = 1;
    heart [25][0] = 6;  heart [25][1] = 42; heart [25][2] = 1;
    heart [26][0] = 6;  heart [26][1] = 39; heart [26][2] = 1;
    heart [27][0] = 3;  heart [27][1] = 39; heart [27][2] = 1;
    heart [28][0] = 3;  heart [28][1] = 36; heart [28][2] = 1;
    heart [29][0] = 0;  heart [29][1] = 36; heart [29][2] = 1;
    heart [30][0] = 0;  heart [30][1] = 18; heart [30][2] = 1;
    heart [31][0] = 6;  heart [31][1] = 18; heart [31][2] = 1;
    heart [32][0] = 6;  heart [32][1] = 12; heart [32][2] = 1;
    heart [33][0] = 12; heart [33][1] = 12; heart [33][2] = 1;
    heart [34][0] = 12; heart [34][1] = 6;  heart [34][2] = 1;
    heart [35][0] = 18; heart [35][1] = 6;  heart [35][2] = 1;
    heart [36][0] = 18; heart [36][1] = 0;  heart [36][2] = 1;

    for(int r = 0; r < 37; r++){
        for(int c=0; c < 3; c++){
            heartAux[r][c] = heart[r][c];
        }
    }

    hitBox = new QRect(180, 225, 48, 42); // Asign the heart his hitbox
}

bool Heart::isDead()
{
    return playerDead;
}

bool Heart::isInvincible()
{
    return invincible;
}

void Heart::setInvincibility(bool value)
{
    invincible = value;
}

void Heart::makeDamage(int quan)
{
    hp -= quan;
}

void Heart::hurtAnimation(QTimer *hurtAnimTimer, QTimer *invinci)
{
    switch(hurtAnimCount){
    case 0:
        move(1, 0);
        break;
    case 1:
        move(-2, 0);
        break;
    case 2:
        move(2, 0);
        break;
    case 3:
        move(-1,0);

        setInvincibility( false );
        invinci->stop();

        hurtAnimTimer->stop();
        break;
    case 4:
        hurtAnimCount = -1;

        makeDamage(1);

        setInvincibility( true );
        invinci->start(1000);

        if(getHp() == 0)
        {
            reset();
            kill();
            rotate(180, 21, 24);
            move(0, 20);
            return;
        }
        break;
    }

    hurtAnimCount++;
}

void Heart::kill()
{
    playerDead = true;
}

void Heart::draw(QPainter *canvas)
{
    // Heart states
    if(isDead())
        canvas->setPen(QPen(QColor(0, 0, 255), 3)); // Dead
    else if(isInvincible())
        canvas->setPen(QPen(QColor(150, 0, 0), 3)); // No damage
    else
        canvas->setPen(QPen(QColor(255, 0, 0), 3)); // Normal

    canvas->setRenderHint(QPainter::Antialiasing, true);

    Mapping draw;
    draw.window(0, 0, 200, 200);
    draw.port(0, 0, 200, 200);

    // L and M is the coordinates of the center of the white square
    // but L minus half the figure and
    // M minus half the figure so it can be centered
    int L = 180;
    int M = 267;
    int x1, y1, x2, y2;

    for(int i=0; i<36; i++){
        draw.map(heart[i][0],   heart[i][1],   x1, y1, L, M);
        draw.map(heart[i+1][0], heart[i+1][1], x2, y2, L, M);
        canvas->drawLine(x1, y1, x2, y2);
    }
}

void Heart::move(int x, int y)
{
    Matrix fig, id, figRes;

    fig.initialize(37, 3);
    figRes.initialize(37, 3);

    id.initialize(3,3);

    for(int i = 0; i < fig.rowCount(); i++)
        for(int j = 0; j < fig.columnCount(); j++)
            fig.set(i, j, heart[i][j]);

    figRes.translation(fig, id, x, y);

    for(int r=0; r < figRes.rowCount(); r++)
        for(int c=0; c < figRes.columnCount(); c++)
            heart[r][c] = figRes.get(r, c);

    // Move the hitbox
    hitBox->setY        ( hitBox->y() - y );
    hitBox->setX        ( hitBox->x() + x );
    hitBox->setHeight   ( hitBox->height() - y );
    hitBox->setWidth    ( hitBox->width() + x );
}

void Heart::rotate(double angle, double x, double y)
{
    Matrix fig, id, figRes;

    fig.initialize(37, 3);
    figRes.initialize(37, 3);

    id.initialize(3,3);

    for(int i = 0; i < fig.rowCount(); i++)
        for(int j = 0; j < fig.columnCount(); j++)
            fig.set(i, j, heart[i][j]);

    figRes.fixedRotation(fig, id, angle, x, y);

    for(int r=0; r < figRes.rowCount(); r++)
        for(int c=0; c < figRes.columnCount(); c++)
            heart[r][c] = figRes.get(r, c);
}

void Heart::reset()
{
    for(int r = 0; r < 37; r++){
        for(int c=0; c < 3; c++){
            heart[r][c] = heartAux[r][c];
        }
    }

    hitBox->setX(180);
    hitBox->setY(225);
    hitBox->setWidth(48);
    hitBox->setHeight(42);

    hp = 4;
    playerDead = false;
}

QRect* Heart::getHitBox()
{
    return hitBox;
}

int Heart::getHp()
{
    return hp;
}
