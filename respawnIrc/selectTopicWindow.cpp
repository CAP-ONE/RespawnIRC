#include "selectTopicWindow.hpp"

selectTopicWindow::selectTopicWindow(QString currentTopic, QWidget* parent) : QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint)
{
    setAttribute(Qt::WA_DeleteOnClose);

    QLabel* labTopic = new QLabel("Topic :", this);
    QPushButton* buttonSelect = new QPushButton("Choisir ce topic", this);
    QPushButton* buttonCancel = new QPushButton("Annuler", this);

    topicLine.setText(currentTopic);

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(buttonSelect);
    buttonLayout->addWidget(buttonCancel);

    QGridLayout* mainLayout = new QGridLayout(this);
    mainLayout->addWidget(labTopic, 0, 0);
    mainLayout->addWidget(&topicLine, 0, 1);
    mainLayout->addLayout(buttonLayout, 1, 0, 1, 2);

    setLayout(mainLayout);
    setWindowTitle("Choisir un topic");
    topicLine.setFocus();

    connect(buttonSelect, SIGNAL(pressed()), this, SLOT(selectThisTopic()));
    connect(buttonCancel, SIGNAL(pressed()), this, SLOT(close()));
}

void selectTopicWindow::selectThisTopic()
{
    emit newTopicSelected(topicLine.text());
    close();
}
