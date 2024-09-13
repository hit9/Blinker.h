defalut: build

install:
	conan install . --output-folder=Build --build=missing -s compiler.cppstd=20 -s build_type=Release

cmake:
	cd Build && cmake .. \
		-DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake \
		-DCMAKE_BUILD_TYPE=Release \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=1

build: cmake
	cd Build && make

run:
	ctest --test-dir ./Build --output-on-failure

clean:
	make -C Build clean

.PHONY: build
