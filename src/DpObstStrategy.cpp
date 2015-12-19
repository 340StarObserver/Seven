#include "DpObstStrategy.h"

#include "Stack.h"

using std::pair;

namespace Seven
{
	// calculate the dp dir table
	/*
	1. create prefix sum array b[] for cost[]
		{
			b[0]=0
			b[i+1]=b[i]+cost[i]
		}
	2. create dp struct, and origin it:
		{
			dp[i][j] = -1, when i!=j
			dp[i][j] = cost[i], when i==j
		}
	3. create dp dir struct:
		{
			dir[i][j] = -1, when i!=j
			dir[i][j] = i, when i==j
		}
	4. start dynamic programing, the idea is:
		{
			note w(i,j) is the smallest cost of { node[i],node[i+1],...node[j] } in the obst
			note B(i,j) is the sum of cost[i],cost[i+1]...cost[j],
			B(i,j) = b[j+1] - b[i]
			w(i,j) = min{ B(i,j) + w(i,k-1) + w(k+1,j) }, dir[i][j-1]<=k<=dir[i+1][j]
		}
	5. clean heap data
	6. return dp dir struct
	*/
	int ** DpObstStrategy::dpDirTable(float * cost, unsigned int N)const
	{
		float ** dp = new float*[N];
		int ** dir = new int*[N];
		float * b = new float[N + 1];
		b[0] = 0;
		for (unsigned int i = 0; i < N; i++)
		{
			dp[i] = new float[N];
			dir[i] = new int[N];
			for (unsigned int j = 0; j < N; j++)
			{
				dp[i][j] = -1;
				dir[i][j] = -1;
			}
			dp[i][i] = cost[i];
			dir[i][i] = i;
			b[i + 1] = b[i] + cost[i];
		}

		float t, t1, t2, t3;
		for (unsigned int i = N - 2; i >= 0 && i<N; i--)
		{
			for (unsigned int j = i + 1; j < N; j++)
			{
				t1 = b[j + 1] - b[i];
				for (int k = dir[i][j - 1]; k <= dir[i + 1][j]; k++)
				{
					t2 = (i + 1 <= (unsigned int)k ? dp[i][k - 1] : 0);
					t3 = ((unsigned int)k + 1 <= j ? dp[k + 1][j] : 0);
					t = t1 + t2 + t3;
					if (dp[i][j]<0 || dp[i][j]>t)
					{
						dp[i][j] = t;
						dir[i][j] = k;
					}
				}
			}
		}

		for (unsigned int i = 0; i < N; i++)
			delete[]dp[i];
		delete[]dp;
		delete[]b;

		return dir;
	}


	// calculate the pre order of nodes based on the dp dir table
	/*
	use DFS to find the pre order of nodes
	{
		1. create the result array res[]
		2. create a stack<pair<int,int>> S
		3. create a origin state pair(0,N-1),and push it to S
		4. while( S is not empty)
			{
				pop its top node,and note is as "cur"
				note p = cur.first
				note q = cur.second
				note k = dir[p][q]
				add k to the res[]
				if( k+1 <= q): then push pair(k+1,q) to S
				if( p <= k-1): then push pair(p,k-1) to S
			}
		5. return res[]
	}
	*/
	int * DpObstStrategy::findPreRootsOrder(int ** dir, unsigned int N)const
	{
		int * res = new int[N];

		Stack<pair<int, int>> S;

		pair<int, int> origin, next;
		origin.first = 0;
		origin.second = N - 1;
		S.push(origin);

		unsigned int i = 0;
		int p, q, k;
		while (!S.empty())
		{
			pair<int, int> cur = *(S.peek());
			S.pop();
			p = cur.first;
			q = cur.second;
			k = dir[p][q];
			res[i++] = k;
			if (k + 1 <= q)
			{
				next.first = k + 1;
				next.second = q;
				S.push(next);
			}
			if (p <= k - 1)
			{
				next.first = p;
				next.second = k - 1;
				S.push(next);
			}
		}

		return res;
	}


	// calculate the best root list according to the costs
	/*
	1. calculate the dp dir table
	2. calculate the pre order of nodes based on the dp dir table
	3. clean rubbish
	4. return result
	*/
	int * DpObstStrategy::strategy(float * cost, unsigned int N)const
	{
		int ** dir = dpDirTable(cost, N);
		int * res = findPreRootsOrder(dir, N);

		for (unsigned int i = 0; i < N; i++)
			delete[]dir[i];
		delete[]dir;

		return res;
	}

}