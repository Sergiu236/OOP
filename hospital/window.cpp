#include "gui.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QInputDialog>
#include <iostream>
#include <algorithm>

CourierWindow::CourierWindow(Service& service, const Courier& courier) : service(service), courier(courier) {
    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* title = new QLabel(QString::fromStdString(courier.name));
    layout->addWidget(title);

    zoneLabel = new QLabel(QString("Zone: Center (%1, %2), Radius: %3")
                                   .arg(courier.zone_x).arg(courier.zone_y).arg(courier.zone_radius));
    layout->addWidget(zoneLabel);

    packageList = new QListWidget();
    layout->addWidget(packageList);

    streetComboBox = new QComboBox();
    streetComboBox->addItem("All Streets");
    for (const auto& street : courier.streets) {
        streetComboBox->addItem(QString::fromStdString(street));
    }
    layout->addWidget(streetComboBox);
    connect(streetComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(filterPackages()));

    QPushButton* deliverButton = new QPushButton("Deliver");
    layout->addWidget(deliverButton);
    connect(deliverButton, SIGNAL(clicked()), this, SLOT(deliverPackage()));

    update();
}

void CourierWindow::update() {
    packageList->clear();
    std::vector<Package> undeliveredPackages;

    // Filter out only undelivered packages
    for (auto& package : service.getPackages()) {
        if (!package.delivery_status) {
            undeliveredPackages.push_back(package);
        }
    }

    QString selectedStreet = streetComboBox->currentText();
    bool filterByStreet = selectedStreet != "All Streets";

    for (auto& package : undeliveredPackages) {
        if (std::find(courier.streets.begin(), courier.streets.end(), package.address_street) != courier.streets.end() ||
            (package.location_x - courier.zone_x) * (package.location_x - courier.zone_x) +
            (package.location_y - courier.zone_y) * (package.location_y - courier.zone_y) <= courier.zone_radius * courier.zone_radius) {
            if (!filterByStreet || QString::fromStdString(package.address_street) == selectedStreet) {
                packageList->addItem(QString::fromStdString(package.recipient + " " + package.address_street + " " + std::to_string(package.address_number)));
                std::cout << "Added package to list: " << package.recipient << ", " << package.address_street << std::endl;
            }
        }
    }
}

void CourierWindow::deliverPackage() {
    auto items = packageList->selectedItems();
    if (!items.empty()) {
        auto item = items.first();
        auto text = item->text().toStdString();
        for (auto& package : service.getPackages()) {
            if (text.find(package.recipient) != std::string::npos && text.find(package.address_street) != std::string::npos) {
                service.deliverPackage(const_cast<Package&>(package));
                break;
            }
        }
    }
}

void CourierWindow::filterPackages() {
    update();
}

CompanyWindow::CompanyWindow(Service& service) : service(service) {
    QVBoxLayout* layout = new QVBoxLayout(this);

    packageList = new QListWidget();
    layout->addWidget(packageList);

    QPushButton* addButton = new QPushButton("Add Package");
    layout->addWidget(addButton);
    connect(addButton, SIGNAL(clicked()), this, SLOT(addPackage()));

    update();
}

void CompanyWindow::update() {
    packageList->clear();
    for (auto& package : service.getPackages()) {
        QString itemText = QString::fromStdString(package.recipient + " " + package.address_street + " " + std::to_string(package.address_number));
        QListWidgetItem* item = new QListWidgetItem(itemText);
        if (package.delivery_status) {
            item->setBackground(Qt::green);
        }
        packageList->addItem(item);
    }
}

void CompanyWindow::addPackage() {
    Package package;
    bool ok;
    QString recipient = QInputDialog::getText(this, tr("Add Package"), tr("Recipient:"), QLineEdit::Normal, "", &ok);
    if (!ok || recipient.isEmpty()) return;
    QString addressStreet = QInputDialog::getText(this, tr("Add Package"), tr("Address Street:"), QLineEdit::Normal, "", &ok);
    if (!ok || addressStreet.isEmpty()) return;
    int addressNumber = QInputDialog::getInt(this, tr("Add Package"), tr("Address Number:"), 1, 1, 1000, 1, &ok);
    if (!ok) return;
    double locationX = QInputDialog::getDouble(this, tr("Add Package"), tr("Location X:"), 0.0, -10000, 10000, 2, &ok);
    if (!ok) return;
    double locationY = QInputDialog::getDouble(this, tr("Add Package"), tr("Location Y:"), 0.0, -10000, 10000, 2, &ok);
    if (!ok) return;

    package.recipient = recipient.toStdString();
    package.address_street = addressStreet.toStdString();
    package.address_number = addressNumber;
    package.location_x = locationX;
    package.location_y = locationY;
    package.delivery_status = false;

    service.addPackage(package);
}

MapWindow::MapWindow(Service& service) : service(service) {
    setFixedSize(400, 400);
}

void MapWindow::update() {
    repaint();
}

void MapWindow::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    for (auto& package : service.getPackages()) {
        if (!package.delivery_status) {
            if (package.address_street.find("rectangle") != std::string::npos) {
                painter.drawRect(static_cast<int>(package.location_x), static_cast<int>(package.location_y), 10, 10);
            } else {
                painter.drawEllipse(static_cast<int>(package.location_x), static_cast<int>(package.location_y), 10, 10);
            }
        }
    }
}
