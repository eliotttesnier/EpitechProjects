/*
** EPITECH PROJECT, 2025
** B-CCP-400-NAN-4-1-theplazza-eliott.tesnier
** File description:
** ReceptionGUI
*/

#ifdef GUI_ENABLED
#include "ReceptionGUI.hpp"
#include "../Reception/Reception.hpp"
#include "../Utils/ColorUtils.hpp"

#include <QMenuBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QApplication>
#include <QDateTime>
#include <QRegularExpression>
#include <QHeaderView>
#include <QTabWidget>
#include <QTableWidget>
#include <QCompleter>
#include <QStringList>
#include <QFrame>
#include <QSystemTrayIcon>
#include <QDebug>

ReceptionGUI::ReceptionGUI(QWidget *parent)
    : QMainWindow(parent)
    , m_centralWidget(nullptr)
    , m_mainSplitter(nullptr)
    , m_outputDisplay(nullptr)
    , m_commandInput(nullptr)
    , m_sendButton(nullptr)
    , m_statusDisplay(nullptr)
    , m_statusTimer(new QTimer(this))
    , m_orderTabWidget(nullptr)
    , m_activeOrdersTable(nullptr)
    , m_completedOrdersTable(nullptr)
    , m_commandCompleter(nullptr)
    , m_validationLabel(nullptr)
    , m_validationFrame(nullptr)
    , m_reception(nullptr)
    , m_configSet(false)
    , m_originalCoutBuffer(nullptr)
    , m_outputCheckTimer(new QTimer(this))
{
    m_pizzaTypes << "regina" << "margarita" << "americana" << "fantasia" << "hawaiian";
    m_pizzaSizes << "S" << "M" << "L" << "XL" << "XXL";

    setupUI();
    setupAutoCompletion();
    setupOrderTables();
    setupMenuBar();
    setupStatusBar();
    connectSignals();

    setWindowTitle("Plazza - Pizza Management System");
    setMinimumSize(1000, 700);
    resize(1400, 900);
}

ReceptionGUI::~ReceptionGUI()
{
    if (m_originalCoutBuffer) {
        std::cout.rdbuf(m_originalCoutBuffer);
    }

    if (m_reception) {
        m_reception->stopListenerThread();
        delete m_reception;
    }
}

void ReceptionGUI::setupUI()
{
    m_centralWidget = new QWidget;
    setCentralWidget(m_centralWidget);

    m_mainSplitter = new QSplitter(Qt::Horizontal);

    QWidget *leftWidget = new QWidget;
    QVBoxLayout *leftLayout = new QVBoxLayout(leftWidget);

    m_outputDisplay = new QTextEdit;
    m_outputDisplay->setReadOnly(true);
    m_outputDisplay->setPlaceholderText("Pizza orders and system messages will appear here...");

    m_validationFrame = new QFrame;
    m_validationFrame->setFrameStyle(QFrame::StyledPanel);
    m_validationFrame->setLineWidth(2);
    QVBoxLayout *validationLayout = new QVBoxLayout(m_validationFrame);

    QHBoxLayout *inputLayout = new QHBoxLayout;
    m_commandInput = new QLineEdit;
    m_commandInput->setPlaceholderText("Enter pizza order (e.g., 'regina XXL x2; margarita M x1') or 'status'");
    m_sendButton = new QPushButton("Send");

    inputLayout->addWidget(new QLabel("Command:"));
    inputLayout->addWidget(m_commandInput);
    inputLayout->addWidget(m_sendButton);

    m_validationLabel = new QLabel;
    m_validationLabel->setWordWrap(true);
    m_validationLabel->setStyleSheet("QLabel { color: gray; font-style: italic; }");

    validationLayout->addLayout(inputLayout);
    validationLayout->addWidget(m_validationLabel);

    leftLayout->addWidget(new QLabel("Output:"));
    leftLayout->addWidget(m_outputDisplay);
    leftLayout->addWidget(m_validationFrame);

    m_orderTabWidget = new QTabWidget;

    QWidget *rightWidget = new QWidget;
    QVBoxLayout *rightLayout = new QVBoxLayout(rightWidget);

    m_statusDisplay = new QTextEdit;
    m_statusDisplay->setReadOnly(true);
    m_statusDisplay->setPlaceholderText("Kitchen status will be displayed here...");

    rightLayout->addWidget(new QLabel("Kitchen Status:"));
    rightLayout->addWidget(m_statusDisplay);

    m_mainSplitter->addWidget(leftWidget);
    m_mainSplitter->addWidget(m_orderTabWidget);
    m_mainSplitter->addWidget(rightWidget);
    m_mainSplitter->setSizes({400, 400, 300});

    QVBoxLayout *mainLayout = new QVBoxLayout(m_centralWidget);
    mainLayout->addWidget(m_mainSplitter);
}

void ReceptionGUI::setupMenuBar()
{
    QMenuBar *menuBar = this->menuBar();

    QMenu *fileMenu = menuBar->addMenu("&File");
    QAction *exitAction = fileMenu->addAction("E&xit");
    connect(exitAction, &QAction::triggered, this, &QWidget::close);

    QMenu *helpMenu = menuBar->addMenu("&Help");
    QAction *aboutAction = helpMenu->addAction("&About");
    connect(aboutAction, &QAction::triggered, [this]() {
        QMessageBox::about(this, "About Plazza",
            "Plazza Pizza Management System\n\n"
            "A simulation of a pizzeria with multiple kitchens,\n"
            "cooks, and real-time order processing.\n\n"
            "Version 1.0 - Epitech Project");
    });
}

void ReceptionGUI::setupStatusBar()
{
    statusBar()->showMessage("Ready - Enter commands to start ordering pizzas");
}

void ReceptionGUI::connectSignals()
{
    connect(m_sendButton, &QPushButton::clicked, this, &ReceptionGUI::onCommandEntered);
    connect(m_commandInput, &QLineEdit::returnPressed, this, &ReceptionGUI::onCommandEntered);
    connect(m_commandInput, &QLineEdit::textChanged, this, &ReceptionGUI::onCommandTextChanged);

    connect(m_statusTimer, &QTimer::timeout, this, &ReceptionGUI::onStatusUpdate);
    m_statusTimer->start(1000);
    connect(m_outputCheckTimer, &QTimer::timeout, this, &ReceptionGUI::checkForOrderCompletions);
    m_outputCheckTimer->start(500);
}

void ReceptionGUI::setConfig(const Config &config)
{
    m_config = config;
    m_configSet = true;

    if (m_reception) {
        delete m_reception;
    }
    m_reception = new Reception(m_config);

    if (!m_originalCoutBuffer) {
        m_originalCoutBuffer = std::cout.rdbuf();
        std::cout.rdbuf(m_globalCaptureBuffer.rdbuf());
    }

    m_reception->startListenerThread();

    m_outputDisplay->append(QString("✓ Plazza initialized with configuration:"));
    m_outputDisplay->append(QString("  - Multiplier: %1").arg(m_config.getMultiplier()));
    m_outputDisplay->append(QString("  - Cooks per kitchen: %1").arg(m_config.getCooksPerKitchen()));
    m_outputDisplay->append(QString("  - Regeneration time: %1ms").arg(m_config.getRegenerationTimeMs()));
    m_outputDisplay->append("");
}

int ReceptionGUI::run()
{
    return 0;
}

void ReceptionGUI::onCommandEntered()
{
    if (!m_configSet || !m_reception) {
        QMessageBox::warning(this, "Error", "Configuration not set. Please restart the application.");
        return;
    }

    QString command = m_commandInput->text().trimmed();
    if (command.isEmpty()) {
        return;
    }

    m_commandInput->clear();
    m_outputDisplay->append(QString("> %1").arg(command));

    try {
        std::string previousContent = m_globalCaptureBuffer.str();

        m_reception->processCommand(command.toStdString());

        std::string newContent = m_globalCaptureBuffer.str();
        if (newContent.length() > previousContent.length()) {
            std::string immediateOutput = newContent.substr(previousContent.length());

            QString cleanOutput = QString::fromStdString(immediateOutput);
            cleanOutput.remove(QRegularExpression("\x1B\\[[0-9;]*[A-Za-z]"));

            if (!cleanOutput.trimmed().isEmpty()) {
                m_outputDisplay->append(cleanOutput.trimmed());

                if (cleanOutput.contains("Order #")) {
                    QRegularExpression orderPattern(R"(Order #(\d+) registered)");
                    QRegularExpressionMatch match = orderPattern.match(cleanOutput);
                    if (match.hasMatch()) {
                        int orderId = match.captured(1).toInt();
                        addNewOrder(orderId, command);
                    }
                }
            }
        }

        statusBar()->showMessage(QString("Last command: %1").arg(command), 5000);

    } catch (const std::exception& e) {
        QString errorMsg = QString("Error processing command: %1").arg(e.what());
        m_outputDisplay->append(QString("<span style='color: red;'>%1</span>").arg(errorMsg));
        QMessageBox::warning(this, "Command Error", errorMsg);
    }
}

void ReceptionGUI::onStatusUpdate()
{
    if (!m_configSet || !m_reception) {
        return;
    }

    try {
        QString statusInfo = QString::fromStdString(getKitchenStatus());

        statusInfo.remove(QRegularExpression("\x1B\\[[0-9;]*[A-Za-z]"));

        m_statusDisplay->clear();
        m_statusDisplay->append(statusInfo);

    } catch (const std::exception& e) {
        m_statusDisplay->clear();
        m_statusDisplay->append(QString("Error getting status: %1").arg(e.what()));
    }
}

void ReceptionGUI::checkForOrderCompletions()
{
    if (!m_configSet || !m_reception) {
        return;
    }

    std::string currentContent = m_globalCaptureBuffer.str();
    static std::string lastProcessedContent;

    if (currentContent.length() > lastProcessedContent.length()) {
        std::string newContent = currentContent.substr(lastProcessedContent.length());

        if (!newContent.empty()) {
            QString newContentStr = QString::fromStdString(newContent);
            newContentStr.remove(QRegularExpression("\x1B\\[[0-9;]*[A-Za-z]"));

            QStringList lines = newContentStr.split('\n', Qt::SkipEmptyParts);
            for (const QString &line : lines) {
                QString trimmedLine = line.trimmed();
                if (!trimmedLine.isEmpty()) {
                    qDebug() << "Captured line:" << trimmedLine;

                    bool isStatusMessage = trimmedLine.contains("=== Kitchen Status ===") ||
                                         trimmedLine.contains("Kitchen #") ||
                                         trimmedLine.contains("- Cooks:") ||
                                         trimmedLine.contains("- Current Load:") ||
                                         trimmedLine.contains("- Ingredients:") ||
                                         trimmedLine.contains("* ") ||
                                         trimmedLine == "No active kitchens.";

                    if (trimmedLine.contains("ORDER COMPLETE", Qt::CaseInsensitive)) {
                        qDebug() << "ORDER COMPLETE message captured:" << trimmedLine;

                        m_outputDisplay->append(QString("<span style='color: green; font-weight: bold;'>✅ %1</span>").arg(trimmedLine));
                        m_outputDisplay->ensureCursorVisible();
                        statusBar()->showMessage("✅ Order completed!", 3000);

                        QRegularExpression orderCompletePattern(R"(ORDER COMPLETE: Order #(\d+):.*in : (\d+m \d+s) seconds)");
                        QRegularExpressionMatch match = orderCompletePattern.match(trimmedLine);
                        if (match.hasMatch()) {
                            int orderId = match.captured(1).toInt();
                            QString duration = match.captured(2);
                            qDebug() << "Parsed order completion - ID:" << orderId << "Duration:" << duration;
                            updateOrderStatus(orderId, "Terminée", duration);
                        } else {
                            qDebug() << "Failed to parse ORDER COMPLETE message:" << trimmedLine;
                        }
                    } else if (!isStatusMessage && !trimmedLine.startsWith(">")) {
                        m_outputDisplay->append(trimmedLine);
                        m_outputDisplay->ensureCursorVisible();
                    }
                }
            }
        }

        lastProcessedContent = currentContent;
    }
}

std::string ReceptionGUI::getKitchenStatus()
{
    if (!m_configSet || !m_reception) {
        return "No reception configured";
    }

    std::string previousContent = m_globalCaptureBuffer.str();

    m_reception->showStatus();

    std::string newContent = m_globalCaptureBuffer.str();
    if (newContent.length() > previousContent.length()) {
        return newContent.substr(previousContent.length());
    }

    return "";
}

void ReceptionGUI::setupAutoCompletion()
{
    QStringList completionList;

    for (const QString &pizza : m_pizzaTypes) {
        for (const QString &size : m_pizzaSizes) {
            completionList << pizza + " " + size;
            completionList << pizza + " " + size + " x1";
            completionList << pizza + " " + size + " x2";
            completionList << pizza + " " + size + " x3";
            completionList << pizza + " " + size + " x4";
            completionList << pizza + " " + size + " x5";
        }
    }

    completionList << "status";

    m_commandCompleter = new QCompleter(completionList, this);
    m_commandCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    m_commandCompleter->setFilterMode(Qt::MatchContains);
    m_commandInput->setCompleter(m_commandCompleter);
}

void ReceptionGUI::setupOrderTables()
{
    m_activeOrdersTable = new QTableWidget(0, 4);
    QStringList activeHeaders;
    activeHeaders << "Order ID" << "Pizza Order" << "Status" << "Time Started";
    m_activeOrdersTable->setHorizontalHeaderLabels(activeHeaders);
    m_activeOrdersTable->horizontalHeader()->setStretchLastSection(true);
    m_activeOrdersTable->setAlternatingRowColors(true);
    m_activeOrdersTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    m_completedOrdersTable = new QTableWidget(0, 5);
    QStringList completedHeaders;
    completedHeaders << "Order ID" << "Pizza Order" << "Status" << "Time Started" << "Duration";
    m_completedOrdersTable->setHorizontalHeaderLabels(completedHeaders);
    m_completedOrdersTable->horizontalHeader()->setStretchLastSection(true);
    m_completedOrdersTable->setAlternatingRowColors(true);
    m_completedOrdersTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    m_orderTabWidget->addTab(m_activeOrdersTable, "En cours (0)");
    m_orderTabWidget->addTab(m_completedOrdersTable, "Terminées (0)");
}

void ReceptionGUI::onCommandTextChanged()
{
    updateCommandValidation();
}

void ReceptionGUI::updateCommandValidation()
{
    QString command = m_commandInput->text().trimmed();

    if (command.isEmpty()) {
        m_validationLabel->setText("Entrez une commande de pizza ou 'status'");
        m_validationLabel->setStyleSheet("QLabel { color: gray; font-style: italic; }");
        m_validationFrame->setStyleSheet("QFrame { border: 2px solid gray; }");
        return;
    }

    bool isValid = validateCommandSyntax(command);

    if (isValid) {
        m_validationLabel->setText("✓ Syntaxe valide");
        m_validationLabel->setStyleSheet("QLabel { color: green; font-weight: bold; }");
        m_validationFrame->setStyleSheet("QFrame { border: 2px solid green; }");
    } else {
        m_validationLabel->setText("✗ Syntaxe invalide. Format attendu: 'pizza taille xquantité' ou 'status'");
        m_validationLabel->setStyleSheet("QLabel { color: red; font-weight: bold; }");
        m_validationFrame->setStyleSheet("QFrame { border: 2px solid red; }");
    }
}

bool ReceptionGUI::validateCommandSyntax(const QString &command)
{
    QString cmd = command.trimmed().toLower();

    if (cmd == "status") {
        return true;
    }

    QRegularExpression pizzaPattern(R"(^(\s*([a-zA-Z]+)\s+(S|M|L|XL|XXL)\s+x\d+\s*;?\s*)+$)", QRegularExpression::CaseInsensitiveOption);

    if (!pizzaPattern.match(cmd).hasMatch()) {
        return false;
    }

    QStringList orders = cmd.split(';', Qt::SkipEmptyParts);
    for (const QString &order : orders) {
        QRegularExpression singlePizzaPattern(R"(^\s*([a-zA-Z]+)\s+(S|M|L|XL|XXL)\s+x\d+\s*$)", QRegularExpression::CaseInsensitiveOption);
        QRegularExpressionMatch match = singlePizzaPattern.match(order.trimmed());

        if (!match.hasMatch()) {
            return false;
        }

        QString pizzaType = match.captured(1).toLower();
        QString size = match.captured(2).toUpper();

        if (!m_pizzaTypes.contains(pizzaType, Qt::CaseInsensitive)) {
            return false;
        }

        if (!m_pizzaSizes.contains(size)) {
            return false;
        }
    }

    return true;
}

void ReceptionGUI::addNewOrder(int orderId, const QString &orderText)
{
    OrderInfo order;
    order.id = orderId;
    order.orderText = orderText;
    order.status = "En cours";
    order.timestamp = QDateTime::currentDateTime().toString("hh:mm:ss");
    order.duration = "";

    m_orders[orderId] = order;

    int row = m_activeOrdersTable->rowCount();
    m_activeOrdersTable->insertRow(row);

    m_activeOrdersTable->setItem(row, 0, new QTableWidgetItem(QString::number(orderId)));
    m_activeOrdersTable->setItem(row, 1, new QTableWidgetItem(orderText));
    m_activeOrdersTable->setItem(row, 2, new QTableWidgetItem("🔄 En cours"));
    m_activeOrdersTable->setItem(row, 3, new QTableWidgetItem(order.timestamp));

    int activeCount = m_activeOrdersTable->rowCount();
    m_orderTabWidget->setTabText(0, QString("En cours (%1)").arg(activeCount));
}

void ReceptionGUI::updateOrderStatus(int orderId, const QString &status, const QString &duration)
{
    if (!m_orders.contains(orderId)) {
        return;
    }

    OrderInfo &order = m_orders[orderId];
    order.status = status;
    order.duration = duration;

    if (status == "Terminée") {
        for (int row = 0; row < m_activeOrdersTable->rowCount(); ++row) {
            QTableWidgetItem *idItem = m_activeOrdersTable->item(row, 0);
            if (idItem && idItem->text().toInt() == orderId) {
                m_activeOrdersTable->removeRow(row);
                break;
            }
        }

        int row = m_completedOrdersTable->rowCount();
        m_completedOrdersTable->insertRow(row);

        m_completedOrdersTable->setItem(row, 0, new QTableWidgetItem(QString::number(orderId)));
        m_completedOrdersTable->setItem(row, 1, new QTableWidgetItem(order.orderText));
        m_completedOrdersTable->setItem(row, 2, new QTableWidgetItem("✅ Terminée"));
        m_completedOrdersTable->setItem(row, 3, new QTableWidgetItem(order.timestamp));
        m_completedOrdersTable->setItem(row, 4, new QTableWidgetItem(duration));

        m_completedOrdersTable->scrollToBottom();

        int activeCount = m_activeOrdersTable->rowCount();
        int completedCount = m_completedOrdersTable->rowCount();
        m_orderTabWidget->setTabText(0, QString("En cours (%1)").arg(activeCount));
        m_orderTabWidget->setTabText(1, QString("Terminées (%1)").arg(completedCount));

        showOrderCompleteNotification(QString("Commande #%1 terminée en %2").arg(orderId).arg(duration));
    }
}

void ReceptionGUI::showOrderCompleteNotification(const QString &message)
{
    QMessageBox::information(this, "🍕 Commande terminée", message);
}

#endif // GUI_ENABLED
