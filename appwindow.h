#ifndef APPWINDOW_H
#define APPWINDOW_H

#include "gridscene.h"
#include "ui_appwindow.h"
#include <QtWidgets/QMainWindow>

class AppWindow : public QMainWindow {
    Q_OBJECT

public:
    AppWindow(QWidget *parent = nullptr);

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    void setConnects();
    void saveSettings();
    void restoreSettings();

private:
    Ui::AppWindow ui;
    GridScene scene;
    const QString settingName{"WindowPos"};
};

#endif // APPWINDOW_H
