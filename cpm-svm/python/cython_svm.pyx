cimport svm
import numpy as np
cimport numpy as np


cdef class mySVM:
    cdef svm.SVM clf
    cpdef train(self, np.ndarray[np.float64_t, ndim=2] X, np.ndarray[np.int_t, ndim=1] y, 
                double lambda_coef, double epsilon_abs, double epsilon_tol, int tMax):
        self.clf.Train(<const double*>X.data, <const long*>y.data, X.shape[0], X.shape[1], X.strides[0], X.strides[1],
                        lambda_coef, epsilon_abs, epsilon_tol, tMax)
    cpdef np.ndarray[np.int_t, ndim=1] predict(self, np.ndarray[np.float64_t, ndim=2] X):
        cdef np.ndarray pred = np.zeros([X.shape[0]], dtype=np.int)
        self.clf.Predict(<const double*>X.data, <long*>pred.data, X.shape[0], X.shape[1], X.strides[0], X.strides[1])
        return pred
