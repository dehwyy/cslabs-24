namespace rsa {
long Encode(long message, long e, long n);
long Decode(long message, long d, long n);
void RunExample();
void RunInteractive();
void RunTask();
}  // namespace rsa
