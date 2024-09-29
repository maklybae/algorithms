int fastExponent(int x, int n) {
  int r = 1;
  int p = x;
  int e = n;

  while (e > 0) {
    if (e % 2 != 0) {
      r *= p;
    }
    p *= p;
    e /= 2;
  }

  return r;
}