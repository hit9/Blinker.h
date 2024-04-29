defalut: build

install-release:
	conan install . --output-folder=build --build=missing -s build_type=Release

install-debug:
	conan install . --output-folder=build --build=missing -s build_type=Debug

cmake-build-release:
	cd build && cmake .. \
		-DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake \
		-DCMAKE_BUILD_TYPE=Release \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=1

cmake-build-test:
	cd build && cmake .. \
		-DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake \
		-DCMAKE_BUILD_TYPE=Debug \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=1 \
		-DBLINKER_TEST=1

build: cmake-build
	cd build && make

build-example:
	cd build/example && make

build-test:
	cd build/tests && make

run-example: build-example
	./build/example/blinker_example

run-tests: build-test
	ctest --test-dir ./build/tests --output-on-failure

clean:
	make -C build clean

lint:
	cppcheck *.h --enable=warning,style,performance,portability --inline-suppr --language=c++

.PHONY: build build-test
