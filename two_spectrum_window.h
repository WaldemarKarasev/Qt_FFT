#ifndef TWO_SPECTRUM_WINDOW_H
#define TWO_SPECTRUM_WINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QTimer>
#include <QtMath>
#include <QDebug>
#include <QString>

#include "qcustomplot.h"

#include "data_holder.h"


namespace Ui {
class Two_Spectrum_Window;
}

class Two_Spectrum_Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Two_Spectrum_Window(QWidget *parent = nullptr);
    ~Two_Spectrum_Window();

public slots:


signals:

    void SendFilename1(QString str);
    void SendFilename2(QString str);

    void SignalToCalculateSpectrum1();
    void SignalToCalculateSpectrum2();

private slots:
    void on_PlotTwoSpectrum_clicked();

    void on_Choose1stSignal_clicked();

    void on_Choose2ndSignal_clicked();

    void on_Calculate1stSpectrum_clicked();

    void on_Calculate2ndSpectrum_clicked();

    void on_CloseButton_clicked();





    void on_CalculateTwoSpectra_clicked();

private:
    Ui::Two_Spectrum_Window *ui;

    QCustomPlot* spectrump1plot;
    QCPGraph*    spectrum1graph;

    QCustomPlot* spectrump2plot;
    QCPGraph*    spectrum2graph;

    Data_Holder* firstSignal;
    Data_Holder* secondSignal;




};

#endif // TWO_SPECTRUM_WINDOW_H
