/*
** EPITECH PROJECT, 2025
** B-CCP-400-NAN-4-1-theplazza-eliott.tesnier
** File description:
** ReceptionGUI
*/

#pragma once

#ifdef GUI_ENABLED
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QSplitter>
#include <QTimer>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QCompleter>
#include <QStringList>
#include <QHeaderView>
#include <QTabWidget>
#include <QSystemTrayIcon>
#include <QFrame>
#include <iostream>
#include <sstream>
#include <streambuf>
#include <functional>
#include <map>
#include <vector>

#include "IReceptionInterface.hpp"
#include "../Config/Config.hpp"

class Reception;

struct OrderInfo {
    int id;
    QString orderText;
    QString status;
    QString timestamp;
    QString duration;
};

class ReceptionGUI : public QMainWindow, public IReceptionInterface {
    Q_OBJECT

public:
    explicit ReceptionGUI(QWidget *parent = nullptr);
    ~ReceptionGUI();

    int run() override;
    void setConfig(const Config &config);

private slots:
    void onCommandEntered();
    void onStatusUpdate();
    void checkForOrderCompletions();
    void onCommandTextChanged();
    void showOrderCompleteNotification(const QString &message);

private:
    void setupUI();
    void setupMenuBar();
    void setupStatusBar();
    void connectSignals();
    void setupAutoCompletion();
    void setupOrderTables();
    void updateOrderStatus(int orderId, const QString &status, const QString &duration = "");
    void addNewOrder(int orderId, const QString &orderText);
    bool validateCommandSyntax(const QString &command);
    void updateCommandValidation();

    std::string getKitchenStatus();

    QWidget *m_centralWidget;
    QSplitter *m_mainSplitter;
    QTextEdit *m_outputDisplay;
    QLineEdit *m_commandInput;
    QPushButton *m_sendButton;
    QTextEdit *m_statusDisplay;
    QTimer *m_statusTimer;

    QTabWidget *m_orderTabWidget;
    QTableWidget *m_activeOrdersTable;
    QTableWidget *m_completedOrdersTable;
    QCompleter *m_commandCompleter;
    QLabel *m_validationLabel;
    QFrame *m_validationFrame;

    Reception *m_reception;
    Config m_config;
    bool m_configSet;

    std::streambuf* m_originalCoutBuffer;
    std::ostringstream m_globalCaptureBuffer;
    QTimer *m_outputCheckTimer;

    std::map<int, OrderInfo> m_orders;
    QStringList m_pizzaTypes;
    QStringList m_pizzaSizes;
};

#endif // GUI_ENABLED
