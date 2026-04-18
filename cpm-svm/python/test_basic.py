import numpy as np
import cpm_svm

# Минимальный тест для обучающей выборки с 2-мя классами

X = np.array([[1, 0], [0, -1], [-1, 0], [0, 1]], dtype=float)
y = np.array([0, 0, 1, 1])

clf = cpm_svm.CPM_SVM()
clf.fit(X, y)
pred = clf.predict(X)
print('actual    =', y)
print('predicted =', pred)