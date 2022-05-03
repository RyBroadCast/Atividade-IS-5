bin: main.c
	gcc $< -o $@ -pthread
.PHONY: run class

run:
	./bin
clean:
	rm bin
