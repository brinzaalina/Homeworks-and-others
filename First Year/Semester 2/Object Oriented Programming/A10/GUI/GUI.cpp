//
// Created by selen on 04/05/2021.
//

#include <QVBoxLayout>
#include <QFormLayout>
#include <QErrorMessage>
#include <QMessageBox>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include "GUI.h"
#include "picturedelegate.h"

DogTableModel::DogTableModel(UserRepository* newRepository){
    this->repository = newRepository;
}

int DogTableModel::rowCount(const QModelIndex &parent) const {
    return this->repository->getNrElems();
}

int DogTableModel::columnCount(const QModelIndex &parent) const {
    return 5;
}

QVariant DogTableModel::data(const QModelIndex &index, int role) const {
    int row = index.row();
    Dog currentDog = this->repository->getAllUserRepo()[row];
    int column = index.column();
    if (role == Qt::DisplayRole || role == Qt::EditRole){
        switch (column) {
            case 0:
                return QString::fromStdString(currentDog.breedGetter());
            case 1:
                return QString::fromStdString(currentDog.nameGetter());
            case 2:
                return QString::fromStdString(std::to_string(currentDog.ageGetter()));
            case 3:
                return QString::fromStdString(currentDog.photoGetter());
            case 4:
                return QString::fromStdString(currentDog.breedGetter());
            default:
                break;
        }
    }
    return QVariant();
}

QVariant DogTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            switch (section) {
                case 0:
                    return QString("Breed");
                case 1:
                    return QString("Name");
                case 2:
                    return QString("Age");
                case 3:
                    return QString("Photo link");
                case 4:
                    return QString("Dog photo");
                default:
                    break;
            }
        }
    }
    return QVariant();
}

void DogTableModel::update() {
    QModelIndex topLeft = this->index(1,1);
    QModelIndex bottomRight = this->index(this->rowCount(), this->columnCount());
    emit layoutChanged();
    emit dataChanged(topLeft, bottomRight);
}

GUI::GUI(Service& serv, UserService& userserv, DogValidator& validator1,Repository& repository): service{serv}, userService{userserv}, validator{validator1}, repository{repository}{
    this->titleWidget = new QLabel(this);
    this->adminButton = new QPushButton(this);
    this->userButton = new QPushButton(this);
    this->initGUI();
    this->connectSignalsAndSlots();
}

void GUI::initGUI() {
    auto* layout = new QVBoxLayout(this);
    QFont titleFont = this->titleWidget->font();
    this->titleWidget->setText("<p style='text-align:center'><font color=#4D2D52>Welcome to the Dog Shelter App! <br> Select your mode!</font></p>");
    titleFont.setItalic(true);
    titleFont.setPointSize(10);
    titleFont.setStyleHint(QFont::System);
    titleFont.setWeight(63);
    this->titleWidget->setFont(titleFont);
    layout->addWidget(this->titleWidget);
    this->adminButton->setText("Admin mode");
    layout->addWidget(this->adminButton);
    this->userButton->setText("User mode");
    layout->addWidget(this->userButton);
    this->setLayout(layout);
    this->setStyleSheet("background-color:#D9DBF1");
}

GUI::~GUI() = default;

void GUI::connectSignalsAndSlots() {
    QObject::connect(this->adminButton, &QPushButton::clicked, this, &GUI::showAdmin);
    QObject::connect(this->userButton, &QPushButton::clicked, this, &GUI::showUser);
}

void GUI::showAdmin() {
    this->service.clearUndoRedo();
    auto* admin = new AdminGUI(this, this->service, this->validator, this->repository);
    admin->show();
}

AdminGUI::AdminGUI(QWidget* parent, Service &serv, DogValidator& validator1, Repository& repo): service{serv}, validator{validator1}, repository{repo}{
    this->titleWidget = new QLabel(this);
    this->dogsListWidget = new QListWidget{};
    this->nameLineEdit = new QLineEdit{};
    this->breedLineEdit = new QLineEdit{};
    this->ageLineEdit = new QLineEdit{};
    this->linkLineEdit = new QLineEdit{};
    this->addButton = new QPushButton("Add");
    this->deleteButton = new QPushButton("Delete");
    this->updateButton = new QPushButton("Update");
    this->chartButton = new QPushButton("Display chart");
    this->undoButton = new QPushButton("Undo");
    this->redoButton = new QPushButton("Redo");
    this->shortcutUndo = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z), this);
    this->shortcutRedo = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y), this);
    setParent(parent);
    setWindowFlag(Qt::Window);
    this->initAdminGUI();
    this->populateList();
    this->connectSignalsAndSlots();
    
}

void AdminGUI::initAdminGUI() {
    auto* layout = new QVBoxLayout(this);
    QFont titleFont = this->titleWidget->font();
    this->titleWidget->setText("<p style='text-align:center'><font color=#4D2D52>ADMIN MODE</font></p>");
    titleFont.setItalic(true);
    titleFont.setPointSize(10);
    titleFont.setStyleHint(QFont::System);
    titleFont.setWeight(63);
    this->titleWidget->setFont(titleFont);
    layout->addWidget(this->titleWidget);

    layout->addWidget(this->dogsListWidget);

    auto * dogDetailsLayout = new QFormLayout{};
    dogDetailsLayout->addRow("Name", this->nameLineEdit);
    dogDetailsLayout->addRow("Breed", this->breedLineEdit);
    dogDetailsLayout->addRow("Age", this->ageLineEdit);
    dogDetailsLayout->addRow("Link", this->linkLineEdit);
    layout->addLayout(dogDetailsLayout);

    auto* buttonsLayout = new QGridLayout{};
    buttonsLayout->addWidget(this->addButton, 0, 0);
    buttonsLayout->addWidget(this->deleteButton, 0, 1);
    buttonsLayout->addWidget(this->updateButton, 1, 0);
    buttonsLayout->addWidget(this->chartButton, 1, 1);
    buttonsLayout->addWidget(this->undoButton, 2, 0);
    buttonsLayout->addWidget(this->redoButton, 2, 1);
    layout->addLayout(buttonsLayout);
}

void AdminGUI::populateList() {
    this->dogsListWidget->clear();
    std::vector<Dog> allDogs = this->service.getAllService();
    for (Dog& dog: allDogs)
        this->dogsListWidget->addItem(QString::fromStdString(dog.nameGetter()));
}

void AdminGUI::connectSignalsAndSlots() {
    QObject::connect(this->dogsListWidget, &QListWidget::itemSelectionChanged, [this]() {
        int selectedIndex = this->getSelectedIndex();
        if (selectedIndex < 0)
            return ;
        Dog dog = this->service.getAllService()[selectedIndex];
        this->nameLineEdit->setText(QString::fromStdString(dog.nameGetter()));
        this->breedLineEdit->setText(QString::fromStdString(dog.breedGetter()));
        this->ageLineEdit->setText(QString::fromStdString(std::to_string(dog.ageGetter())));
        this->linkLineEdit->setText(QString::fromStdString(dog.photoGetter()));
    });

    QObject::connect(this->shortcutUndo, &QShortcut::activated, this, &AdminGUI::undoGUI);
    QObject::connect(this->shortcutRedo, &QShortcut::activated, this, &AdminGUI::redoGUI);

    QObject::connect(this->addButton, &QPushButton::clicked, this, &AdminGUI::addDog);
    QObject::connect(this->deleteButton, &QPushButton::clicked, this, &AdminGUI::deleteDog);
    QObject::connect(this->updateButton, &QPushButton::clicked, this, &AdminGUI::updateDog);
    QObject::connect(this->chartButton, &QPushButton::clicked, this, &AdminGUI::displayChart);
    QObject::connect(this->undoButton, &QPushButton::clicked, this, &AdminGUI::undoGUI);
    QObject::connect(this->redoButton, &QPushButton::clicked, this, &AdminGUI::redoGUI);
}

void AdminGUI::addDog() {
    std::string breed = this->breedLineEdit->text().toStdString();
    std::string name = this->nameLineEdit->text().toStdString();
    std::string age_s = this->ageLineEdit->text().toStdString();
    std::string link = this->linkLineEdit->text().toStdString();
    int age;
    try {
        this->validator.validateBreed(breed);
        this->validator.validateName(name);
        this->validator.validateAgeString(age_s);
        age = stoi(age_s);
        this->validator.validateAge(age);
        this->validator.validatePhotoLink(link);
        this->service.addService(breed, name, age, link);
        this->populateList();
    } catch (ValidationException& exc) {
        auto* error = new QMessageBox();
        error->setIcon(QMessageBox::Critical);
        error->setText(exc.what());
        error->setWindowTitle("Invalid input!");
        error->exec();
    } catch (RepositoryException& re) {
        auto* error = new QMessageBox();
        error->setIcon(QMessageBox::Critical);
        error->setText(re.what());
        error->setWindowTitle("Error at adding dog!");
        error->exec();
    }
}

void AdminGUI::deleteDog() {
    try {
        std::string name = this->nameLineEdit->text().toStdString();
        this->validator.validateName(name);
        this->service.deleteService(name);
        this->populateList();
    } catch (ValidationException& exc) {
        auto* error = new QMessageBox();
        error->setIcon(QMessageBox::Critical);
        error->setText(exc.what());
        error->setWindowTitle("Invalid input!");
        error->exec();
    } catch (RepositoryException& re) {
        auto* error = new QMessageBox();
        error->setIcon(QMessageBox::Critical);
        error->setText(re.what());
        error->setWindowTitle("Error at deleting dog!");
        error->exec();
    }
}

void AdminGUI::updateDog() {
    int index = this->getSelectedIndex();
    try {
        if (index < 0) {
            auto* error = new QMessageBox();
            error->setIcon(QMessageBox::Critical);
            error->setText("No dog selected!");
            error->setWindowTitle("Selection error!");
            error->exec();
        } else {
            std::string old_name = this->service.getAllService()[index].nameGetter();
            std::string new_name = this->nameLineEdit->text().toStdString();
            std::string new_breed = this->breedLineEdit->text().toStdString();
            std::string age_s = this->ageLineEdit->text().toStdString();
            int age;
            std::string new_link = this->linkLineEdit->text().toStdString();
            this->validator.validateName(old_name);
            this->validator.validateName(new_name);
            this->validator.validateBreed(new_breed);
            this->validator.validateAgeString(age_s);
            age = stoi(age_s);
            this->validator.validateAge(age);
            this->validator.validatePhotoLink(new_link);
            this->service.updateService(old_name, new_breed, new_name, age, new_link);
            this->populateList();
        }
    } catch (ValidationException& exc) {
        auto* error = new QMessageBox();
        error->setIcon(QMessageBox::Critical);
        error->setText(exc.what());
        error->setWindowTitle("Invalid input!");
        error->exec();
    } catch (RepositoryException& re) {
        auto* error = new QMessageBox();
        error->setIcon(QMessageBox::Critical);
        error->setText(re.what());
        error->setWindowTitle("Error at deleting dog!");
        error->exec();
    }
}

void AdminGUI::displayChart() {
    this->chartWindow = new QWidget{};
    auto* chartLayout = new QVBoxLayout(this->chartWindow);
    this->chartWindow->setStyleSheet("background-color:#D9DBF1");
    std::vector<std::string> breeds = this->service.getAllBreeds();
    auto* chart = new QtCharts::QChart();
    auto *axis_x = new QtCharts::QBarCategoryAxis();
    axis_x->setTitleText("Breeds");

    QStringList categories;
    for (int i = 1; i <= breeds.size(); i++) {
        categories << QString::fromStdString(std::to_string(i));
    }

    axis_x->append(categories);
    chart->addAxis(axis_x, Qt::AlignBottom);

    auto* axis_y = new QtCharts::QValueAxis();
    chart->addAxis(axis_y, Qt::AlignLeft);
    axis_y->setRange(0, 8);
    axis_y->setTitleText("Number of dogs");

    for (std::string& breed: breeds) {
        auto *series = new QtCharts::QBarSeries();
        auto* set = new QtCharts::QBarSet(QString::fromStdString(breed));
        int number_of_dogs = this->service.numberOfDogsPerBreed(breed);
        *set << number_of_dogs;
        series->append(set);
        chart->addSeries(series);
        series->attachAxis(axis_y);
    }

    chart->setTitle("Number of dogs per breed");
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignLeft);
    chart->legend()->setBackgroundVisible(true);
    chart->legend()->setBorderColor(QColor::fromRgb(171, 147, 225));
    chart->legend()->setFont(QFont("Cambria Math", 7));

    auto* chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    chartLayout->addWidget(chartView);
    this->chartWindow->resize(840, 720);
    this->chartWindow->show();
}

int AdminGUI::getSelectedIndex() const {
    QModelIndexList selectedIndexes = this->dogsListWidget->selectionModel()->selectedIndexes();
    if (selectedIndexes.empty()) {
        this->nameLineEdit->clear();
        this->breedLineEdit->clear();
        this->ageLineEdit->clear();
        this->linkLineEdit->clear();
        return -1;
    }
    int selectedIndex = selectedIndexes.at(0).row();
    return selectedIndex;
}

void AdminGUI::undoGUI() {
    try {
        this->service.undoLastAction();
        this->populateList();
    } catch (RepositoryException& re) {
        QMessageBox::critical(this, "Error", re.what());
    }
}

void AdminGUI::redoGUI() {
    try {
        this->service.redoLastAction();
        this->populateList();
    } catch (RepositoryException& re) {
        QMessageBox::critical(this, "Error", re.what());
    }
}

AdminGUI::~AdminGUI() = default;

void GUI::showUser() {
    this->userService.clearUndoRedo();
    auto* user = new UserGUI(this, this->service, this->userService, this->validator);
    user->show();
}


UserGUI::UserGUI(QWidget* parent, Service& serv, UserService &userserv, DogValidator& validator1): service{serv}, userService{userserv}, validator{validator1} {
    this->titleWidget = new QLabel(this);
    this->dogsListWidget = new QListWidget{};
    this->nameLineEdit = new QLineEdit{};
    this->breedLineEdit = new QLineEdit{};
    this->ageLineEdit = new QLineEdit{};
    this->linkLineEdit = new QLineEdit{};
    this->breedFilterLineEdit = new QLineEdit{};
    this->ageFilterLineEdit = new QLineEdit{};
    this->addButton = new QPushButton("Add to the adoption list");
    this->filterButton = new QPushButton("Filter");
    this->openListButton = new QPushButton("Open file");
    this->csvButton = new QRadioButton("CSV");
    this->htmlButton = new QRadioButton("HTML");
    this->undoButton = new QPushButton("Undo");
    this->redoButton = new QPushButton("Redo");
    this->shortcutUndo = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_U), this);
    this->shortcutRedo = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_R), this);
    this->repoTypeSelected = false;
    this->filtered = false;
    setParent(parent);
    setWindowFlag(Qt::Window);
    this->initUserGUI();
    this->populateDogList();
    this->connectSignalsAndSlots();
}

void UserGUI::initUserGUI() {
    auto* layout = new QVBoxLayout(this);
    QFont titleFont = this->titleWidget->font();
    this->titleWidget->setText("<p style='text-align:center'><font color=#4D2D52>USER MODE <br> Select the type of file you want for saving your adopted dogs!</font></p>");
    titleFont.setItalic(true);
    titleFont.setPointSize(10);
    titleFont.setStyleHint(QFont::System);
    titleFont.setWeight(63);
    this->titleWidget->setFont(titleFont);
    layout->addWidget(this->titleWidget);

    auto* radioButtonsLayout = new QGridLayout(this);
    radioButtonsLayout->addWidget(this->csvButton, 0, 0);
    radioButtonsLayout->addWidget(this->htmlButton, 1, 0);
    radioButtonsLayout->addWidget(this->openListButton, 0, 1);
    layout->addLayout(radioButtonsLayout);

    this->listAndTableLayout = new QGridLayout(this);
    this->listAndTableLayout->addWidget(this->dogsListWidget, 0, 0);
    layout->addLayout(this->listAndTableLayout);

    auto * dogDetailsLayout = new QFormLayout{};
    dogDetailsLayout->addRow("Name", this->nameLineEdit);
    dogDetailsLayout->addRow("Breed", this->breedLineEdit);
    dogDetailsLayout->addRow("Age", this->ageLineEdit);
    dogDetailsLayout->addRow("Link", this->linkLineEdit);
    dogDetailsLayout->addRow(this->addButton);
    layout->addLayout(dogDetailsLayout);

    auto* undoRedoLayout = new QGridLayout(this);
    undoRedoLayout->addWidget(this->undoButton, 0, 0);
    undoRedoLayout->addWidget(this->redoButton, 0, 1);
    layout->addLayout(undoRedoLayout);


    auto *filterTitle = new QLabel("<p style='text-align:center'><font color=#4D2D52><br>Filter the available dogs by breed and age</font></p>");
    QFont filterFont = filterTitle->font();
    filterFont.setPointSize(10);
    filterFont.setStyleHint(QFont::System);
    filterFont.setWeight(63);
    filterTitle->setFont(filterFont);
    layout->addWidget(filterTitle);

    auto *  filterDetailsLayout = new QFormLayout{};
    filterDetailsLayout->addRow("Breed", this->breedFilterLineEdit);
    filterDetailsLayout->addRow("Age", this->ageFilterLineEdit);
    filterDetailsLayout->addRow(this->filterButton);
    layout->addLayout(filterDetailsLayout);

}

void UserGUI::createTable() {
    this->adoptionListTableModel = new DogTableModel{this->userService.getUserRepo()};
    this->adoptionListTable = new QTableView{};
    this->adoptionListTable->setModel(this->adoptionListTableModel);
    this->adoptionListTable->setItemDelegate(new PictureDelegate{});
    this->listAndTableLayout->addWidget(this->adoptionListTable, 0, 1);
    this->adoptionListTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->resize(900, 500);
}

void UserGUI::populateDogList() {
    this->dogsListWidget->clear();
    std::vector<Dog> allDogs = this->service.getAllService();
    for (Dog& dog: allDogs)
        this->dogsListWidget->addItem(QString::fromStdString(dog.nameGetter()));
}

void UserGUI::connectSignalsAndSlots() {
    QObject::connect(this->dogsListWidget, &QListWidget::itemClicked, [this]() {
        std::string dog_name = this->dogsListWidget->selectedItems().at(0)->text().toStdString();
        int index = this->service.findByNameService(dog_name);
        Dog dog = this->service.getAllService()[index];
        this->nameLineEdit->setText(QString::fromStdString(dog.nameGetter()));
        this->breedLineEdit->setText(QString::fromStdString(dog.breedGetter()));
        this->ageLineEdit->setText(QString::fromStdString(std::to_string(dog.ageGetter())));
        this->linkLineEdit->setText(QString::fromStdString(dog.photoGetter()));
        std::string link = std::string("start ").append(dog.photoGetter());
        system(link.c_str());
    });

    QObject::connect(this->shortcutUndo, &QShortcut::activated, this, &UserGUI::undoGUI);
    QObject::connect(this->shortcutRedo, &QShortcut::activated, this, &UserGUI::redoGUI);

    QObject::connect(this->csvButton, &QRadioButton::clicked, [this]() {
        this->userService.repositoryType("csv");
        this->repoTypeSelected = true;
        this->createTable();
    });

    QObject::connect(this->htmlButton, &QRadioButton::clicked, [this]() {
        this->userService.repositoryType("html");
        this->repoTypeSelected = true;
        this->createTable();
    });

    QObject::connect(this->openListButton, &QPushButton::clicked, [this]() {
        if (!this->repoTypeSelected) {
            auto* error = new QMessageBox();
            error->setIcon(QMessageBox::Warning);
            error->setText("Please select the type of file you want!");
            error->setWindowTitle("File type warning!");
            error->exec();
        } else {
            std::string link = std::string("start ").append(this->userService.getFileService());
            system(link.c_str());
        }
    });

    QObject::connect(this->addButton, &QPushButton::clicked, this, &UserGUI::addDog);
    QObject::connect(this->filterButton, &QPushButton::clicked, this, &UserGUI::filterDogs);
    QObject::connect(this->undoButton, &QPushButton::clicked, this, &UserGUI::undoGUI);
    QObject::connect(this->redoButton, &QPushButton::clicked, this, &UserGUI::redoGUI);
}

int UserGUI::getSelectedIndex() const {
    QModelIndexList selectedIndexes = this->dogsListWidget->selectionModel()->selectedIndexes();
    if (selectedIndexes.empty()) {
        this->nameLineEdit->clear();
        this->breedLineEdit->clear();
        this->ageLineEdit->clear();
        this->linkLineEdit->clear();
        return -1;
    }
    int selectedIndex = selectedIndexes.at(0).row();
    return selectedIndex;
}

void UserGUI::populateAdoptionList() {
    this->adoptionListTableModel->update();
    this->adoptionListTable->resizeRowsToContents();
    this->adoptionListTable->resizeColumnsToContents();
}

void UserGUI::addDog() {
    if (!this->repoTypeSelected) {
        auto *error = new QMessageBox();
        error->setIcon(QMessageBox::Warning);
        error->setText("Please select the type of file you want!");
        error->setWindowTitle("File type warning!");
        error->exec();
    } else {
        std::string breed = this->breedLineEdit->text().toStdString();
        std::string name = this->nameLineEdit->text().toStdString();
        std::string age_s = this->ageLineEdit->text().toStdString();
        std::string link = this->linkLineEdit->text().toStdString();
        int age;
        try {
            this->validator.validateBreed(breed);
            this->validator.validateName(name);
            this->validator.validateAgeString(age_s);
            age = stoi(age_s);
            this->validator.validateAge(age);
            this->validator.validatePhotoLink(link);
            Dog dog = Dog(breed, name, age, link);
            this->userService.addUserService(dog);
            if (!this->filtered)
                this->populateDogList();
            else
                this->adoptionListWidget->addItem(this->dogsListWidget->takeItem(this->getSelectedIndex()));
            this->populateAdoptionList();
        } catch (ValidationException& exc) {
            auto* error = new QMessageBox();
            error->setIcon(QMessageBox::Critical);
            error->setText(exc.what());
            error->setWindowTitle("Invalid input!");
            error->exec();
        } catch (RepositoryException& re) {
            auto* error = new QMessageBox();
            error->setIcon(QMessageBox::Critical);
            error->setText(re.what());
            error->setWindowTitle("Error at adding dog!");
            error->exec();
        }
    }
}

void UserGUI::filterDogs(){
    try {
        std::string breed_filter = this->breedFilterLineEdit->text().toStdString();
        std::string age_filter_s = this->ageFilterLineEdit->text().toStdString();
        int age;
        if (breed_filter.empty() && age_filter_s.empty()) {
            this->filtered = false;
            this->populateDogList();
        } else {
            this->validator.validateString(breed_filter);
            this->validator.validateAgeString(age_filter_s);
            age = stoi(age_filter_s);
            this->validator.validateAge(age);
            std::vector<Dog> validDogs;
            this->service.getFiltered(validDogs, breed_filter, age);
            if (validDogs.empty()) {
                std::string error;
                error += std::string("The list of valid dogs is empty!");
                if(!error.empty())
                    throw UserException(error);
            } else {
                this->filtered = true;
                this->dogsListWidget->clear();
                for (Dog& dog: validDogs)
                    this->dogsListWidget->addItem(QString::fromStdString(dog.nameGetter()));
            }
        }
    } catch (ValidationException& ve) {
        auto *error = new QMessageBox();
        error->setIcon(QMessageBox::Critical);
        error->setText(ve.what());
        error->setWindowTitle("Validation error!");
        error->exec();
    } catch (UserException& ue) {
        auto *error = new QMessageBox();
        error->setIcon(QMessageBox::Critical);
        error->setText(ue.what());
        error->setWindowTitle("Filter error!");
        error->exec();
    }
}

void UserGUI::undoGUI() {
    try {
        this->userService.undoLastAction();
        this->populateDogList();
        this->populateAdoptionList();
    } catch (RepositoryException& re) {
        QMessageBox::critical(this, "Error", re.what());
    }
}

void UserGUI::redoGUI() {
    try {
        this->userService.redoLastAction();
        this->populateDogList();
        this->populateAdoptionList();
    } catch (RepositoryException& re) {
        QMessageBox::critical(this, "Error", re.what());
    }
}

UserGUI::~UserGUI() = default;