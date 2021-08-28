target = NUCLEO_F401RE

configure:
	mbed-tools configure -m $(target) -t GCC_ARM
	cmake -S . -B cmake_build/$(target)/develop/GCC_ARM -GNinja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

setup: # Setup For clangd completion
	mbed-tools configure -m $(target) -t GCC_ARM
	cmake -S . -B cmake_build/$(target)/develop/GCC_ARM -GNinja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
		-DCMAKE_CXX_FLAGS="-I/usr/local/opt/arm-gcc-bin@8/arm-none-eabi/include/c++/8.3.1 -I/usr/local/opt/arm-gcc-bin@8/arm-none-eabi/include -I/usr/local/opt/arm-gcc-bin@8/arm-none-eabi/include/c++/8.3.1/arm-none-eabi"
	cp cmake_build/$(target)/develop/GCC_ARM/compile_commands.json .

build: # configure setup
	cmake --build cmake_build/$(target)/develop/GCC_ARM

rebuild:
	mbed-tools compile -m $(target) -t GCC_ARM --clean

write: build
	mbed-tools compile -m $(target) -t GCC_ARM -f

run: write
	mbed-tools compile -m $(target) -t GCC_ARM --sterm --baudrate 9600

all: setup run
	echo "done"

