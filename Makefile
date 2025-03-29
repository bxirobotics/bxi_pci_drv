BUILD_DIR = ./build

all:buildp
	@rm $(BUILD_DIR)/bin/* -rf
	@cd $(BUILD_DIR);make -j4 -s
clean:
	@rm $(BUILD_DIR) -rf
buildp:
	@$(shell if [ ! -e $(BUILD_DIR) ]; then mkdir -p $(BUILD_DIR);fi)
	@cd $(BUILD_DIR);cmake .. $(FLAGS_USER)