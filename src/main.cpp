#include <iostream>
#include "virtual.hpp"
#include "virtuallib.hpp"

int main() {
	printf("test -- virtual -- \n");
	Tests::test_Virtual();
	printf("\ntest -- virtual::lib --\n");
	Tests::test_Virtual_Lib();
}