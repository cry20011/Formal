#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <set>

std::vector<std::vector<std::pair<int, char>>> edges;
std::vector<char> alph;

bool operator<(const std::pair<int, char>& x, const std::pair<int, char>& y){
	return x.first < y.first;
}

int new_vert(const std::set<int>& s){
	int new_vert = 0;
	for(const auto& x : s){
		new_vert = new_vert * 10 + x;
	}
	return new_vert;
}



void make_vert(int curr_vert, char letter, std::deque<int>& d, std::vector<int>& been_vert, std::set<int>& set_next_vert){
	
	std::set<int> s = std::set<int>();
	for(int i = 0; i < edges[curr_vert].size(); ++i){
		if(edges[curr_vert][i].second == letter){
			//std::cout << "ZZZZ\n";
			s.insert(edges[curr_vert][i].first);
			
		}
	}
			//std::cout << "aaaaaaaaa" << n_vert << '\n';
	for(const auto& x : s){
		set_next_vert.insert(x);
	}
}


void print_DKA(std::deque<int>& d, std::vector<int>& been_vert){

	int curr_vert = d.front();
	d.pop_front();
	printf("%5d", curr_vert);


	for(int i = 0; i < alph.size(); ++i){
		int curr_vert_copy = curr_vert;
		std::set<int> set_next_vert;

		while(curr_vert_copy){
			int end = curr_vert_copy % 10;
			curr_vert_copy /= 10;

				
			make_vert(end, alph[i], d, been_vert, set_next_vert);
	

		}
		if(set_next_vert.size() > 0){
			int next_v = new_vert(set_next_vert);
			printf("%5d", next_v);
		
			if(std::find(been_vert.begin(), been_vert.end(), next_v) == been_vert.end()){
				d.push_back(next_v);
				been_vert.push_back(next_v);
			}
		}else
			printf("%5c", 'X');
	}
		printf("\n");
}



void build_DKA(){
	std::deque<int> d;
	std::vector<int> been_vert;


	printf("%5c", 'V');
	for(int i = 0; i < alph.size(); ++i){
		printf("%5c", alph[i]);
	}
	std::cout << '\n';

	int curr_vert = 1;
	d.push_back(curr_vert);
	been_vert.push_back(curr_vert);


	while(d.size() != 0){
	//	std::cout << "AAAA\n";
		print_DKA(d, been_vert);
	}
	
}

void enter_edges(int n_vert){
	edges.push_back({});
	std::cout << "enter edges\n";
	for(int i = 1; i <= n_vert; ++i){
		int next_vert = 0;
		char letter;
		edges.push_back({});
		while(next_vert != -1){
			std::cin >> next_vert;
		
			if(next_vert != -1){
				std::cin >> letter;
				edges[i].push_back({next_vert, letter});
			}
		}
	}
	for(int i = 1; i <= n_vert; ++i){
		std::sort(edges[i].begin(), edges[i].end());
	}
}


int main(){

	int n_vert, n_lett;
	std::cout << "enter n_vert and n_lett\n";
	std::cin >> n_vert >> n_lett; 

	std::cout << "enter alphabet\n";
	for(int i = 0; i < n_lett; ++i){
		char x = 0;
		std::cin >> x;
		alph.push_back(x);
	}
	enter_edges(n_vert);


	build_DKA();



/*

	for(int i = 0; i < n_vert; ++i){
		printf("%d : ", i);
		for(int j = 0; j < edges[i].size(); ++j)
			std::cout << edges[i][j].first << ' ' << edges[i][j].second << ' ';
		
		std::cout << '\n';
	}
*/


}	