DIRECTORIES = $(wildcard */)

all:
	for DIR in $(DIRECTORIES); do \
		cd $$DIR; \
		ln -sf ../sub_makefile makefile; \
		make; \
		cd -; \
	done

clean:
	for DIR in $(DIRECTORIES); do \
		cd $$DIR; \
		make clean; \
		cd -; \
	done

run:
	for DIR in $(DIRECTORIES); do \
		cd $$DIR; \
		./unittest; \
		cd -; \
	done
