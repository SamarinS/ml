from sklearn.base import BaseEstimator, ClassifierMixin
from sklearn.utils import check_X_y, check_array
import numpy as np
import spam

class CPM_SVM(BaseEstimator, ClassifierMixin):
    def __init__(self, lambda_coef=0.01, epsilon_tol=1e-3, epsilon_abs=0.01, max_iter=100):
        
        self.lambda_coef = lambda_coef
        self.epsilon_tol = epsilon_tol
        self.epsilon_abs = epsilon_abs
        self.max_iter = max_iter
    
    def fit(self, X, y):
        X, y = check_X_y(X, y)
        X = np.asarray(X, dtype=np.float64, order='C')

        if issubclass(y.dtype.type, np.floating) == True:
            for label in y:
                if label.is_integer() == False:
                    raise ValueError("Unknown label type: labels shouldn't be floating point numbers with non-zero fractional part")

        self.classes_, y = np.unique(y, return_inverse=True)

        if len(self.classes_) < 2:
            raise ValueError(
                "The number of classes has to be greater than one; got %d"
                % len(self.classes_))

        self.betta_ = spam.fit(X, y,
            self.lambda_coef,
            self.epsilon_abs,
            self.epsilon_tol,
            self.max_iter)

        return self
    
    def predict(self, X):
        if hasattr(self, 'betta_') == False:
            raise ValueError("The classifier is not fitted yet. Please call 'fit' with appropriate arguments before using this method.")

        X = check_array(X)
        X = np.asarray(X, dtype=np.float64, order='C')

        if X.shape[1] != self.betta_.shape[1]:
            raise ValueError(
                "The number of X columns has to be equal to the number of features (%d); got %d"
                % (self.betta_.shape[1], X.shape[1]))

        y = spam.predict(X, self.betta_, len(self.classes_))

        return self.classes_.take(np.asarray(y, dtype=np.intp))