cdef extern from "src/svm.h":
    cdef cppclass SVM:
        void Train(const double* data, const long* resp, int n_samples, int n_vars,
               int row_step, int col_step,
               double lambda_coef, double epsilon_abs, double epsilon_tol, int tMax);
        void Predict(const double* data, long* pred,
                 int n_samples, int n_vars,
                 int row_step, int col_step) const;
