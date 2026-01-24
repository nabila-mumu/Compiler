int x,y,z;
int foo(){
	int a;
	x=5;
	y=6;
	a = x+y;
	a++;
	return a;
}
int main(){
	z=9;
	y=foo();
	z = z+y;
	println(z);
	return 0;
}