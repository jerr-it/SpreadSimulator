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

void MainWindow::on_actionSave_Config_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save Config", "", "Config (*.cfg);;All Files(*)");
    if(filename.isEmpty()){
        return;
    }

    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly)){
        QMessageBox::information(this, "Unable to save file", file.errorString());
        return;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_4_9);

    out << ui->spinbox_entitycount->value();
    out << ui->spinbox_initialinfected->value();
    out << ui->spinbox_mobileentities->value();
    out << ui->spinbox_hospitalcap->value();

    out << ui->spinbox_testspertick->value();
    out << ui->spinbox_ticksuntilexpiration->value();

    out << ui->spinbox_infectionchance->value();
    out << ui->spinbox_survivalchance->value();
    out << ui->spinbox_detectionchance->value();

    out << ui->spinbox_influenceradius->value();
    out << ui->checkbox_distancing->isChecked();
    out << ui->spinbox_centrallocations->value();

    out << ui->spinbox_width->value();
    out << ui->spinbox_height->value();
    out << ui->spinbox_iterations->value();
    out << ui->spinbox_threads->value();
}

void MainWindow::on_actionLoad_Config_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Save Config", "", "Config (*.cfg);;All Files(*)");

    if(filename.isEmpty()){
        return;
    }

    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox::information(this, "Unable to open file", file.errorString());
        return;
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_4_9);

    int entCount;
    int initInf;
    int initMob;
    int hospCap;

    int tpt;
    int tue;

    double infChance;
    double survChance;
    double detectChance;

    double infRadius;
    bool distancing;
    int centralLocations;

    int width;
    int height;
    int iterations;
    int thread;

    in >> entCount;
    in >> initInf;
    in >> initMob;
    in >> hospCap;

    in >> tpt;
    in >> tue;

    in >> infChance;
    in >> survChance;
    in >> detectChance;

    in >> infRadius;
    in >> distancing;
    in >> centralLocations;

    in >> width;
    in >> height;
    in >> iterations;
    in >> thread;

    ui->spinbox_entitycount->setValue(entCount);
    ui->spinbox_initialinfected->setValue(initInf);
    ui->spinbox_mobileentities->setValue(initMob);
    ui->spinbox_hospitalcap->setValue(hospCap);

    ui->spinbox_testspertick->setValue(tpt);
    ui->spinbox_ticksuntilexpiration->setValue(tue);

    ui->spinbox_infectionchance->setValue(infChance);
    ui->spinbox_survivalchance->setValue(survChance);
    ui->spinbox_detectionchance->setValue(detectChance);

    ui->spinbox_influenceradius->setValue(infRadius);
    ui->checkbox_distancing->setEnabled(distancing);
    ui->spinbox_centrallocations->setValue(centralLocations);

    ui->spinbox_width->setValue(width);
    ui->spinbox_height->setValue(height);
    ui->spinbox_iterations->setValue(iterations);
    ui->spinbox_threads->setValue(thread);
}
