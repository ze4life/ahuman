.PHONY: clean All

All:
	@echo ----------Building project:[ aiapi - Debug ]----------
	@"mingw32-make.exe"  -j 2 -f "aiapi.mk"
	@echo ----------Building project:[ fann - Debug ]----------
	@"mingw32-make.exe"  -j 2 -f "fann.mk"
	@echo ----------Building project:[ generic - Debug ]----------
	@"mingw32-make.exe"  -j 2 -f "generic.mk"
	@echo ----------Building project:[ moddb - Debug ]----------
	@"mingw32-make.exe"  -j 2 -f "moddb.mk"
	@echo ----------Building project:[ modheart - Debug ]----------
	@"mingw32-make.exe"  -j 2 -f "modheart.mk"
	@echo ----------Building project:[ modhtm - Debug ]----------
	@"mingw32-make.exe"  -j 2 -f "modhtm.mk"
	@echo ----------Building project:[ modio - Debug ]----------
	@"mingw32-make.exe"  -j 2 -f "modio.mk"
	@echo ----------Building project:[ modknowledge - Debug ]----------
	@"mingw32-make.exe"  -j 2 -f "modknowledge.mk"
	@echo ----------Building project:[ modmedia - Debug ]----------
	@"mingw32-make.exe"  -j 2 -f "modmedia.mk"
	@echo ----------Building project:[ modmind - Debug ]----------
	@"mingw32-make.exe"  -j 2 -f "modmind.mk"
	@echo ----------Building project:[ modnn - Debug ]----------
	@"mingw32-make.exe"  -j 2 -f "modnn.mk"
	@echo ----------Building project:[ aiengine - Debug ]----------
	@"mingw32-make.exe"  -j 2 -f "aiengine.mk"
clean:
	@echo ----------Cleaning project:[ aiapi - Debug ]----------
	@"mingw32-make.exe"  -j 2 -f "aiapi.mk"  clean
	@echo ----------Cleaning project:[ fann - Debug ]----------
	@"mingw32-make.exe"  -j 2 -f "fann.mk"  clean
	@echo ----------Cleaning project:[ generic - Debug ]----------
	@"mingw32-make.exe"  -j 2 -f "generic.mk"  clean
	@echo ----------Cleaning project:[ moddb - Debug ]----------
	@"mingw32-make.exe"  -j 2 -f "moddb.mk"  clean
	@echo ----------Cleaning project:[ modheart - Debug ]----------
	@"mingw32-make.exe"  -j 2 -f "modheart.mk"  clean
	@echo ----------Cleaning project:[ modhtm - Debug ]----------
	@"mingw32-make.exe"  -j 2 -f "modhtm.mk"  clean
	@echo ----------Cleaning project:[ modio - Debug ]----------
	@"mingw32-make.exe"  -j 2 -f "modio.mk"  clean
	@echo ----------Cleaning project:[ modknowledge - Debug ]----------
	@"mingw32-make.exe"  -j 2 -f "modknowledge.mk"  clean
	@echo ----------Cleaning project:[ modmedia - Debug ]----------
	@"mingw32-make.exe"  -j 2 -f "modmedia.mk"  clean
	@echo ----------Cleaning project:[ modmind - Debug ]----------
	@"mingw32-make.exe"  -j 2 -f "modmind.mk"  clean
	@echo ----------Cleaning project:[ modnn - Debug ]----------
	@"mingw32-make.exe"  -j 2 -f "modnn.mk"  clean
	@echo ----------Cleaning project:[ aiengine - Debug ]----------
	@"mingw32-make.exe"  -j 2 -f "aiengine.mk" clean
