#include <cstdio>
using namespace std;
#define ri register int
const int MOD = 998244353;
int t, typ, n, l, r, k, ans, c, cc, inv[100005];
inline void mo(int &x)
{
	if (x >= MOD)
		x -= MOD;
	if (x < 0)
		x += MOD;
}
inline int ksm(int b, int p)
{
	int a = 1;
	while (p)
	{
		if (p & 1)
			a = 1ll * a * b % MOD;
		b = 1ll * b * b % MOD;
		p = p >> 1;
	}
	return a;
}
int main()
{
	for (ri i = 1; i <= 100002; i++)
		inv[i] = ksm(i, MOD - 2);
	for (scanf("%d", &t); t; t--)
	{
		scanf("%d", &typ);
		if (typ == 1)
		{
			scanf("%d%d", &n, &k);
			if (n <= k)
				printf("%d\n", ksm(2, n));
			else
			{
				ans = 0;
				c = 1;
				for (ri i = 0; i <= k; i++)
				{
					ans += c;
					mo(ans);
					c = 1ll * c * (n - i) % MOD * inv[i + 1] % MOD;
				}
				printf("%d\n", ans);
			}
		}
		else
		{
			scanf("%d%d%d", &l, &r, &k);
			ans = 0;
			if (r <= k)
			{
				c = ksm(2, l);
				for (ri i = l; i <= r; i++)
				{
					ans += c;
					mo(ans);
					c = c << 1;
					mo(c);
				}
			}
			else
			{
				if (l <= k)
				{
					c = ksm(2, l);
					for (ri i = l; i <= k; i++)
					{
						ans += c;
						mo(ans);
						c = c << 1;
						mo(c);
					}
					l = k + 1;
				}
				c = r + 1;
				cc = l;
				for (ri i = 0; i <= k; i++)
				{
					ans += c - cc;
					mo(ans);
					c = 1ll * c * (r - i) % MOD * inv[i + 2] % MOD;
					cc = 1ll * cc * (l - i - 1) % MOD * inv[i + 2] % MOD;
				}
			}
			printf("%d\n", ans);
		}
	}
}
