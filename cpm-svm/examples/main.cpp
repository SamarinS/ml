#include <iostream>

#include "../svm/dense_data.h"
#include "../svm/sparse_data.h"

const std::string DATA_FILENAME_STR = "data-filename";
const std::string TRAIN_PORTION_STR = "train-portion";
const std::string MIX_SEED_STR = "mix-seed";
const std::string LAMBDA_STR = "lambda";
const std::string EPSILON_ABS_STR = "epsilon-abs";
const std::string EPSILON_TOL_STR = "epsilon-tol";
const std::string MAX_ITER_STR = "max-iter";

void usage(const char* exe_path)
{
    std::cerr << "Usage: " << exe_path << " " << DATA_FILENAME_STR <<
        " [--" << TRAIN_PORTION_STR << "]" <<
        " [--" << MIX_SEED_STR << "]" <<
        " [--" << LAMBDA_STR << "]" <<
        " [--" << EPSILON_ABS_STR << "]" <<
        " [--" << EPSILON_TOL_STR << "]" <<
        " [--" << MAX_ITER_STR << "]" << std::endl;
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        usage(argv[0]);
        return 1;
    }

    auto filename = argv[1];

    DenseData* data = DenseData::LoadFromFile(filename);
    if (data == nullptr)
    {
        std::cerr << "Error: unable to load data from " << filename << std::endl;
        return 1;
    }

    // ToDo: implement svm training and scoring on the data loaded

    delete data;
}