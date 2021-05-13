#include <QKeyEvent>

#include "controller.h"
#include "dp_view.h"

DP_View::DP_View()
{

}

DP_View::DP_View(Controller* controller) : QTableView() , controller_(controller){

}

void DP_View::keyPressEvent(QKeyEvent* event) {
    switch(event->key())
    {
        case Qt::Key_Right:{
            controller_->iter();
            return;
        }
    }

    QTableView::keyPressEvent(event);
}
