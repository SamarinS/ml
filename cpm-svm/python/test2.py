import cpm_svm
import numpy as np
from sklearn import datasets

#X = np.array([[1, 0], [0, -1], [-1, 0], [0, 1]], dtype=np.float)
#y = np.array([0, 0, 1, 1])

iris = datasets.load_iris()
perm = np.random.permutation(150)
X = iris.data
y = iris.target
X_train = X[perm[:120]]
y_train = y[perm[:120]]
X_test = X[perm[120:]]
y_test = y[perm[120:]]

clf = cpm_svm.CPM_SVM(lambda_coef=0.1, epsilon_abs=0.0001, epsilon_tol=0.01, max_iter=100)

clf.fit(X_train, y_train)

print y_test
print clf.predict(X_test)
print clf.score(X_test, y_test)
