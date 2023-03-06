#include "two_spectrum_window.h"
#include "ui_two_spectrum_window.h"

Two_Spectrum_Window::Two_Spectrum_Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Two_Spectrum_Window)
{
    ui->setupUi(this);

    firstSignal = new Data_Holder(this);
    secondSignal = new Data_Holder(this);

    spectrump1plot = ui->Spectrum1;
    spectrump2plot = ui->Spectrum2;

    connect(this, &Two_Spectrum_Window::SendFilename1, firstSignal, &Data_Holder::ReceivingFilename);
    connect(this, &Two_Spectrum_Window::SendFilename2, secondSignal, &Data_Holder::ReceivingFilename);

    connect(this, &Two_Spectrum_Window::SignalToCalculateSpectrum1, firstSignal, &Data_Holder::Calculate_Spectrum);
    connect(this, &Two_Spectrum_Window::SignalToCalculateSpectrum2, secondSignal, &Data_Holder::Calculate_Spectrum);

}

Two_Spectrum_Window::~Two_Spectrum_Window()
{
    delete ui;
}

void Two_Spectrum_Window::on_Choose1stSignal_clicked()
{
    QString str;
    str = QFileDialog::getOpenFileName(this, "Chose the file", "C:\\", "Text Document (*.txt)");
    ui->FirstSignalPath->setText(str);
    emit SendFilename1(str);

}


void Two_Spectrum_Window::on_Choose2ndSignal_clicked()
{
    QString str;
    str = QFileDialog::getOpenFileName(this, "Chose the file", "C:\\", "Text Document (*.txt)");
    ui->SecondSignalPath->setText(str);
    emit SendFilename2(str);
}


void Two_Spectrum_Window::on_CalculateTwoSpectra_clicked()
{
    qDebug() << "Signals to calculate spectra of two signals are emited";
    emit SignalToCalculateSpectrum1();
    emit SignalToCalculateSpectrum2();
}


void Two_Spectrum_Window::on_Calculate1stSpectrum_clicked()
{
    qDebug() << "Signals to calculate spectrum of first signal is emited";
    emit SignalToCalculateSpectrum1();
}

void Two_Spectrum_Window::on_Calculate2ndSpectrum_clicked()
{
    qDebug() << "Signals to calculate spectrum of second signal is emited";
    emit SignalToCalculateSpectrum2();
}

void Two_Spectrum_Window::on_PlotTwoSpectrum_clicked()
{
    qDebug() << "spectrum plotting started";

    qDebug() << "first plot";
    spectrum1graph = ui->Spectrum1->addGraph();
    spectrum1graph->setData(firstSignal->GetSpectrumStepsValues(), firstSignal->GetSpectrumValues());
    spectrum1graph->rescaleAxes();

    spectrump1plot->xAxis->ticker()->setTickCount(10);
    spectrump1plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    spectrump1plot->replot();

    qDebug() << "second plot";
    spectrum2graph = ui->Spectrum2->addGraph();
    spectrum2graph->setData(secondSignal->GetSpectrumStepsValues(), secondSignal->GetSpectrumValues());
    spectrum2graph->rescaleAxes();

    spectrump2plot->xAxis->ticker()->setTickCount(10);
    spectrump2plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    spectrump2plot->replot();
    qDebug() << "Spectrum plots are ready";
}

void Two_Spectrum_Window::on_CloseButton_clicked()
{
    this->close();
}
