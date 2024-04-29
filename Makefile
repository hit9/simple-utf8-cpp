defalut: build

install-release:
	conan install . --output-folder=build --build=missing -s build_type=Release

install-debug:
	conan install . --output-folder=build --build=missing -s build_type=Debug

cmake-build:
	cd build && cmake .. \
		-DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake \
		-DCMAKE_BUILD_TYPE=Release \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=1

cmake-build-test:
	cd build && cmake .. \
		-DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake \
		-DCMAKE_BUILD_TYPE=Debug \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=1 \
		-DSIMPLE_UTF8_TEST=1

cmake-build-test-release-mode:
	cd build && cmake .. \
		-DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake \
		-DCMAKE_BUILD_TYPE=Release \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=1 \
		-DSIMPLE_UTF8_TEST=1

build: cmake-build
	cd build && make

build-example:
	cd build/example && make example

build-test:
	cd build/tests && make tests

build-benchmark:
	cd build/tests && make benchmark

run-example: build-example
	./build/example/example

run-tests:
	cmake --build build --target runtests

run-benchmark:
	cmake --build build --target runbenchmark

clean:
	make -C build clean

.PHONY: build build-test
