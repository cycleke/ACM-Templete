int exgcd(int a, int b, int &x, int &y) {
  if (b == 0) return x = 1, y = 0, a;
  int g = exgcd(b, a % b, y, x);
  y -= a / b * x;
  return g;
}
