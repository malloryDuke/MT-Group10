driver: Driver.o Book.o Cart.o Inventory.o User.h
	g++ Driver.o Book.o Cart.o Inventory.o User.h -o driver

Book.o: Book.cpp Book.h
	g++ -c Book.cpp

Cart.o: Cart.cpp Cart.h
	g++ -c Cart.cpp

Inventory.o: Inventory.cpp Inventory.h
	g++ -c Inventory.cpp

clean:
	rm *.o driver 
