all:
	g++ -std=c++11 -I/usr/include/python2.7 -shared -o spam.so -fPIC \
	../cpm-svm/data.cpp \
	../cpm-svm/base.cpp \
	../cpm-svm/svm.cpp \
	../cpm-svm/solve_qp.cpp \
	spammodule.c
clean:
	rm spam.so