from sklearn.base import BaseEstimator, ClassifierMixin
from sklearn.utils import check_X_y, check_array
import numpy as np
import cython_svm

class CPM_SVM(BaseEstimator, ClassifierMixin):
    def __init__(self, lambda_coef=1., epsilon_tol=1e-3, epsilon_abs=0.01, max_iter=100):
        
        self.lambda_coef = lambda_coef
        self.epsilon_tol = epsilon_tol
        self.epsilon_abs = epsilon_abs
        self.max_iter = max_iter
    
    def fit(self, X, y):
        X, y = check_X_y(X, y, multi_output=True)
        self.classes_, y = np.unique(y, return_inverse=True)
        self.svm = cython_svm.mySVM()
        self.svm.train(X, y, self.lambda_coef, self.epsilon_tol, self.epsilon_abs, self.max_iter);
        return self
    
    def predict(self, X):
        X = check_array(X)
        y = self.svm.predict(X)
        return self.classes_.take(np.asarray(y, dtype=np.intp))
        
