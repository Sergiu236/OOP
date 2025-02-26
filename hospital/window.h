#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include <QListWidget>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include "service.h"
#include "observer.h"

class CourierWindow : public QWidget, public Observer {
    Q_OBJECT

            Service& service;
    Courier courier;
    QListWidget* packageList;
    QComboBox* streetComboBox;
    QLabel* zoneLabel;

public:
    CourierWindow(Service& service, const Courier& courier);
    void update() override;

private slots:
            void deliverPackage();
    void filterPackages();
};

class CompanyWindow : public QWidget, public Observer {
    Q_OBJECT

            Service& service;
    QListWidget* packageList;

public:
    CompanyWindow(Service& service);
    void update() override;

private slots:
            void addPackage();
};

class MapWindow : public QWidget, public Observer {
    Q_OBJECT

            Service& service;

public:
    MapWindow(Service& service);
    void update() override;

protected:
    void paintEvent(QPaintEvent* event) override;
};

#endif // GUI_H
