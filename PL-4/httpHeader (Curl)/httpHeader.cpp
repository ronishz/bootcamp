#include<iostream>
using namespace std;
#include<stdlib.h>

int main(){

	system("curl -vis www.google.com -o httpHeader.txt > /dev/null 2>&1");
	return 0;
}
