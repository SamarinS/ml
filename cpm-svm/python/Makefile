all:
	g++ -std=c++11 -I/usr/include/python2.7 ../cpm-svm/data.cpp ../cpm-svm/svm.cpp ../cpm-svm/solve_qp.cpp -shared -o spam.so -fPIC spammodule.c
clean:
	rm spam.so