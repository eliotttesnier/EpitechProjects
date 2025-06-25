/*
** EPITECH PROJECT, 2025
** B-CCP-400-NAN-4-1-theplazza-eliott.tesnier
** File description:
** GuiApplication
*/

#pragma once

#ifdef GUI_ENABLED
#include <QApplication>

class GuiApplication : public QApplication {
    Q_OBJECT

public:
    GuiApplication(int &argc, char **argv);
    ~GuiApplication() = default;

    int run();

private:
    void setupApplication();
};

#endif // GUI_ENABLED
