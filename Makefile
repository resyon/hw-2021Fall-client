run: CMakeLists.txt
	cd utility && ./run.sh

install:
	sudo ./utility/install-oatpp-modules.sh

clean:
	rm -rf ./build
