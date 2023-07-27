#include "appwindow.h"
#include <QScreen>
#include <QSettings>

AppWindow::AppWindow(QWidget *parent) : QMainWindow(parent) {
    ui.setupUi(this);
    restoreSettings();
    ui.graphicsView->setScene(&scene);
    setConnects();
}

void AppWindow::closeEvent(QCloseEvent *event) {
    saveSettings();
    QWidget::closeEvent(event);
}

void AppWindow::setConnects() {
    connect(ui.generateButton, &QPushButton::released, [this]() {
        ui.statusbar->clearMessage();
        scene.cellsX = ui.widthSpinBox->value();
        scene.cellsY = ui.heightSpinBox->value();
        scene.callGenerate();
    });

    connect(&scene, &GridScene::info,
            [this](std::tuple<int, int, int, int, int> info) {
                ui.statusbar->showMessage(
                    "A (" + QString::number(std::get<0>(info)) + "," +
                    QString::number(std::get<1>(info)) + "), B(" +
                    QString::number(std::get<2>(info)) + "," +
                    QString::number(std::get<3>(info)) +
                    ")    Path: " + QString::number(std::get<4>(info)));
            });
}

void AppWindow::saveSettings() {
    QSettings settings;
    settings.setValue(settingName, pos());
}

void AppWindow::restoreSettings() {
    QSettings settings;
    QVariant pos = settings.value(settingName);
    if (pos.isValid() && screen()->availableGeometry().contains(pos.toPoint()))
        move(pos.toPoint());
}
