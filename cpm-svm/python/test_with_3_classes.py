import os

import numpy as np
import matplotlib

if os.environ.get("DISPLAY", "") == "":
    matplotlib.use("Agg")

import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap
from cpm_svm import CPM_SVM

# Минимальный тест для обучающей выборки с 3-мя классами

def _show_or_save(filename: str):
    if os.environ.get("DISPLAY", "") == "":
        plt.savefig(filename, dpi=150, bbox_inches="tight")
        plt.close()
    else:
        plt.show()

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
    _show_or_save("points.png")


def plot_decision_regions(clf, X, y=None, pad=0.5, step=0.01, alpha=0.25, class_colors=None):
    X = np.asarray(X, dtype=np.float64)
    if X.ndim != 2 or X.shape[1] != 2:
        raise ValueError("plot_decision_regions expects X with shape (n_samples, 2)")

    if y is None:
        y = clf.predict(X)
    y = np.asarray(y)

    classes = list(clf.classes_)
    to_int = {c: i for i, c in enumerate(classes)}

    if class_colors is None:
        class_colors = {c: str(c) for c in classes}

    x0_min, x0_max = X[:, 0].min() - pad, X[:, 0].max() + pad
    x1_min, x1_max = X[:, 1].min() - pad, X[:, 1].max() + pad

    xx0, xx1 = np.meshgrid(
        np.arange(x0_min, x0_max + step, step),
        np.arange(x1_min, x1_max + step, step),
    )
    grid = np.c_[xx0.ravel(), xx1.ravel()]

    grid_pred = clf.predict(grid).reshape(xx0.shape)

    Z = np.vectorize(to_int.get)(grid_pred)

    region_cmap = ListedColormap([class_colors[c] for c in classes])
    plt.contourf(
        xx0,
        xx1,
        Z,
        alpha=alpha,
        levels=np.arange(len(classes) + 1) - 0.5,
        cmap=region_cmap,
    )

    for c in classes:
        mask = y == c
        if np.any(mask):
            plt.scatter(
                X[mask, 0],
                X[mask, 1],
                label=str(c),
                color=class_colors[c],
                edgecolors="k",
                s=60,
            )

    plt.legend(loc="best")
    _show_or_save("decision_regions.png")

X = [[0, 1], [0.1, 1],
     [1, 1],
     [1, 0]]
actual = ['red', 'red', 'green', 'blue']

clf = CPM_SVM()
clf.fit(X, actual)
pred = clf.predict(X)

print("actual    =", actual)
print("predicted =", pred)
plot(X, pred)
plot_decision_regions(clf, X, actual)

