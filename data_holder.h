#ifndef DATA_HOLDER_H
#define DATA_HOLDER_H

#include <QObject>

#include <QDebug>

#include <vector>
#include <complex>
#include <cmath>

#include <QVector>
#include <QString>
#include <QFile>
#include <QTextStream>

class Data_Holder : public QObject
{
    Q_OBJECT


public:
    // Constructors (default, with filename) and destructor
    explicit Data_Holder(QObject *parent = nullptr);
    ~Data_Holder();

    // reading signal data from file
    void readDataFromFile();

    // setting filename from signal
    void SetFilename(QString str);

    // calculating frequency bins
    void FreqCalculation();

    // Getters for plotting singal
    // Signal data
    QVector<double> GetSamplesValues();
    // Time data
    QVector<double> GetTimeValues();
    // Spectrum data (spectrum bins values)
    QVector<double> GetSpectrumValues();
    // Spectrum steps
    QVector<double> GetSpectrumStepsValues();

public  slots:
    // Receive and Set filename, signal data ???Why not a Setter???
    void ReceivingFilename(QString str);

    // Receive signal to calculate spectrum
    void Calculate_Spectrum();

signals:

private slots:

private:
    // path to file with sasmples and time stamps
    QString filename;

    // signal DATA
    std::vector<double> x_time;
    std::vector<std::complex<double>> samples;
    std::vector<std::complex<double>> freq_bins;

    // test variables to use as flags
    bool samples_is_set = false;
    bool freq_is_set = false;
    bool filename_is_set = false;


    // private method to convert String values to Double in public methods readDataFromFile();
    void StringToDouble(QString& string, double& time, double& samples);
    bool CompareTwoDouble(double first, double second, double epsilon);

    // private method is used t find signal spectrum
    std::vector<std::complex<double>> FFT(std::vector<std::complex<double>>& samples);

    // private method forforming an samples array for FFT
    // std::vector<std::complex<double>> CuttingSamples(std::vector<std::complex<double>> samples, std::vector<double> x_time);


};

#endif // DATA_HOLDER_H
