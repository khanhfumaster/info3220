#include "slidingbrick.h"

void SlidingBrick::advance(int phase) {
    if (phase == 0){
      return;
    }

    if (m_life <= 0) {
        scene()->removeItem(this);
        this->deleteLater();
    }
    else {
        int futureXPos =pos().x() + m_xVelocity;

        if (futureXPos <= 0) {
            futureXPos = 0;
            m_xVelocity *= -1;
        }

        else if (futureXPos + m_width >= scene()->width()) {
            futureXPos = scene()->width() - m_width;
            m_xVelocity *= -1;
        }

        // manage brick collision with other bricks
        QList<QGraphicsItem *> sceneItems = scene()->items();

        for( int i=0; i<sceneItems.count(); ++i ) {

            QGraphicsItem * otherItem = sceneItems[i];

            if (otherItem == this || otherItem->data(1) == "Ball")
                continue;


            qreal otherX = otherItem->pos().x();
            qreal otherY = otherItem->pos().y();
            qreal otherHeight = otherItem->boundingRect().height();
            qreal otherWidth = otherItem->boundingRect().width();

            //check if they might hit (on the same level/row)
            if (this->pos().y() <= otherY + otherHeight && this->pos().y() + m_height > otherY) {
                if (futureXPos + m_width > otherX && futureXPos < otherX) {
                    m_xVelocity *= -1;
                    futureXPos = otherX - m_width;
                }

                else if (futureXPos <= otherX + otherWidth && futureXPos + m_width > otherX + otherWidth) {
                    m_xVelocity *= -1;
                    futureXPos = otherX + otherWidth;
                }
            }
        }

        setPos(futureXPos, pos().y());
    }

}