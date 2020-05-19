void
fibonacci(Monitor *mon, int s)
{
	unsigned int i, n, nx, ny, nw, nh;
	Client *c;

	for (n = 0, c = nexttiled(mon->clients); c; c = nexttiled(c->next), n++);
	if (n == 0)
		return;

	nx = mon->wx + mon->gappov;
	ny = mon->gappoh;
	nw = mon->ww - 2*mon->gappov;
	nh = mon->wh - 2*mon->gappoh;

	for (i = 0, c = nexttiled(mon->clients); c; c = nexttiled(c->next)) {
		if ((i % 2 && nh / 2 > 2 * c->bw)
		   || (!(i % 2) && nw / 2 > 2 * c->bw)) {
			if (i < n - 1) {
				if (i % 2)
					nh = (nh - mon->gappih) / 2;
				else
					nw = (nw - mon->gappiv) / 2;
				if ((i % 4) == 2 && !s)
					nx += nw + mon->gappiv;
				else if ((i % 4) == 3 && !s)
					ny += nh + mon->gappih;
			}
			if ((i % 4) == 0) {
				if (s)
					ny += nh + mon->gappih;
				else
					ny -= nh + mon->gappih;
			}
			else if ((i % 4) == 1)
				nx += nw + mon->gappiv;
			else if ((i % 4) == 2)
				ny += nh + mon->gappih;
			else if ((i % 4) == 3) {
				if (s)
					nx += nw + mon->gappiv;
				else
					nx -= nw + mon->gappiv;
			}
			if (i == 0) {
				if (n != 1)
					nw = (mon->ww - 2*mon->gappov - mon->gappiv) * mon->mfact;
				ny = mon->wy + mon->gappoh;
			}
			else if (i == 1)
				nw = mon->ww - nw - mon->gappiv - 2*mon->gappov;
			i++;
		}
		resize(c, nx, ny, nw - 2 * c->bw, nh - 2 * c->bw, False);
	}
}

void
dwindle(Monitor *mon)
{
	fibonacci(mon, 1);
}

void
spiral(Monitor *mon)
{
	fibonacci(mon, 0);
}
