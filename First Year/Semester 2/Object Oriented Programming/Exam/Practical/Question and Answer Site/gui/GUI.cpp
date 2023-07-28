#include <QMessageBox>
#include <QFormLayout>
#include "GUI.h"

GUI::GUI(Service &service, User& user): service{service}, user{user} {
    this->allLayout = new QVBoxLayout{this};
    this->questionsListWidget = new QListWidget{};
    this->answersListWidget = new QListWidget{};
    this->votesSpinBox = new QSpinBox{};
    this->addQuestionButton = new QPushButton("Add question");
    this->addAnswerPushButton = new QPushButton("Add answer");
    this->lineEdit = new QLineEdit{};
    this->initGUI();
    this->populateList();
    this->connectSignalsAndSlots();
}

void GUI::initGUI() {
    auto listsLayout = new QHBoxLayout{};
    listsLayout->addWidget(this->questionsListWidget);
    listsLayout->addWidget(this->answersListWidget);
    this->allLayout->addLayout(listsLayout);

    auto editLayout = new QFormLayout{};
    editLayout->addRow("Text:", this->lineEdit);
    this->allLayout->addLayout(editLayout);
    this->allLayout->addWidget(this->addQuestionButton);
    this->allLayout->addWidget(this->addAnswerPushButton);
    this->allLayout->addWidget(this->votesSpinBox);
}

void GUI::populateList() {
    this->questionsListWidget->clear();
    std::vector<Question> allQuestions = this->service.getAllQuestions();
    for (auto question: allQuestions) {
        auto* item = new QListWidgetItem(QString::fromStdString(question.getDescription()));
        this->questionsListWidget->addItem(item);
    }
}

void GUI::populateAnswerList() {
    this->answersListWidget->clear();
    int selectedIndex = this->getSelectedIndex();
    std::vector<Answer> answers = this->service.getAnswers(this->service.getAllQuestions()[selectedIndex].getId());
    for (auto answer: answers) {
        auto item = new QListWidgetItem(QString::fromStdString(std::to_string(answer.getId()) +" - " + answer.getAnswer() + " - " + std::to_string(answer.getNumberVotes())));
        if (answer.getName() == user.getName()) item->setBackground(Qt::yellow);
        this->answersListWidget->addItem(item);
    }
}

void GUI::spinBox() {
    int selectedIndex = this->getSelectedIndexAnswers();
    int selected = this->getSelectedIndex();
    this->votesSpinBox->setEnabled(true);
    if (selectedIndex != -1) {
        std::vector<Answer> answers = this->service.getAnswers(this->service.getAllQuestions()[selected].getId());
        if (answers[selectedIndex].getName() == this->user.getName())
            this->votesSpinBox->setEnabled(false);
        else {
            this->votesSpinBox->setValue(answers[selectedIndex].getNumberVotes());
            this->votesSpinBox->setRange(answers[selectedIndex].getNumberVotes() - 1, answers[selectedIndex].getNumberVotes() + 1);
        }
    }
}

void GUI::connectSignalsAndSlots() {
    QObject::connect(this->addQuestionButton, &QPushButton::clicked, this, &GUI::addQuestion);
    QObject::connect(this->addAnswerPushButton, &QPushButton::clicked, this, &GUI::addAnswer);
    QObject::connect(this->questionsListWidget, &QListWidget::itemClicked, this, &GUI::populateAnswerList);
    QObject::connect(this->answersListWidget, &QListWidget::itemClicked, this, &GUI::spinBox);
    QObject::connect(this->votesSpinBox, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &GUI::changeVotes);
}

void GUI::update() {
    this->populateList();
    this->populateAnswerList();
}

void GUI::addQuestion() {
    std::string title = this->lineEdit->text().toStdString();
    if (title.empty()) {
        QMessageBox::critical(this, "Error", "Invalid question!");
        return;
    }
    this->service.addQuestion(title, this->user.getName());
}

void GUI::addAnswer() {
    int selectedIndex = this->getSelectedIndex();
    std::string title = this->lineEdit->text().toStdString();
    if (title.empty()){
        QMessageBox::critical(this, "Error", "Invalid answer!");
        return;
    }
    this->service.addAnswer(this->service.getAllQuestions()[selectedIndex].getId(), this->user.getName(), title, 0);
}

void GUI::changeVotes() {
    int selectedIndex = this->getSelectedIndexAnswers();
    int selected = this->getSelectedIndex();
    std::vector<Answer> answers = this->service.getAnswers(this->service.getAllQuestions()[selected].getId());
    int votes = this->votesSpinBox->value();
    answers[selectedIndex].setNumberVotes(votes);
    this->service.updateAnswer(answers[selectedIndex]);
}

int GUI::getSelectedIndex() const {
    QModelIndexList selectedIndices = this->questionsListWidget->selectionModel()->selectedIndexes();
    if (selectedIndices.empty())
        return -1;
    int selectedIndex = selectedIndices.at(0).row();
    return selectedIndex;
}

int GUI::getSelectedIndexAnswers() const {
    QModelIndexList selectedIndices = this->answersListWidget->selectionModel()->selectedIndexes();
    if (selectedIndices.empty())
        return -1;
    int selectedIndex = selectedIndices.at(0).row();
    return selectedIndex;
}


Search::Search(Service &service): service{service} {
    this->lineEdit = new QLineEdit{};
    this->matchingTreeWidget = new QTreeWidget{};
    this->connectSignalsAndSlots();
    auto layout = new QVBoxLayout{this};
    layout->addWidget(this->matchingTreeWidget);
    layout->addWidget(this->lineEdit);
}

void Search::connectSignalsAndSlots() {
    QObject::connect(this->lineEdit, &QLineEdit::textChanged, this, &Search::filterList);
}

void Search::filterList() {
    this->matchingTreeWidget->clear();
    this->matchingTreeWidget->setColumnCount(1);
    std::string filter = this->lineEdit->text().toStdString();
    std::vector<std::string> answers = this->service.getAllAnswers(filter);
    auto treeItem = new QTreeWidgetItem(this->matchingTreeWidget);
    if (!answers.empty()) {
        treeItem->setText(0, QString::fromStdString(answers[0]));
        for (int index = 1; index < answers.size(); index++) {
            auto treeChild = new QTreeWidgetItem();
            treeChild->setText(0, QString::fromStdString(answers[index]));
            treeItem->addChild(treeChild);
        }
    }
}

void Search::update() {
    this->filterList();
}
