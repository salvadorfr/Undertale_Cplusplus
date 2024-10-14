#include "bone.h"

Bone::Bone() {}

void Bone::initializeBone()
{
    bone[0][0] = 6;  bone[0][1] = 0; bone[0][2] = 1;
    bone[1][0] = 15; bone[1][1] = 0; bone[1][2] = 1;
    bone[2][0] = 21; bone[2][1] = 12; bone[2][2] = 1;
    bone[3][0] = 63; bone[3][1] = 12; bone[3][2] = 1;
    bone[4][0] = 69; bone[4][1] = 0; bone[4][2] = 1;
    bone[5][0] = 78; bone[5][1] = 0; bone[5][2] = 1;
    bone[6][0] = 84; bone[6][1] = 6; bone[6][2] = 1;
    bone[7][0] = 84; bone[7][1] = 15; bone[7][2] = 1;
    bone[8][0] = 78; bone[8][1] = 21; bone[8][2] = 1;
    bone[9][0] = 84; bone[9][1] = 27; bone[9][2] = 1;
    bone[10][0] = 84; bone[10][1] = 36; bone[10][2] = 1;
    bone[11][0] = 78; bone[11][1] = 42; bone[11][2] = 1;
    bone[12][0] = 69; bone[12][1] = 42; bone[12][2] = 1;
    bone[13][0] = 63; bone[13][1] = 30; bone[13][2] = 1;
    bone[14][0] = 21; bone[14][1] = 30; bone[14][2] = 1;
    bone[15][0] = 15; bone[15][1] = 42; bone[15][2] = 1;
    bone[16][0] = 6; bone[16][1] = 42; bone[16][2] = 1;
    bone[17][0] = 0; bone[17][1] = 36; bone[17][2] = 1;
    bone[18][0] = 0; bone[18][1] = 27; bone[18][2] = 1;
    bone[19][0] = 6; bone[19][1] = 21; bone[19][2] = 1;
    bone[20][0] = 0; bone[20][1] = 15; bone[20][2] = 1;
    bone[21][0] = 0; bone[21][1] = 6; bone[21][2] = 1;
    bone[22][0] = 6; bone[22][1] = 0; bone[22][2] = 1;

    for(int r = 0; r < 23; r++){
        for(int c=0; c < 3; c++){
            boneAux[r][c] = bone[r][c];
        }
    }

    hitBox = new QRect(-168, 152, 84, 42);// Asign the bone his hitbox
}

void Bone::draw(QPainter *canvas)
{
    canvas->setPen(QPen(QColor(255, 255, 255), 3));
    canvas->setRenderHint(QPainter::Antialiasing, true);

    Mapping draw;
    draw.window(0, 0, 200, 200);
    draw.port(0, 0, 200, 200);

    // L in -168 so the bone is hidden two times his size on the left size of the screen
    // and M 192 so it is inside the white square
    int L = -168;
    int M = 192;
    int x1, y1, x2, y2;

    for(int i=0; i<22; i++){
        draw.map(bone[i][0],   bone[i][1],   x1, y1, L, M);
        draw.map(bone[i+1][0], bone[i+1][1], x2, y2, L, M);
        canvas->drawLine(x1, y1, x2, y2);
    }
}

void Bone::attack()
{
    static bool dir = true;
    static int count = 0;

    if(dir){
        // Move the bone 70px 10 times so it goes thru the screen
        move(70, 0);
        count++;

        if(count == 10){
            // Once it hits 700px reset the bone so it goes to his original position
            // generate a random yPosition so it goes in different levels
            // and move the bone 700 x so it is in the other side of the screen and
            // the random value
            reset();
            int yPos = QRandomGenerator64::global()->bounded(158);
            move(700, -yPos);

            // change the dir flag so it enters the other if
            dir = false;
            count = 0;
        }
    }
    if(!dir){
        // Do the same as before but to the other side
        move(-70, 0);
        count++;

        if(count == 10){
            // We do the same but leave it in x position because its already
            // on the left side of the screen
            reset();
            int yPos = QRandomGenerator64::global()->bounded(158);
            move(0, -yPos);

            dir = true;
            count = 0;
        }
    }
}

void Bone::damagePlayer(Heart player, QTimer *hurtAnim, QTimer *invinc, QTimer *scoreTim )
{
    if(hitBox->intersects( *player.getHitBox() )){
        if( !invinc->isActive() && !player.isInvincible()){
            hurtAnim->start(100);
            invinc->start(1000);
        }

        // Rotate the heart upside down once his hp is out
        if(player.getHp() == 0){
            scoreTim->stop();
        }
    }
}

QRect *Bone::getHitBox()
{
    return hitBox;
}

void Bone::reset()
{
    for(int r = 0; r < 23; r++){
        for(int c=0; c < 3; c++){
            bone[r][c] = boneAux[r][c];
        }
    }

    hitBox->setX(-168);
    hitBox->setY(152);
    hitBox->setWidth(84);
    hitBox->setHeight(42);
}

void Bone::move(int x, int y)
{
    Matrix fig, id, figRes;

    fig.initialize(23, 3);
    figRes.initialize(23, 3);

    id.initialize(3,3);

    for(int i = 0; i < fig.rowCount(); i++)
        for(int j = 0; j < fig.columnCount(); j++)
            fig.set(i, j, bone[i][j]);

    figRes.translation(fig, id, x, y);

    for(int r=0; r < figRes.rowCount(); r++)
        for(int c=0; c < figRes.columnCount(); c++)
            bone[r][c] = figRes.get(r, c);

    // Move the hitbox
    hitBox->setY        ( hitBox->y() - y );
    hitBox->setX        ( hitBox->x() + x );
    hitBox->setHeight   ( hitBox->height() - y );
    hitBox->setWidth    ( hitBox->width() + x );
}
