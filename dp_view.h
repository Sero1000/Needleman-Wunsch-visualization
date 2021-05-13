#ifndef DP_VIEW_H
#define DP_VIEW_H

#include <QTableView>

class Controller;
class Alignment;

class DP_View : public QTableView
{
public:
    DP_View();

    DP_View(Controller* controller);

protected:
    void keyPressEvent(QKeyEvent* event) override;

private:
    Controller* controller_;
};

#endif // DP_VIEW_H
