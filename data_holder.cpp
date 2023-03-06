#include "data_holder.h"

Data_Holder::Data_Holder(QObject* parent) : QObject(parent)
{
    qDebug() << "Data Holder created\n";
}


Data_Holder::~Data_Holder()
{
    qDebug() << "Data Holder destroyed\n";
}

// public functions
void Data_Holder::readDataFromFile()
{
    QFile file(filename);
    QString data;

    // reserving memory for signall data (file has 1440000 samples)
    x_time.reserve(1e6  + 4e5);
    samples.reserve(1e6 + 4e5);

    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Cannot open file";
        return;
    }
    else
    {
        QTextStream stream(&file);
        double time;
        double value;

        while(!stream.atEnd())
        {
            time = 0;
            value = 0;
            data = stream.readLine();
            StringToDouble(data, time, value);
            if(time > 0)
            {
                x_time.push_back(time);
                samples.push_back(std::complex<double>(value, 0));
            }
            else
                continue;

        }
//        data = file.readAll();
    }
    file.close();

    qDebug() << x_time[0];
    qDebug() << samples[0].real();
    qDebug() << samples[0].imag();
    qDebug() << "samples.size()" << samples.size();
    qDebug() << "x_time.size()" << x_time.size();


    // validate data
    samples_is_set = true;
}

void Data_Holder::SetFilename(QString str)
{
    filename = str;
}

void Data_Holder::FreqCalculation()
{
    bool flag = true;
    size_t i = 0;
    std::vector<std::complex<double>>::iterator iter1, iter2;

    qDebug() << "Start cutting samples to size of pow(2, ?)";
    qDebug() << samples.size();
    // Cuttin samples vector for better work of FFT algorithm, because FFT works with arrays
    // of length equal to the power of two

    size_t samp_size = samples.size();
    while (flag)
    {
        qDebug() << i;

        if(samp_size == 0)
        {
            // TODO: safety in this situation
            flag = false;
            break;
        }

        if(samp_size >= pow(2, i) && samp_size < pow(2, i+1))
        {
            iter1 = samples.begin() + pow(2,i);
            iter2 = samples.end();

            samples.erase(iter1, iter2);

            flag = false;
            break;
        }

        ++i;

    }

    qDebug() << samples.size();
    qDebug() << "Samples are cut, FFT is ready to start.";

    // Run the FFT algorithm
    freq_bins = FFT(samples);

    qDebug() << "FFT is finished computing";

}

QVector<double> Data_Holder::GetSamplesValues()
{
    // Defining conteiner for plot graph
    QVector<double> Y_sample_values;
    Y_sample_values.reserve(samples.size());

    for(size_t i = 0; i < samples.size(); ++i)
    {
        Y_sample_values.push_back(samples[i].real());
    }

    return Y_sample_values;
}

QVector<double> Data_Holder::GetTimeValues()
{
    QVector<double> X_time_values = QVector<double>::fromStdVector(x_time);
    return X_time_values;

}

QVector<double> Data_Holder::GetSpectrumValues()
{
    QVector<double> Y_Spectrum_values;
    Y_Spectrum_values.reserve(freq_bins.size());

    // normilize frequency bins values
    auto norm_value = freq_bins.size();
    for(size_t i = 0; i < freq_bins.size()/2; ++i)
    {
        // convert frequency bin value to magnitude
        // we take only half of values from freq_bins because of Nyquist Sampling Frequency/2
        double mag = std::abs(freq_bins[i].operator/=(norm_value));
        //double mag = freq_bins[i].operator/=(norm_value).real();

        // push back converted value of one frequency bin
        Y_Spectrum_values.push_back(mag);
    }

    qDebug() << Y_Spectrum_values[Y_Spectrum_values.size() - 1];
    return Y_Spectrum_values;

}

QVector<double> Data_Holder::GetSpectrumStepsValues()
{
    QVector<double> freq_steps;
    freq_steps.reserve(freq_bins.size()/2);

    double sampling_freq = 8000;
    auto num_of_samples = samples.size();
    double freq_resolution = sampling_freq/num_of_samples;

    for(size_t i = 0; i < freq_bins.size()/2; ++i)
    {
        freq_steps.push_back(i*freq_resolution); // rotation/min
    }

    qDebug() << freq_steps[freq_steps.size()-1];
    return freq_steps;

}


// public slots
void Data_Holder::ReceivingFilename(QString str)
{
    SetFilename(str);

    // Set the Signal Data
    readDataFromFile();

    //  only for debugging
    qDebug() << "Data is set! Now we can plot signal";

}

void Data_Holder::Calculate_Spectrum()
{
    qDebug() << "The spectrum began to be calculated after pressing the button";
    FreqCalculation();
}


// private functions
void Data_Holder::StringToDouble(QString &string, double &time, double &samples)
{
    QStringList list = string.split(' ', QString::SkipEmptyParts);

    for (const QString& it : qAsConst(list))
    {
        if(time == 0)
        {
            time = it.toDouble();
        }
        else
            samples = it.toDouble();
    }
}

bool Data_Holder::CompareTwoDouble(double first, double second, double epsilon=0.0001)
{
    if(std::fabs(first-second) < epsilon)
        return true; // they are same

    return false; // they are not the same
}



// The CORE of application. The MAIN algorithm.
std::vector<std::complex<double>> Data_Holder::FFT(std::vector<std::complex<double>>& samples)
{
    // Find the number of samples we have
        int N = samples.size();

        // Execute the end ofo the recursive even/odd splits once we only have one sample
        if(N == 1)
            return samples;

        // Splitt the samples into even and odd subsums
        // Find half the total number of samples
        int M = N / 2;

        // Declare an even and an odd complex vector
        std::vector<std::complex<double>> Xeven(M, 0);
        std::vector<std::complex<double>> Xodd(M, 0);

        // Input the even and odd samples into respective vectors
        for (int i = 0; i < M; ++i)
        {
            Xeven[i] = samples[2*i];
            Xodd[i]  = samples[2*i + 1];
        }

        // Perform the recursive FFT operation on the odd and even sides
        std::vector<std::complex<double>> Feven(M, 0);
        Feven = FFT(Xeven);

        std::vector<std::complex<double>> Fodd(M, 0);
        Fodd = FFT(Xodd);

        //----------END RECURSION----------//
        // Declare vector of frequency bins
        std::vector<std::complex<double>> freqbins(N, 0);

        // Define pi = 3.14159265
        double pi = 3.14159265;

        // Combinethe values found
        for (int k = 0; k < N / 2; ++k)
        {
            //For each split set, we need to multiply a k-dependent complex
            // numberr by the odd subsum
            std::complex<double> cmplxExponential = std::polar(1.0, -2*pi*k / N ) * Fodd[k];
            freqbins[k] = Feven[k] + cmplxExponential;

            // Everytime you add pi, exponential changes sign
            freqbins[k + N/2] = Feven[k] - cmplxExponential;
        }

        return freqbins;
}


