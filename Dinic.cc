template< typename T >
struct Dinic{
	struct edge {
		int to;
		T cap;
		int rev;
	};
	const T INF;
	vector<vector<edge>> G;
	vector<int> dist;

	explicit Dinic(int V) : INF(numeric_limits< T >::max()), G(V), dist(V, -1){}

	void add_edge(int from, int to, T cap){
		G[from].emplace_back((edge){to, cap, (int)G[to].size()});
		G[to].emplace_back((edge){from, 0, (int)G[from].size() - 1});
	}

	bool build_level_graph(int s, const int t){
		dist.assign(G.size(), -1);
		queue<int> q;
		q.push(s);
		dist[s] = 0;
		while(!q.empty()){
			int v = q.front(); q.pop();
			for(auto &e : G[v]){
				if(e.cap > 0 && dist[e.to] == -1){
					dist[e.to] = dist[v] + 1;
					q.push(e.to);
				}
			}
		}
		return (dist[t] != -1);
	}

	T find_augment_path(int s, const int t, T flow){
		if(s == t) return flow;
		for(auto &e : G[s]){
			if(dist[e.to] > dist[s] && e.cap > 0){
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
		while(build_level_graph(s, t)){
			while(true){
				T f = find_augment_path(s, t, INF);
				if(f == 0) break;
				flow += f;
			}
		}
		return flow;
	}
};
