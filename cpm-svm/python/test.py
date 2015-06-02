import cython_svm
import numpy as np

X = np.array([[1, 0], [0, -1], [-1, 0], [0, 1]], dtype=np.float)
y = np.array([0, 0, 1, 1])

clf = cython_svm.mySVM()
clf.train(X, y, lambda_coef=1., epsilon_abs=0.0001, epsilon_tol=0.01, tMax=100)
pred = clf.predict(X)
print pred
