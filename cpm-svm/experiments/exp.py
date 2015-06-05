import numpy as np

from cpm_svm import CPM_SVM as cpm_svm
from sklearn.svm import SVC as svm
from sklearn.ensemble import RandomForestClassifier as rf
from sklearn.ensemble import GradientBoostingClassifier as gbt

svm_params = [
        {'C': [1, 10, 100, 1000], 'kernel': ['linear']},
        {'C': [1, 10, 100, 1000], 'gamma': [0.001, 0.0001], 'kernel': ['rbf']},
    ]
cpm_svm_params = [{'lambda_coef': [1., 0.1, 0.01, 0.001, 0.0001, 0.00001]}]
rf_params = [{'n_estimators': [5, 20, 70, 250, 1000]}]
gbt_params = [{'n_estimators':[5, 20, 70, 250, 1000], 'learning_rate':[0.3, 0.8, 1.0]}]


def experiment(data, model, tuned_params, verbosity=100):
    from sklearn.grid_search import GridSearchCV
    import time
    
    X_train = data["X_train"]
    X_test = data["X_test"]
    y_train = data["y_train"]
    y_test = data["y_test"]
    
    clf = GridSearchCV(model(), tuned_params, cv=5, verbose=verbosity)
    clf.fit(X_train, y_train)
    
    start_time = time.time()
    model(**clf.best_params_).fit(X_train, y_train)
    exec_time = time.time() - start_time
    
    print "score:", clf.score(X_test, y_test)
    print "best_params:", clf.best_params_
    print "time(sec):", exec_time


def load_uci_data(name, d=','):
    from sklearn.cross_validation import train_test_split

    data = np.loadtxt(name, delimiter=d)
    X = data[:,:-1]
    y = data[:,-1]
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.25, random_state=1)
    current_result = [{"name":name, "n_samles":X.shape[0], "n_vars":X.shape[1], "n_classes":np.unique(y).shape[0]}]
    print "name = ", name
    print "n_samples = ", X.shape[0]
    print "n_vars = ", X.shape[1]
    print "n_classes = ", np.unique(y).shape[0]
    return {"X_train":X_train, "X_test":X_test, "y_train":y_train, "y_test":y_test}

def load_libsvm_data(name):
    from sklearn.datasets.svmlight_format import load_svmlight_file
    from sklearn.cross_validation import train_test_split
    
    return load_svmlight_file(name)
    
