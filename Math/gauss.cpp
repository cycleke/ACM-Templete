
const double EPS = 1e-9;
const int MAXN = MAX_NODE;
double a[MAXN][MAXN], x[MAXN];
int equ, var;

int gauss() {
  int i, j, k, col, max_r;
  for (k = 0, col = 0; k < equ && col < var; k++, col++) {
    max_r = k;
    for (i = k + 1; i < equ; i++)
      if (fabs(a[i][col]) > fabs(a[max_r][col])) max_r = i;
    if (fabs(a[max_r][col]) < EPS) return 0;

    if (k != max_r) {
      for (j = col; j < var; j++) swap(a[k][j], a[max_r][j]);
      swap(x[k], x[max_r]);
    }

    x[k] /= a[k][col];
    for (j = col + 1; j < var; j++) a[k][j] /= a[k][col];
    a[k][col] = 1;

    for (i = k + 1; i < equ; i++)
      if (i != k) {
        x[i] -= x[k] * a[i][col];
        for (j = col + 1; j < var; j++) a[i][j] -= a[k][j] * a[i][col];
        a[i][col] = 0;
      }
  }

  for (col = equ - 1, k = var - 1; ~col; --col, --k) {
    if (fabs(a[col][k]) > 0) {
      for (i = 0; i < k; ++i) {
        x[i] -= x[k] * a[i][col];
        for (j = col + 1; j < var; j++) a[i][j] -= a[k][j] * a[i][col];
        a[i][col] = 0;
      }
    }
  }

  return 1;
}
