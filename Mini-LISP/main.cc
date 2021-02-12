int main(int argc, char **argv) {
  try {
loop:
S s = read();
S e = eval(s);
print(s);
goto loop;
  } catch (int e) {

  }
	return 0;
}
