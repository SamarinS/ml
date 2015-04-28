#include "svm.h"
#include "data.h"

#include <iostream>


#include "solve_qp.h"
#include "timer.h"

using namespace std;


int Main(int argc, char* argv[]);


int main(int argc, char* argv[])
{
    return Main(argc, argv);
}



int Main(int argc, char* argv[])
{
    if(argc!=8)
    {
        cout << "Usage: cpm-svm.exe <data_filename> <train_portion> <mix_seed> <lambda>"
                " <epsilon_abs> <epsilon_tol> <max_iter>" << endl;
        return 1;
    }
    const char* dataPathStr = argv[1];
    const char* trainPortionStr = argv[2];
    const char* seedStr = argv[3];
    const char* lambdaStr = argv[4];
    const char* epsilonAbsStr = argv[5];
    const char* epsilonTolStr = argv[6];
    const char* maxIterStr = argv[7];


    cout << "Loading data from file \"" << dataPathStr << "\" ..." << endl;
    Data data;
    data.ReadFile(dataPathStr);
    if(!data.IsLoaded())
    {
        cout << "Error while loading data" << endl;
        return 1;
    }
    cout << "ok" << endl;

    cout << endl << "Data set information:" << endl;
    cout << "\t Number of variables: " << data.VarNumber() << endl;
    cout << "\t Number of samples: " <<
            data.TestSampleIdx().size() + data.TrainSampleIdx().size() << endl;
    cout << "\t Number of classes: " << data.LabelsNumber() << endl;

    float trainPortion = float(atof(trainPortionStr));
    data.SetTrainTestSplit(trainPortion);
    cout << "\t " << trainPortion*100 << "% of data is used for training" << endl;
    cout << "\t Train sample count: " << data.TrainSampleIdx().size() << endl;
    cout << "\t Test sample count: " << data.TestSampleIdx().size() << endl;


    int seed = atoi(seedStr);
    if(seed>=0)
    {
        srand(unsigned(seed));
        data.Mix();
        cout << "\t Data mixed with seed=" << seed << endl;
    }
    else
    {
        cout << "\t Data not mixed" << endl;
    }



    Real lambda = Real(atof(lambdaStr));
    Real epsilon_abs = Real(atof(epsilonAbsStr));
    Real epsilon_tol = Real(atof(epsilonTolStr));
    int maxIter = atoi(maxIterStr);

    cout << endl;
    cout << "SVM parameters:" << endl;
    cout << "\t Lambda = " << lambda << endl;
    cout << "\t Abs epsilon = " << epsilon_abs << endl;
    cout << "\t Tol epsilon = " << epsilon_tol << endl;
    cout << "\t Max number of iterations = " << maxIter << endl;


    cout << endl << "Svm training..." << endl;
    SVM svm;

    long long time_svm = -gettimeus();
    svm.Train(data, lambda, epsilon_abs, epsilon_tol, maxIter);
    time_svm += gettimeus();

    cout << "Svm training completed." << endl;
    cout << "svm training time: " << double(time_svm)/1000000 << " seconds" << endl;
    cout << "Train accuracy: " << (1.0-svm.CalcError(data, SVM::TRAIN))*100 << "%" << endl;

    if(data.TestSampleIdx().size()!=0)
    {
        cout << "Test  accuracy: " << (1.0-svm.CalcError(data, SVM::TEST))*100 << "%" << endl;
    }

    return 0;
}

