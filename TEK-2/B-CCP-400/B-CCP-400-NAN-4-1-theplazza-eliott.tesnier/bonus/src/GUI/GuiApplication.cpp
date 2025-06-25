/*
** EPITECH PROJECT, 2025
** B-CCP-400-NAN-4-1-theplazza-eliott.tesnier
** File description:
** GuiApplication
*/

#ifdef GUI_ENABLED
#include "GuiApplication.hpp"
#include "ReceptionGUI.hpp"
#include <QStyleFactory>

GuiApplication::GuiApplication(int &argc, char **argv)
    : QApplication(argc, argv)
{
    setupApplication();
}

void GuiApplication::setupApplication()
{
    setApplicationName("Plazza");
    setApplicationVersion("1.0");
    setOrganizationName("Epitech");

    setStyle(QStyleFactory::create("Fusion"));
}

int GuiApplication::run()
{
    ReceptionGUI *reception = new ReceptionGUI();
    reception->show();

    return exec();
}

#endif // GUI_ENABLED
