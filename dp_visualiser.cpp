#include <QTableView>
#include <QHeaderView>
#include <QKeyEvent>
#include <QDockWidget>
#include <QListView>
#include <QItemSelectionModel>
#include <QVBoxLayout>
#include <QTextEdit>

#include "dp_view.h"
#include "dp_visualiser.h"
#include "dp_table.h"
#include "controller.h"
#include "alignmentmodel.h"

#include "./ui_dp_visualiser.h"

#include <QPushButton>

DP_Visualiser::DP_Visualiser(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DP_Visualiser), tableModel_(nullptr)
{
    QVBoxLayout* vertLayout = new QVBoxLayout();
    QWidget* centralWidget = new QWidget();
    centralWidget->setLayout(vertLayout);
    textEdit_ = new QTextEdit();
    textEdit_->setReadOnly(true);

    AlignmentModel* alignmentModel = new AlignmentModel();
    controller_ = new Controller(alignmentModel);

    tableView_ = new DP_View(controller_);

    setCentralWidget(centralWidget);
    vertLayout->addWidget(tableView_);
    vertLayout->addWidget(textEdit_);

    QDockWidget* dockWidget = new QDockWidget();
    alignmentView_ = new QListView();
    alignmentView_->setModel(alignmentModel);

    dockWidget->setWidget(alignmentView_);

    addDockWidget(Qt::RightDockWidgetArea,dockWidget);
    setupInputWidget();

    QItemSelectionModel* selectionModel = alignmentView_->selectionModel();

    connect(selectionModel, &QItemSelectionModel::currentChanged,this,&DP_Visualiser::onAlignmentSelected);
    connect(controller_,&Controller::stepFinished,this,&DP_Visualiser::log);
}

DP_Visualiser::~DP_Visualiser()
{
    delete ui;
}

void DP_Visualiser::onAlignmentSelected(const QModelIndex& current, const QModelIndex& prev)
{
    Alignment* alignment = reinterpret_cast<Alignment*>(current.internalPointer());
    QString alignmentName = current.data().toString();

    QString showStr;
    QString st1 = alignment->st1();
    QString st2 = alignment->st2();

    for(auto iter = st1.rbegin(); iter != st1.rend();++iter){
        showStr.append(*iter + ' ');
    }

    showStr.append("\n\n");

    for(auto iter = st2.rbegin(); iter != st2.rend();++iter){
        showStr.append(*iter + ' ');
    }

    textEdit_->clear();
    textEdit_->insertPlainText(showStr);

    textEdit_->insertPlainText("\n\n");
    textEdit_->insertPlainText(QString("The Score of %1 is %2").arg(alignmentName).arg(alignment->score()));

    highlightTraceback(*alignment);
}

void DP_Visualiser::setupInputWidget(){
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QFrame *frame;
    QFormLayout *formLayout_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;

    QPushButton* pushButton = new QPushButton("Start Alignment Algo.");

    connect(pushButton, &QPushButton::clicked,this,&DP_Visualiser::start);
    QDockWidget* dockWidget = new QDockWidget();

    widget = new QWidget();

    dockWidget->setWidget(widget);

    verticalLayout = new QVBoxLayout(widget);
    formLayout = new QFormLayout();

    label_4 = new QLabel("Seq 1 : ", widget);
    formLayout->setWidget(0,QFormLayout::LabelRole, label_4);

    seqOneEdit_ = new QLineEdit(widget);
    formLayout->setWidget(0, QFormLayout::FieldRole, seqOneEdit_);

    label_5 = new QLabel("Seq 2 :", widget);
    formLayout->setWidget(1, QFormLayout::LabelRole, label_5);

    seqTwoEdit_ = new QLineEdit(widget);
    formLayout->setWidget(1, QFormLayout::FieldRole, seqTwoEdit_);

    formLayout->addWidget(pushButton);

    verticalLayout->addLayout(formLayout);

    frame = new QFrame(widget);
    frame->setFrameShape(QFrame::HLine);
    frame->setFrameShadow(QFrame::Sunken);

    verticalLayout->addWidget(frame);

    formLayout_2 = new QFormLayout();

    label = new QLabel("Gap Score : ",widget);
    formLayout_2->setWidget(0, QFormLayout::LabelRole, label);

    gapScoreSpinBox_ = new QSpinBox(widget);
    gapScoreSpinBox_->setMinimum(-1000);
    gapScoreSpinBox_->setValue(-2);
    formLayout_2->setWidget(0, QFormLayout::FieldRole, gapScoreSpinBox_);

    label_2 = new QLabel("Match Score : ", widget);
    formLayout_2->setWidget(1, QFormLayout::LabelRole, label_2);

    matchScoreSpinBox_ = new QSpinBox(widget);
    matchScoreSpinBox_->setMinimum(-1000);
    matchScoreSpinBox_->setValue(1);
    formLayout_2->setWidget(1, QFormLayout::FieldRole, matchScoreSpinBox_);

    label_3 = new QLabel("Mismatch Score : ", widget);
    formLayout_2->setWidget(2, QFormLayout::LabelRole, label_3);

    mismatchScoreSpinBox_ = new QSpinBox(widget);
    mismatchScoreSpinBox_->setMinimum(-1000);
    mismatchScoreSpinBox_->setValue(-1);
    formLayout_2->setWidget(2, QFormLayout::FieldRole, mismatchScoreSpinBox_);

    connect(gapScoreSpinBox_,qOverload<int>(&QSpinBox::valueChanged),controller_,&Controller::setGapScore);
    connect(matchScoreSpinBox_,qOverload<int>(&QSpinBox::valueChanged), controller_, &Controller::setGapScore);
    connect(mismatchScoreSpinBox_,qOverload<int>(&QSpinBox::valueChanged), controller_, &Controller::setMismatchScore);

    connect(pushButton,&QPushButton::clicked,this , &DP_Visualiser::start);
    verticalLayout->addLayout(formLayout_2);

    addDockWidget(Qt::LeftDockWidgetArea, dockWidget);
}

void DP_Visualiser::start(){
    QString sequence1 = seqOneEdit_->text();
    QString sequence2 = seqTwoEdit_->text();

    tableModel_ = new DP_Table(sequence1, sequence2);

    tableView_->setModel(tableModel_);
    controller_->setDPTable(tableModel_);
}

void DP_Visualiser::highlightTraceback(const Alignment& alignment){
    QItemSelection traceBackSelection = tableModel_->getTraceBackSelection(alignment);

    tableView_->selectionModel()->clearSelection();
    tableView_->selectionModel()->select(traceBackSelection, QItemSelectionModel::Select);
}

void DP_Visualiser::log(const QString& text){
    textEdit_->clear();
    textEdit_->setText(text);
}

void DP_Visualiser::keyPressEvent(QKeyEvent* event) {
    switch(event->key())
    {
        case Qt::Key_Right:{
            controller_->iter();
            return;
        }
    }

    QMainWindow::keyPressEvent(event);
}
