#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QKeyEvent>
#include <QTimer>

#include "matrix.h"
#include "mapping.h"
#include "heart.h"
#include "bone.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void drawLifeBar();

    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void paintEvent(QPaintEvent *event) override;
    void attackSlot();
    void hurtAnimationSlot();
    void gameReset();
    void scoreUpdate();

private:
    Ui::Widget *ui;

    // Paint
    QPainter *canvas;

    // // Bone ( Enemy )
    Bone bone;
    QTimer *boneMovement;

    // // Heart ( Player )
    Heart player;
    QTimer *heartInvincibility;
    QTimer *heartHurtAnimationTimer;

    // // Game state
    bool hitBoxToggle = false;
    int score = 0;
    QTimer *scoreTimer;
};
#endif // WIDGET_H
