configure:
	mbed-tools configure -m NUCLEO_F401RE -t GCC_ARM
	cmake -S . -B cmake_build/NUCLEO_F401RE/develop/GCC_ARM -GNinja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
	# ln -sf cmake_build/NUCLEO_F401RE/develop/GCC_ARM/compile_commands.json

setup:
	mbed-tools configure -m NUCLEO_F401RE -t GCC_ARM
	cmake -S . -B cmake_build/NUCLEO_F401RE/develop/GCC_ARM -GNinja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
		-DCMAKE_CXX_FLAGS="-I/usr/local/opt/arm-gcc-bin@8/arm-none-eabi/include/c++/8.3.1 -I/usr/local/opt/arm-gcc-bin@8/arm-none-eabi/include -I/usr/local/opt/arm-gcc-bin@8/arm-none-eabi/include/c++/8.3.1/arm-none-eabi"
	cp cmake_build/NUCLEO_F401RE/develop/GCC_ARM/compile_commands.json .

build: # configure setup
	cmake --build cmake_build/NUCLEO_F401RE/develop/GCC_ARM

rebuild:
	mbed-tools compile -m NUCLEO_F401RE -t GCC_ARM --clean

write: build
	mbed-tools compile -m NUCLEO_F401RE -t GCC_ARM -f

run: write
	mbed-tools compile -m NUCLEO_F401RE -t GCC_ARM --sterm --baudrate 9600

all: setup run
	echo "done"

