#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    player.initializeHeart();
    bone.initializeBone();

    // Timers
    boneMovement = new QTimer();
    boneMovement->start(100);
    connect(boneMovement, SIGNAL(timeout()), this, SLOT(attackSlot())); // Makes a loop

    heartInvincibility = new QTimer();
    connect(heartInvincibility, SIGNAL(timeout()), heartInvincibility, SLOT(stop())); // makes the timer a singleShot

    heartHurtAnimationTimer = new QTimer();
    connect(heartHurtAnimationTimer, SIGNAL(timeout()), this, SLOT(hurtAnimationSlot())); // Makes a loop

    scoreTimer = new QTimer();
    scoreTimer->start(1000);
    connect(scoreTimer, SIGNAL(timeout()) , this, SLOT(scoreUpdate())); // Update the score each sec
}

Widget::~Widget()
{
    delete ui;
}

void Widget::drawLifeBar()
{
    canvas->fillRect(100, 364, 200, 25, QColor(50, 0, 0)); // Container

    canvas->fillRect(100, 364, player.getHp() * 50, 25, QColor(200, 0, 0)); // Health lvl
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
    case Qt::Key_Up :
        if( !player.isDead() ){
            if(player.getHitBox()->y() > 155){     // Coalition check
                player.move(0, 10);
                update();
            }
        }
        break;

    case Qt::Key_Right:
        if( !player.isDead() ){
            if(player.getHitBox()->x() < 245){     // Coalition check
                player.move(10, 0);
                update();
            }
        }
        break;

    case Qt::Key_Down:
        if( !player.isDead() ){
            if(player.getHitBox()->y() < 305){     // Coalition check
                player.move(0, -10);
                update();
            }
        }
        break;

    case Qt::Key_Left:
        if( !player.isDead() ){
            if(player.getHitBox()->x() > 100){     // Coalition check
                player.move(-10, 0);
                update();
            }
        }
        break;
    }

    switch(event->key()){
    case Qt::Key_Escape:
        QCoreApplication::quit();
        break;
    case Qt::Key_R: // Reset (Only after dying)
        if( player.isDead() )
            gameReset();
        break;
    case Qt::Key_H:
        if( !player.isDead() )
            hitBoxToggle = !hitBoxToggle;
        break;
    }
}

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    canvas = new QPainter(this);
    if( !player.isDead() )
    {
        if(hitBoxToggle){ // draws Hitboxes
            canvas->setPen(QColor(0, 0, 255));
            canvas->drawRect(player.getHitBox()->x(), player.getHitBox()->y(), player.getHitBox()->width(), player.getHitBox()->height());
            canvas->drawRect(bone.getHitBox()->x(), bone.getHitBox()->y(), bone.getHitBox()->width(), bone.getHitBox()->height());
        }

        // Draw movement area
        canvas->setPen(QPen( QColor(255, 255, 255), 4 ));
        canvas->drawRect(100, 150, 200, 200);

        player.draw(canvas);
        bone.draw(canvas);
        drawLifeBar();
    }else{
        player.draw(canvas);

        boneMovement->stop();

        ui->lbl_Enemy->setVisible(false);
        ui->lbl_Health->setVisible(false);
        ui->lbl_HP->setVisible(false);
        ui->lbl_Score->setVisible(false);
        ui->lbl_Guide->setVisible(false);

        canvas->fillRect(this->geometry(), QColor(0,0,0)); // Fill the screen with black

        canvas->setPen(QPen( QColor(255, 255, 255) ));
        canvas->setFont(QFont("Comic Sans MS", 38));
        canvas->drawText(50, 175, "GAME OVER");

        canvas->setFont(QFont("Comic Sans MS", 10));
        canvas->drawText(120, 275, "Your score is " + QString::number(score) + " U SUCK");

        canvas->setFont(QFont("Comic Sans MS", 15));
        canvas->drawText(105, 305, "Press (r) to try again");
    }

    canvas->end();
}

void Widget::attackSlot()
{
    bone.attack();
    bone.damagePlayer(player, heartHurtAnimationTimer, heartInvincibility, scoreTimer);
    ui->lbl_Health->setText(QString::number(player.getHp()));
    update();
}

void Widget::hurtAnimationSlot()
{
    player.hurtAnimation(heartHurtAnimationTimer, heartInvincibility);
    update();
}

void Widget::gameReset()
{
    bone.reset();
    player.reset();

    score = 0;

    ui->lbl_Enemy->setVisible(true);
    ui->lbl_Health->setVisible(true);
    ui->lbl_Health->setText(QString::number(player.getHp()));
    ui->lbl_HP->setVisible(true);
    ui->lbl_Score->setVisible(true);
    ui->lbl_Guide->setVisible(true);
    ui->lbl_Score->setText("score:\n" + QString::number(score));

    boneMovement->start(100);
    scoreTimer->start(1000);

    update();
}

void Widget::scoreUpdate()
{
    score += 100;
    ui->lbl_Score->setText("score:\n" + QString::number(score));
    ui->lbl_Score->setScaledContents(true);
}
