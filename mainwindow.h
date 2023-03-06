#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QTimer>
#include <QtMath>
#include <QDebug>
#include <QString>

#include "qcustomplot.h"

#include "data_holder.h"
#include "two_spectrum_window.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:



signals:

    void SendFilename(QString str);
    void SignalToCalculateSpectrum();

private slots:

    void on_FindThePath_clicked();

    void on_PlotSignal_clicked();

    void on_PlotSpectrum_clicked();

    void on_CalculateSpectrum_clicked();



    void on_TwoSpectrumWindow_clicked();

    void on_SpectrumComparisonWindow_clicked();

    void on_CloseButton_clicked();

private:
    Ui::MainWindow *ui;

    QCustomPlot* signal_plot;
    QCPGraph* signal_graph;

    QCustomPlot* spectrum_plot;
    QCPGraph* spectrum_graph;

    Data_Holder* successful_launch;
    Data_Holder* failed_launch;

    Two_Spectrum_Window* TwoSpectrumWindow;


signals:


};
#endif // MAINWINDOW_H
