compile:
	gcc control.c -o control
	gcc write.c -o write

clean:
	rm *# *~ control write
