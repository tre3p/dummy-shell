all: shell

shell: shell.c
	cc shell.c -o shell

clean:
	rm -fr shell