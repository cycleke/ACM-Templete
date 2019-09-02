const int MAXN = 4 * 1e5 + 3;
const double PI = acos(-1);
complex<double> a[MAXN], b[MAXN];

int n, bit;
int rev[MAXN];

void fft(complex<double> *a, int sign) {
  for (int i = 0; i < n; ++i)
    if (i < rev[i]) swap(a[i], a[rev[i]]);

  for (int j = 1; j < n; j <<= 1) {
    complex<double> wn(cos(2 * PI / (j << 1)), sign * sin(2 * PI / (j << 1)));
    for (int i = 0; i < n; i += (j << 1)) {
      complex<double> w(1, 0), t0, t1;
      FOR(k, 0, j) {
        t0 = a[i + k];
        t1 = w * a[i + j + k];
        a[i + k] = t0 + t1;
        a[i + j + k] = t0 - t1;
        w *= wn;
      }
    }
  }
  if (sign == -1)
    for (int i = 0; i < n; ++i) a[i] /= n;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n, m, x;
  cin >> n >> m;
  for (int i = 0; i <= n; ++i) {
    cin >> x;
    a[i].real(x);
  }
  for (int i = 0; i <= m; ++i) {
    cin >> x;
    b[i].real(x);
  }

  ::n = 1;
  bit = 0;
  while (::n <= n + m) {
    ::n <<= 1;
    ++bit;
  }
  rev[0] = 0;
  FOR(i, 1, ::n) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
  fft(a, 1);
  fft(b, 1);
  FOR(i, 0, ::n) a[i] *= b[i];
  fft(a, -1);
  FOR(i, 0, n + m + 1) cout << int(a[i].real() + .5) << " ";
  cout << "\n";
  return 0;
}