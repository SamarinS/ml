from cpm_svm import CPM_SVM as cpm_svm
from sklearn import datasets
from sklearn.ensemble import RandomForestClassifier as rf
from sklearn.ensemble import GradientBoostingClassifier as gbt
from sklearn.model_selection import GridSearchCV
from sklearn.svm import SVC as svm

import numpy as np
import time

svm_params = [
        {'C': [1, 10, 100, 1000], 'kernel': ['linear']},
        {'C': [1, 10, 100, 1000], 'gamma': [0.001, 0.0001], 'kernel': ['rbf']},
    ]
cpm_svm_params = [{'lambda_coef': [1., 0.1, 0.01, 0.001]}]
rf_params = [{'n_estimators': [5, 20, 70, 250, 1000]}]
gbt_params = [{'n_estimators':[5, 20, 70, 250, 1000], 'learning_rate':[0.3, 0.8, 1.0]}]

class Data:
    def __init__(self, x_train, x_test, y_train, y_test):
        self.x_train = x_train
        self.x_test = x_test
        self.y_train = y_train
        self.y_test = y_test


def experiment(data, model, tuned_params, verbosity=100):
    clf = GridSearchCV(model(), tuned_params, cv=5, verbose=verbosity)
    clf.fit(data.x_train, data.y_train)
    
    start_time = time.time()
    model(**clf.best_params_).fit(data.x_train, data.y_train)
    exec_time = time.time() - start_time
    
    print("score:", clf.score(data.x_test, data.y_test))
    print("best_params:", clf.best_params_)
    print("time(sec):", exec_time)

def to_dense_data(data):
    return Data(data.x_train.todense(), data.y_train, data.x_test.todense(), data.y_test)

def split_data(X, y):
    from sklearn.model_selection import train_test_split
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.25, random_state=1)
    
    print("n_samples:", X.shape[0])
    print("n_vars", X.shape[1])
    print("n_classes", np.unique(y).shape[0])
    return Data(X_train, X_test, y_train, y_test)

def load_uci_data(name, d=','):
    name = '/home/sergey/uci_data/'+name  
    data = np.loadtxt(name, delimiter=d)
    print("dataset:", name)
    X = data[:,:-1]
    y = data[:,-1]
    return split_data(X, y)

def load_libsvm_data(name):
    from sklearn.datasets import load_svmlight_file
    
    name = '/home/sergey/libsvm_data/' + name
    X, y = load_svmlight_file(name)
    print("dataset:", name)
    return split_data(X, y)
    
data = load_libsvm_data('connect-4')
experiment(data, cpm_svm, cpm_svm_params)

