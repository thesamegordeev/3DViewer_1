CC 			= gcc
CFLAGS 		= -std=c11 -Wall -Werror -Wextra
BACK_P 		= 3D_Viewer/back/
SOURCES 	= $(wildcard 3D_Viewer/back/*.c)
OBJECTS 	= $(patsubst %.c, %.o, $(SOURCES))
STATIC_LIB	= 3D_Viewer.a
TEST_LIBS=$(shell pkg-config --cflags --libs check)


all: install

install:
	rm -rf build
	mkdir -vp build
	cd build && cmake ../3D_Viewer
	cd build && $(MAKE)

uninstall: clean
	rm -rf 3D_Viewer/CMakeLists.txt.user
	rm -rf 3D_Viewer/build
	rm -rf build

.gcov_flag:
	$(eval CFLAGS += --coverage)

dist: 
	tar -czvf 3D_Viewer.tar.gz 3D_Viewer Doxyfile Makefile
## tar -xzvf 3D_Viewer.tar.gz РАЗАРХИВИРОВАНИЕ

dvi:
	rm -rf Documentation
	doxygen
	open Documentation/html/index.html


gcov_report: clean .gcov_flag tests
	mkdir -p gcov
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory gcov
	rm -rf $(BACK_P)*.gcno $(BACK_P)*.gcda $(BACK_P)*.gcov *.gcno *.gcda *.gcov
	open gcov/index.html

$(STATIC_LIB): clean $(OBJECTS)
	ar -rcs $(STATIC_LIB) $(OBJECTS)
	ranlib $(STATIC_LIB)
	rm -f $(BACK_P)*.o


tests: clean $(STATIC_LIB)
	$(CC) $(CFLAGS) Tests/*.c -o test $(STATIC_LIB) $(TEST_LIBS)
	./test

valgrind:
	CK_FORK=no valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./test

clean:
	rm -rf Documentation test gcov build install screencap.gif 3D_Viewer.tar.gz
	rm -rf $(BACK_P)*.o *.a *.gcda *.gcno *.gch *.pdf *.tar rep.info test.info test.dSYM coverage.info 3D_Viewer/back/.clang-format

style:
	cp ../materials/linters/.clang-format 3D_Viewer/back/
	cd 3D_Viewer/back/ && clang-format -n *.*
