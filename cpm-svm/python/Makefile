CFLAGS=-std=c++11 -I/usr/include/python2.7 -shared -fPIC

ifeq (true, $(BMRM_INFO))
  CFLAGS += -DBMRM_INFO
endif

all:
	g++ $(CFLAGS) -o spam.so \
	../cpm-svm/data.cpp \
	../cpm-svm/base.cpp \
	../cpm-svm/svm.cpp \
	../cpm-svm/solve_qp.cpp \
	spammodule.c
clean:
	rm spam.so
