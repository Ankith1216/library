template< typename T >
struct FordFulkerson{
	struct edge {
		int to;
		T cap;
		int rev;
	};
	const T INF;
	vector<vector<edge>> G;
	vector<bool> vis;


	explicit FordFulkerson(int V) : INF(numeric_limits< T >::max()), G(V), vis(V){}

	void add_edge(int from, int to, T cap){
		G[from].emplace_back((edge){to, cap, (int)G[to].size()});
		G[to].emplace_back((edge){from, 0, (int)G[from].size() - 1});
	}

	T find_augment_path(int s, const int t, T flow){
		if(s == t) return flow;
		vis[s] = true;
		for(auto &e : G[s]){
			if(!vis[e.to] && e.cap > 0){
				T F = find_augment_path(e.to, t, min(flow, e.cap));
				if(F > 0){
					e.cap -= F;
					G[e.to][e.rev].cap += F;
					return F;
				}
			}
		}
		return 0;
	}

	T max_flow(int s, int t){
		T flow = 0;
		while(true){
			for(int i = 0; i < vis.size(); i++) vis[i] = false;
			T f = find_augment_path(s, t, INF);
			if(f == 0) break;
			flow += f;
		}
		return flow;
	}
};
