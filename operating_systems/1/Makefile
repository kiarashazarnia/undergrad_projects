all: client server
	@echo "build success!"

client:
	@gcc -g -w common/*.c client.c -o client.out

server:
	@gcc -g -w common/*.c server.c -o server.out

clean:
	@rm -rf *.out
