.PHONY: clean All

All:
	@echo ----------Building project:[ modmedia - Debug ]----------
	@"mingw32-make.exe"  -j 2 -f "modmedia.mk"
clean:
	@echo ----------Cleaning project:[ modmedia - Debug ]----------
	@"mingw32-make.exe"  -j 2 -f "modmedia.mk" clean
