import matplotlib.pyplot as plt
from cpm_svm import CPM_SVM

def plot(X, y):
    red_x = []
    red_y = []

    green_x = []
    green_y = []

    blue_x = []
    blue_y = []

    for i in range(len(X)):
        if y[i] == 'red':
            red_x.append(X[i][0])
            red_y.append(X[i][1])
        elif y[i] == 'green':
            green_x.append(X[i][0])
            green_y.append(X[i][1])
        elif y[i] == 'blue':
            blue_x.append(X[i][0])
            blue_y.append(X[i][1])

    plt.plot(red_x, red_y, 'ro')
    plt.plot(green_x, green_y, 'go')
    plt.plot(blue_x, blue_y, 'bo')
    plt.show()

X = [[0, 1], [0.1, 1],
     [1, 1],
     [1, 0]]
actual = ['red', 'red', 'green', 'blue']

clf = CPM_SVM()
clf.fit(X, actual)
pred = clf.predict(X)

print("pred =", pred)
plot(X, pred)

