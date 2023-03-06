#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <vector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    successful_launch = new Data_Holder(this);
    failed_launch = new Data_Holder(this);

    signal_plot   = ui->Signal;
    spectrum_plot = ui->Spectrum;


    connect(this, &MainWindow::SendFilename, successful_launch, &Data_Holder::ReceivingFilename);
    connect(this, &MainWindow::SignalToCalculateSpectrum, successful_launch, &Data_Holder::Calculate_Spectrum);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_FindThePath_clicked()
{
    QString str;
    str = QFileDialog::getOpenFileName(this, "Chose the file", "C:\\", "Text Document (*.txt)");
    ui->PathToFile->setText(str);
    emit SendFilename(str);
}


void MainWindow::on_PlotSignal_clicked()
{
    signal_graph = ui->Signal->addGraph();
    signal_graph->setData(successful_launch->GetTimeValues(), successful_launch->GetSamplesValues());
    signal_graph->rescaleAxes();

    signal_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    signal_plot->replot();

    qDebug() << "signal plot is ready";
}



void MainWindow::on_CalculateSpectrum_clicked()
{
    qDebug() << "Signal to calculate Spectrum is emited";
    emit SignalToCalculateSpectrum();
}

void MainWindow::on_PlotSpectrum_clicked()
{
    qDebug() << "spectrum plotting started";

    spectrum_graph = ui->Spectrum->addGraph();
    spectrum_graph->setData(successful_launch->GetSpectrumStepsValues(), successful_launch->GetSpectrumValues());
    spectrum_graph->rescaleAxes();

    spectrum_plot->xAxis->ticker()->setTickCount(10);
    spectrum_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    spectrum_plot->replot();

    qDebug() << "Spectrum plot is ready";
}





void MainWindow::on_TwoSpectrumWindow_clicked()
{
    TwoSpectrumWindow = new Two_Spectrum_Window(this);
    TwoSpectrumWindow->show();
}


void MainWindow::on_SpectrumComparisonWindow_clicked()
{

}


void MainWindow::on_CloseButton_clicked()
{
    this->close();
}

