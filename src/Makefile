CC=gcc -std=c11
CC1=clang
#CFLAGS_FOR_FUNC=-g
CFLAGS_FOR_FUNC=-g -Wall -Wextra -Werror 
CFLAGS=
ADD_CFLAGS=-g
#ADD_CFLAGS=-g -Wno-unused-parameter
LIBS=-lcheck
SOURCES= s21_3dviewer.c s21_matrix.c s21_parser.c
OBJECTS=$(SOURCES:.c=.o)
PATH-TO-CHECK=
PATH-TO-LIB-CHECK=
PATH-TO-QT=Qt-project-v1/3D-Viewer-v1/
GCOV_TEST = gcov_test
GCOV_DIR = report
UNAME_S := $(shell uname -s)
TEST_TARGET = s21_3dviewer_test

EXECUTABLE= check test gcov_report dvi dist install


all: $(EXECUTABLE)

install:
	rm -rf temp
	rm -rf ../../s21_3DViewerApp
	mkdir temp
	cd temp; qmake ../Qt-project-v1/3D-Viewer-v1/3D-Viewer-v1.pro
	cd temp; make
	cd temp; make clean
	mkdir ../../s21_3DViewerApp
ifeq ($(UNAME_S),Linux)
	cp temp/3D-Viewer-v1 ../../s21_3DViewerApp/3D-Viewer-v1
else
	cp temp/3D-Viewer-v1.app/Contents/MacOS/3D-Viewer-v1 ../../s21_3DViewerApp/3D-Viewer-v1
endif
	cp obj-images/*.obj ../../s21_3DViewerApp/
	rm -rf temp
	../../s21_3DViewerApp/3D-Viewer-v1

uninstall:
	rm -rf temp
	rm -rf ../../s21_3DViewerApp

dist:
	rm -rf ../../s21_3DViewerApp-tar
	mkdir ../../s21_3DViewerApp-tar
	tar -cf ../../s21_3DViewerApp-tar/s21_3DViewer_v1.0.tar Makefile $(PATH-TO-QT)*.*

dvi:
	rm -rf ../../s21_3DViewerPdf
	mkdir ../../s21_3DViewerPdf
	cp s21_3D-Viewer-v1.pdf ../../s21_3DViewerPdf/s21_3D-Viewer-v1.pdf


doit_for_3dviewer:$(SOURCES) s21_3dviewer.h
	$(foreach var,$(SOURCES), $(CC) $(CFLAGS_FOR_FUNC) -c $(var);)


s21_3dviewer.a: doit_for_3dviewer
	ar rcs s21_3dviewer.a $(OBJECTS)
	cp s21_3dviewer.a libs21_3dviewer.a
	rm lib*.a *.o

test: s21_3dviewer_test
	rm *.o
	./s21_3dviewer_test

mem_test: s21_3dviewer_test
	rm *.o
ifeq ($(UNAME_S),Linux)
	valgrind -s --tool=memcheck --leak-check=full ./$(TEST_TARGET)
else
	CK_FORK=no leaks -atExit -- ./$(TEST_TARGET)
endif


s21_3dviewer_test: s21_3dviewer.a s21_3dviewer_test.o
	$(CC) -o s21_3dviewer_test  s21_3dviewer_test.o s21_3dviewer.a $(PATH-TO-CHECK) $(PATH-TO-LIB-CHECK) -lcheck -lm

s21_3dviewer_test.o: s21_3dviewer_test.c s21_3dviewer.h
	$(CC) $(CFLAGS) -c s21_3dviewer_test.c -lcheck -lm $(PATH-TO-CHECK)

gcov_report: 
#echo '$(UNAME_S)'
ifeq ($(UNAME_S),Linux)
	$(CC) $(CFLAGS) $(ADD_CFLAGS) --coverage s21_3dviewer_test.c $(SOURCES) -o s21_3dviewer_test $(PATH-TO-CHECK) $(PATH-TO-LIB-CHECK) -lcheck -lm
	./s21_3dviewer_test
	lcov -t "s21_3dviewer_test" -o s21_3dviewer_test.info -c -d .  
	genhtml -o report s21_3dviewer_test.info
	xdg-open ./report/index.html
	rm -rf *.gcda *.gcno s21_3dviewer_test s21_3dviewer_test.info
else
	$(CC) $(CFLAGS) $(ADD_CFLAGS) --coverage s21_3dviewer_test.c $(SOURCES) -o s21_3dviewer_test `pkg-config --cflags --libs check`
	./s21_3dviewer_test
	lcov -t "s21_3dviewer_test" -o s21_3dviewer_test.info -c -d .   
	genhtml -o report s21_3dviewer_test.info
	open ./report/index.html
	rm -rf *.gcda *.gcno s21_3dviewer_test s21_3dviewer_test.info
endif

clean_all: clean clean_gcov

clean:
	rm *.o

clean_gcov:
	rm -rf ./*.gcda ./*.gcno ./*.info ./$(GCOV_TEST) ./$(GCOV_DIR)

check:
	python3 ../materials/linters/cpplint.py --extensions=c --verbose=5 *.c *.h
	cppcheck --enable=all --suppress=missingIncludeSystem --check-config *.h *.c
#CK_FORK=no leaks -atExit -- ./$(TEST_TARGET)