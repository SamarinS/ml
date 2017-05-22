import numpy as np
import cpm_svm

X = np.array([[1, 0], [0, -1], [-1, 0], [0, 1]], dtype=np.float)
y = np.array([0, 0, 1, 1])

clf = cpm_svm.CPM_SVM()
clf.fit(X, y)
pred = clf.predict(X)
print pred
