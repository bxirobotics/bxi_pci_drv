BUILD_DIR ?= $(HOME)/.cache/bxi-build/pci-native

.PHONY: all
all:
	cmake -S . -B "$(BUILD_DIR)" $(FLAGS_USER)
	cmake --build "$(BUILD_DIR)" --parallel 4
