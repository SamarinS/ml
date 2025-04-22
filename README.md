# ml

## cpm-svm project

### Build
Need install (tested with Ubuntu 20.04):
1. Boost: `sudo apt-get install libboost-all-dev`
2. python3-numpy package: `sudo apt-get install python3-numpy`
3. Python3 venv: `sudo apt install python3.12-venv`
      1. `python3 -m venv sklearn-env`
      2. `source sklearn-env/bin/activate`
      3. `pip3 install -U scikit-learn`
      4. `python3 -m pip show scikit-learn`
4. For test_with_3_classes.py test:
      1. `python3 -m pip install matplotlib`
      2. `sudo apt-get install python3-tk`
5. CMake: `sudo apt  install cmake`

Build and run test script:

0. `source sklearn-env/bin/activate`
1. `cd cpm-svm`
2. `mkdir build`
3. `cd build`
4. `cmake ..`
5. `make`
6. `cd ../python/`
7. `ln -s ../build/python/svmmodule.so svmmodule.so`
8. Check: `python3 test_basic.py`
