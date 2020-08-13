// huarongdao_solution.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct mn4
{
	int a[4];
};

struct map
{
	int cao;
	int guan;
	int jiang;
	int bing;
	int before1;
	int before2;
	map(int Cao = 0, int Guan = 0, int Jiang = 0, int Bing = 0)
	{
		cao = Cao;
		jiang = Jiang;
		guan = Guan;
		bing = Bing;
	}
};

int findm(vector<map> v, map& m)
{
	for (int i = 0;i < v.size();i++)
	{
		if (v[i].bing == m.bing && v[i].cao == m.cao && v[i].guan == m.guan && v[i].jiang == m.jiang)
		{
			return i;
		}
	}
	return -1;
}

struct mapori
{
	int caom;
	int caon;
	int bingm[4];
	int bingn[4];
	int guanm;
	int guann;
	int jiangm[4];
	int jiangn[4];
};

int getm(int a)
{
	return a / 4;
}
int getn(int a)
{
	return a % 4;
}

int getplace(int m, int n)
{
	return 4 * m + n;
}

int order(int a1, int a2, int a3, int a4)
{
	int a[4];
	a[0] = a1;
	a[1] = a2;
	a[2] = a3;
	a[3] = a4;
	int tem;
	int re = 0;
	for (int i = 3;i >= 0;i--)
	{
		for (int j = 0;j < i;j++)
		{
			if (a[j] < a[j + 1])
			{
				tem = a[j];
				a[j] = a[j + 1];
				a[j + 1] = tem;
			}
		}
		re *= 20;
		re += a[i];
	}
	return re;
}


struct point
{
	int m;
	int n;
	point(int M = 0, int N = 0)
	{
		m = M;
		n = N;
	}
};

vector<point> Cao = { point(0,0) ,point(0,1),point(1,0),point(1,1)};
vector<point> Guan = { point(0,0),point(0,1) };
vector<point> Bing = { point(0,0) };
vector<point> Jiang = { point(0,0),point(1,0) };

void replace(int m, int n, int mask[5][4], vector<point> type, int a)
{
	for (int i = 0;i < type.size();i++)
	{
		mask[m + type[i].m][n + type[i].n] = a;
	}
}

bool test_field(int m, int n, int mask[5][4], vector<point> type, int a)
{
	for (int i = 0;i < type.size();i++)
	{
		if (m+type[i].m<0||m+type[i].m>4|| n + type[i].n<0|| n + type[i].n>3|| mask[m + type[i].m][n + type[i].n] != a)
		{
			return false;
		}
	}
	return true;
}

vector<point> des(int m,int n,int Mask[5][4],vector<point> type)
{
	static vector<point> direction = { point(0,-1),point(1,0),point(-1,0),point(0,1) };
	int mask[5][4];
	int pos[5][4];
	for (int i = 0;i < 5;i++)
	{
		for (int j = 0;j < 4;j++)
		{
			mask[i][j] = Mask[i][j];
			pos[i][j] = 0;
		}
	}
	pos[m][n] = 1;
	vector<point> re;
	replace(m, n, mask, type, 0);
	for (int i = 0;i < 4;i++)
	{
		if (test_field(m + direction[i].m, n + direction[i].n, mask, type, 0))
		{
			if (pos[m + direction[i].m][n + direction[i].n] != 1)
			{
				pos[m + direction[i].m][n + direction[i].n] = 1;
				re.push_back(point(m + direction[i].m, n + direction[i].n));
				for (int j = 0;j < 4;j++)
				{
					if (test_field(m + direction[i].m+direction[j].m, n + direction[i].n+direction[j].n, mask, type, 0))
					{
						if (pos[m + direction[i].m+ direction[j].m][n + direction[i].n+ direction[j].n] != 1)
						{
							pos[m + direction[i].m + direction[j].m][n + direction[i].n + direction[j].n] = 1;
							re.push_back(point(m + direction[i].m + direction[j].m, n + direction[i].n + direction[j].n));
						}
					}
				}
			}
		}
	}
	return re;
}


void mapmark(int a[5][4], mapori ori)
{
	for (int i = 0;i < 5;i++)
	{
		for (int j = 0;j < 4;j++)
		{
			a[i][j] = 0;
		}
	}
	for (int i = 0;i < 4;i++)
	{
		a[ori.bingm[i]][ori.bingn[i]] = 1;
	}
	for (int i = 0;i < 4;i++)
	{
		a[ori.jiangm[i]][ori.jiangn[i]] = 1;
		a[ori.jiangm[i]+1][ori.jiangn[i]] = 1;
	}
	a[ori.caom][ori.caon] = 1;
	a[ori.caom+1][ori.caon] = 1;
	a[ori.caom][ori.caon+1] = 1;
	a[ori.caom+1][ori.caon+1] = 1;
	
	a[ori.guanm][ori.guann] = 1;
	a[ori.guanm][ori.guann + 1] = 1;
}

void showorimap(mapori ori)
{
	int a[5][4];
	for (int i = 0;i < 5;i++)
	{
		for (int j = 0;j < 4;j++)
		{
			a[i][j] = 0;
		}
	}
	for (int i = 0;i < 4;i++)
	{
		a[ori.bingm[i]][ori.bingn[i]] = 1;
	}
	for (int i = 0;i < 4;i++)
	{
		a[ori.jiangm[i]][ori.jiangn[i]] = 2;
		a[ori.jiangm[i] + 1][ori.jiangn[i]] = 2;
	}
	a[ori.caom][ori.caon] = 4;
	a[ori.caom + 1][ori.caon] = 4;
	a[ori.caom][ori.caon + 1] = 4;
	a[ori.caom + 1][ori.caon + 1] = 4;

	a[ori.guanm][ori.guann] = 3;
	a[ori.guanm][ori.guann + 1] = 3;
	cout << endl;
	for (int i = 0;i < 5;i++)
	{
		for (int j = 0;j < 4;j++)
		{
			cout << a[i][j] << ' ';
		}
		cout << endl;
	}
}


mn4 getmn4(int a)
{
	mn4 re;
	for (int i = 3;i >= 0;i--)
	{
		re.a[i] = a % 20;
		a /= 20;
	}
	return re;
}

map oritomap(mapori &ori)
{
	map re;
	re.cao = getplace(ori.caom, ori.caon);
	re.guan = getplace(ori.guanm, ori.guann);
	re.before1 = -1;
	int tem[4];
	for (int i = 0;i < 4;i++)
	{
		tem[i]= getplace(ori.bingm[i], ori.bingn[i]);
	}
	re.bing = order(tem[0],tem[1],tem[2],tem[3]);
	
	for (int i = 0;i < 4;i++)
	{
		tem[i]= getplace(ori.jiangm[i], ori.jiangn[i]);
	}
	re.jiang = order(tem[0], tem[1], tem[2], tem[3]);
	return re;
}

mapori maptoori(map &m)
{
	mapori re;
	re.caom = getm(m.cao);
	re.caon = getn(m.cao);
	re.guanm = getm(m.guan);
	re.guann = getn(m.guan);
	mn4 tem4 = getmn4(m.bing);
	for (int i = 0;i < 4;i++)
	{
		re.bingm[i] = getm(tem4.a[i]);
		re.bingn[i] = getn(tem4.a[i]);
	}
	tem4 = getmn4(m.jiang);
	for (int i = 0;i < 4;i++)
	{
		re.jiangm[i] = getm(tem4.a[i]);
		re.jiangn[i] = getn(tem4.a[i]);
	}
	return re;
}

vector<map> note[160000];

bool add(map& tem)
{
	int fi = findm(note[tem.bing], tem);
	if (fi==-1)
	{
		note[tem.bing].push_back(tem);
		return true;
	}
	return false;
}

map BFS(map ori)
{
	queue<map> que;
	que.push(ori);
	add(ori);
	map tem;
	int temm;
	int temn;
	vector<point>tempos;
	mapori oritem;
	mn4 tem4;

	map temsub;
	bool judge;
	int before1;
	int before2;
	int mark[5][4];
	while (!que.empty())
	{
		tem = que.front();
		que.pop();
		oritem = maptoori(tem);
		if (oritem.caom == 3 && oritem.caon == 1)
		{
			break;
		}
		mapmark(mark, oritem);
		before1 = tem.bing;
		before2 = findm(note[tem.bing], tem);
		tempos = des(oritem.caom, oritem.caon, mark, Cao);
		temm = oritem.caom;
		temn = oritem.caon;
		for(int i=0;i<tempos.size();i++)
		{
			oritem.caom = tempos[i].m;
			oritem.caon = tempos[i].n;
			temsub = oritomap(oritem);
			temsub.before1 = before1;
			temsub.before2 = before2;
			judge = add(temsub);
			if (judge)
			{
				que.push(temsub);
			}
			
		}
		oritem.caom = temm;
		oritem.caon = temn;
		
		tempos = des(oritem.guanm, oritem.guann, mark, Guan);
		temm = oritem.guanm;
		temn = oritem.guann;
		for (int i = 0;i < tempos.size();i++)
		{
			oritem.guanm = tempos[i].m;
			oritem.guann = tempos[i].n;
			temsub = oritomap(oritem);
			temsub.before1 = before1;
			temsub.before2 = before2;
			judge = add(temsub);
			if (judge)
			{
				que.push(temsub);
			}

		}
		oritem.guanm = temm;
		oritem.guann = temn;
		for (int h = 0;h < 4;h++)
		{
			tempos = des(oritem.bingm[h], oritem.bingn[h], mark, Bing);
			temm = oritem.bingm[h];
			temn = oritem.bingn[h];
			for (int i = 0;i < tempos.size();i++)
			{
				oritem.bingm[h] = tempos[i].m;
				oritem.bingn[h] = tempos[i].n;
				temsub = oritomap(oritem);
				temsub.before1 = before1;
				temsub.before2 = before2;
				judge = add(temsub);
				if (judge)
				{
					que.push(temsub);
				}

			}
			oritem.bingm[h] = temm;
			oritem.bingn[h] = temn;
		}
		for (int h = 0;h < 4;h++)
		{
			tempos = des(oritem.jiangm[h], oritem.jiangn[h], mark, Jiang);
			temm = oritem.jiangm[h];
			temn = oritem.jiangn[h];
			for (int i = 0;i < tempos.size();i++)
			{
				oritem.jiangm[h] = tempos[i].m;
				oritem.jiangn[h] = tempos[i].n;
				temsub = oritomap(oritem);
				temsub.before1 = before1;
				temsub.before2 = before2;
				judge = add(temsub);
				if (judge)
				{
					que.push(temsub);
				}
			}
			oritem.jiangm[h] = temm;
			oritem.jiangn[h] = temn;
		}
	}
	return tem;
}

int main()
{
	mapori ori;
	ori.bingm[0] = 4;
	ori.bingn[0] = 0;
	ori.bingm[1] = 3;
	ori.bingn[1] = 1;
	ori.bingm[2] = 3;
	ori.bingn[2] = 2;
	ori.bingm[3] = 4;
	ori.bingn[3] = 3;
	ori.caom = 0;
	ori.caon = 1;
	ori.guanm = 2;
	ori.guann = 1;
	ori.jiangm[0] = 0;
	ori.jiangn[0] = 0;
	ori.jiangm[1] = 2;
	ori.jiangn[1] = 0;
	ori.jiangm[2] = 0;
	ori.jiangn[2] = 3;
	ori.jiangm[3] = 2;
	ori.jiangn[3] = 3;
	map m = oritomap(ori);
	m.before1 = -1;
	map re = BFS(m);
	vector<map> sta;
	sta.push_back(re);
	while (re.before1!=-1)
	{
		re = note[re.before1][re.before2];
		sta.push_back(re);
	}
	for (int i = sta.size() - 1;i >= 0;i--)
	{
		ori = maptoori(sta[i]);
		showorimap(ori);
	}
	cout << sta.size();
}


