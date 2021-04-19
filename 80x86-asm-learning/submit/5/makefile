SC=g++ -static

def:
	${SC} -c impl.s && ${SC} -c main.s
	${SC} -o main.exe main.o impl.o

clean:
	rm -f *.o *.exe
