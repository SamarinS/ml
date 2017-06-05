#include <Python.h>
#include <numpy/arrayobject.h>

#include <iostream>
#include <cstdint>

#include "../cpm-svm/base.h"

static PyObject *SpamError;

static void setBetta(SvmData* svmData, const PyArrayObject* betta)
{
    for (npy_intp i = 0; i < betta->dimensions[0]; i++)
    {
        Vec vec(betta->dimensions[1]);
        for (Vec::size_type j = 0; j < vec.size(); j++)
        {
            vec[j] = *(double*)(betta->data + i*betta->strides[0] + j*betta->strides[1]);
        }
        svmData->betta.push_back(vec);
    }
}

static PyArrayObject* getBetta(const SvmData& svmData)
{
    int n_dimensions = 2;
    npy_intp dim1 = svmData.betta.size();
    npy_intp dim2 = svmData.betta[0].size();
    npy_intp dimensions[n_dimensions] = {dim1, dim2};
    PyArrayObject* obj = (PyArrayObject*)PyArray_SimpleNew(
        n_dimensions, dimensions, PyArray_DOUBLE);

    for (std::vector<Vec>::size_type i = 0;i<svmData.betta.size();i++)
    {
        auto vec_size = svmData.betta[i].size();
        for (Vec::size_type j = 0;j<vec_size;j++)
        {
            ((double*)obj->data)[i*vec_size+j] = svmData.betta[i][j];
        }
    }

    return obj;
}

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

    DenseData data(
        (const double*)X->data,
        X->dimensions[0],
        X->dimensions[1],
        X->strides[0],
        X->strides[1]
    );

    SvmParams params(lambda, epsilon_abs, epsilon_tol, tMax);
    SvmData svmData;
    trainSvm(data, (const long*)y->data, params, &svmData);

    auto betta = getBetta(svmData);
    return PyArray_Return(betta);
}

static PyObject* spam_fit_sparse(PyObject* self, PyObject* args)
{
    int rows_number;
    int cols_number;
    PyArrayObject* X_data;
    PyArrayObject* X_indices;
    PyArrayObject* X_indptr;
    PyArrayObject* y;
    double lambda;
    double epsilon_abs;
    double epsilon_tol;
    int tMax;

    if (!PyArg_ParseTuple(args, "iiO!O!O!O!dddi",
                          &rows_number,
                          &cols_number,
                          &PyArray_Type, &X_data,
                          &PyArray_Type, &X_indices,
                          &PyArray_Type, &X_indptr,
                          &PyArray_Type, &y, 
                          &lambda,
                          &epsilon_abs,
                          &epsilon_tol,
                          &tMax))
    {
        return NULL;
    }

    SparseData data(
        (const double*)X_data->data,
        rows_number,
        cols_number,
        (int*)X_indices->data,
        (int)X_indices->dimensions[0],
        (int*)X_indptr->data,
        (int)X_indptr->dimensions[0]
    );

    SvmParams params(lambda, epsilon_abs, epsilon_tol, tMax);
    SvmData svmData;
    trainSvm(data, (const long*)y->data, params, &svmData);

    auto betta = getBetta(svmData);
    return PyArray_Return(betta);
}

static PyObject* spam_predict(PyObject* self, PyObject* args)
{
    PyArrayObject* X;
    PyArrayObject* betta;
    int n_classes;

    if (!PyArg_ParseTuple(args, "O!O!i", 
                          &PyArray_Type, &X,
                          &PyArray_Type, &betta,
                          &n_classes))
    {
        return NULL;
    }

    DenseData data(
        (const double*)X->data,
        X->dimensions[0],
        X->dimensions[1],
        X->strides[0],
        X->strides[1]
    );

    int n_dimensions = 1;
    npy_intp dimensions[n_dimensions] = {X->dimensions[0]};
    PyArrayObject* obj = (PyArrayObject*)PyArray_SimpleNew(
        n_dimensions, dimensions, PyArray_LONG);

    SvmData svmData;
    setBetta(&svmData, betta);
    svmData.n_classes = n_classes;

    predict(data, (long*)obj->data, svmData);

    return PyArray_Return(obj);
}

static PyObject* spam_predict_sparse(PyObject* self, PyObject* args)
{
    int rows_number;
    int cols_number;
    PyArrayObject* X_data;
    PyArrayObject* X_indices;
    PyArrayObject* X_indptr;
    PyArrayObject* betta;
    int n_classes;

    if (!PyArg_ParseTuple(args, "iiO!O!O!O!i",
                          &rows_number,
                          &cols_number,
                          &PyArray_Type, &X_data,
                          &PyArray_Type, &X_indices,
                          &PyArray_Type, &X_indptr,
                          &PyArray_Type, &betta,
                          &n_classes))
    {
        return NULL;
    }

    SparseData data(
        (const double*)X_data->data,
        rows_number,
        cols_number,
        (int*)X_indices->data,
        (int)X_indices->dimensions[0],
        (int*)X_indptr->data,
        (int)X_indptr->dimensions[0]
    );

    int n_dimensions = 1;
    npy_intp dimensions[n_dimensions] = {(npy_intp)rows_number};
    PyArrayObject* obj = (PyArrayObject*)PyArray_SimpleNew(
        n_dimensions, dimensions, PyArray_LONG);

    SvmData svmData;
    setBetta(&svmData, betta);
    svmData.n_classes = n_classes;

    predict(data, (long*)obj->data, svmData);

    return PyArray_Return(obj);
}

static PyMethodDef SpamMethods[] = {
    {"fit", spam_fit, METH_VARARGS, "cpm-svm classifier: fit"},
    {"fit_sparse", spam_fit_sparse, METH_VARARGS, "cpm-svm classifier: fit sparse"},
    {"predict", spam_predict, METH_VARARGS, "cpm-svm classifier: predict"},
    {"predict_sparse", spam_predict_sparse, METH_VARARGS, "cpm-svm classifier: predict sparse"},
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