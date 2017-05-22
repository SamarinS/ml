#include <Python.h>
#include <numpy/arrayobject.h>

#include <iostream>
#include <cstdint>

#include "../cpm-svm/svm.h"

SVM svm;

static PyObject *SpamError;

static PyObject* spam_fit(PyObject* self, PyObject* args)
{
    PyArrayObject* X;
    PyArrayObject* y;
    double lambda;
    double epsilon_abs;
    double epsilon_tol;
    int tMax;

    if (!PyArg_ParseTuple(args, "O!O!dddi", 
                          &PyArray_Type, &X,
                          &PyArray_Type, &y, 
                          &lambda,
                          &epsilon_abs,
                          &epsilon_tol,
                          &tMax))
    {
        return NULL;
    }

    BaseData* data = new DenseData(
        (const double*)X->data,
        X->dimensions[0],
        X->dimensions[1],
        X->strides[0],
        X->strides[1]
    );

    svm.Train(*(DenseData*)data, (const long*)y->data,
              lambda, epsilon_abs, epsilon_tol, tMax);

    return Py_None;
}

static PyObject* spam_predict(PyObject* self, PyObject* args)
{
    PyArrayObject* X;

    if (!PyArg_ParseTuple(args, "O!", 
                          &PyArray_Type, &X))
    {
        return NULL;
    }

    BaseData* data = new DenseData(
        (const double*)X->data,
        X->dimensions[0],
        X->dimensions[1],
        X->strides[0],
        X->strides[1]
    );

    int n_dimensions = 1;
    int dimensions[n_dimensions] = {X->dimensions[0]};
    PyArrayObject* obj = (PyArrayObject*)PyArray_FromDims(
        n_dimensions, dimensions, PyArray_LONG);

    svm.Predict(*(DenseData*)data, (long*)obj->data);

    return PyArray_Return(obj);
}

static PyMethodDef SpamMethods[] = {
    {"fit", spam_fit, METH_VARARGS, "cpm-svm classifier: fit"},
    {"predict", spam_predict, METH_VARARGS, "cpm-svm classifier: predict"},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

PyMODINIT_FUNC
initspam(void)
{
    PyObject *m;

    m = Py_InitModule("spam", SpamMethods);
    if (m == NULL)
        return;

    import_array();

    SpamError = PyErr_NewException("spam.error", NULL, NULL);
    Py_INCREF(SpamError);
    PyModule_AddObject(m, "error", SpamError);
}