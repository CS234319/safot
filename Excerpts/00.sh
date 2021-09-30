% rm -f User.java First.java
echo class User extends Second {} > User.java
echo public class First {} class Second{} > First.java
javac -verbose User.java
