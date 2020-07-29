#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Button_Run_pressed()
{
    int entCount = ui->spinbox_entitycount->value();
    int initInf = ui->spinbox_initialinfected->value();
    int initMob = ui->spinbox_mobileentities->value();
    int hospCap = ui->spinbox_hospitalcap->value();

    int tpt = ui->spinbox_testspertick->value();
    int tue = ui->spinbox_ticksuntilexpiration->value();

    double infChance = ui->spinbox_infectionchance->value();
    double survChance = ui->spinbox_survivalchance->value();
    double detectChance = ui->spinbox_detectionchance->value();

    double infRadius = ui->spinbox_influenceradius->value();
    bool distancing = ui->checkbox_distancing->isChecked();
    int centralLocations = ui->spinbox_centrallocations->value();

    int width = ui->spinbox_width->value();
    int height = ui->spinbox_height->value();
    int iterations = ui->spinbox_iterations->value();
    int threads = ui->spinbox_threads->value();

    std::string cmd = "./SpreadSimulation " + std::to_string(entCount) + " "
            + std::to_string(initInf) + " "
            + std::to_string(initMob) + " "
            + std::to_string(hospCap) + " "
            + std::to_string(tpt) + " "
            + std::to_string(tue) + " "
            + std::to_string(infChance * 100) + " "
            + std::to_string(survChance * 100) + " "
            + std::to_string(detectChance * 100) + " "
            + std::to_string(infRadius) + " "
            + std::to_string(distancing) + " "
            + std::to_string(centralLocations) + " "
            + std::to_string(width) + " "
            + std::to_string(height) + " "
            + std::to_string(iterations) + " "
            + std::to_string(threads) + " | python StatRenderer.py";

    system(cmd.c_str());
}
