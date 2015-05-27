from sklearn.base import BaseEstimator, ClassifierMixin
from sklearn.utils import check_X_y, check_array
import numpy as np

class CPM_SVM(BaseEstimator, ClassifierMixin):
    def __init__(self, lambda_coef=1., epsilon_tol=1e-3, epsilon_abs=0., max_iter=-1):
        
        self.lambda_coef = lambda_coef
        self.epsilon_tol = epsilon_tol
        self.epsilon_abs = epsilon_abs
        self.max_iter = max_iter
    
    def fit(self, X, y):
        X, y = check_X_y(X, y, "csr", multi_output=True)
        self.classes_, y = np.unique(y, return_inverse=True)
        #self.betta_ = np.ones((X.shape[0], 1))
        return self
    
    def predict(self, X):
        X = check_array(X, "csr")
        y = np.zeros(X.shape[0])
        return self.classes_.take(np.asarray(y, dtype=np.intp))
        