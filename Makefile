COMPILE_TARGETS=./src/*.c
APPLICATION=application
C_FLAGS=-std=c99 -Wno-missing-braces
LINUX_FLAGS=-lraylib -lGL -lm -lpthread -ldl -lrt -lX11
WINNT_FLAGS=-lraylib -lopengl32 -lgdi32 -lwinmm


default:
	@echo "Targets avalible:"
	@echo "compile"
	@echo "run"
	@echo "clean"

compile: $(COMPILE_TARGETS)
	gcc $(COMPILE_TARGETS) -o ./bin/$(APPLICATION) -O2 $(C_FLAGS) $(LINUX_FLAGS)

run: ./bin/$(APPLICATION)
	./bin/$(APPLICATION)

clean:
	rm ./bin/*

cr:
	make compile
	make run
