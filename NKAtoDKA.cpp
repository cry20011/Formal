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

int make_vert_from_set(const std::set<int>& s){
	int new_vert = 0;
	for(const auto& x : s){
		new_vert = new_vert * 10 + x;
	}
	return new_vert;
}


void make_new_vert(int curr_vert, char letter, std::deque<int>& d, std::vector<int>& been_vert, std::set<int>& set_next_vert){
	
	std::set<int> s = std::set<int>();
	for(int i = 0; i < edges[curr_vert].size(); ++i){
		if(edges[curr_vert][i].second == letter){
			s.insert(edges[curr_vert][i].first);
			
		}
	}
	for(const auto& x : s){
		set_next_vert.insert(x);
	}
}


void print_vert_DKA(std::deque<int>& d, std::vector<int>& been_vert){

	int curr_vert = d.front();
	d.pop_front();
	printf("%10d", curr_vert);


	for(int i = 0; i < alph.size(); ++i){
		int curr_vert_copy = curr_vert;
		std::set<int> set_next_vert;

		while(curr_vert_copy){
			int end = curr_vert_copy % 10;
			curr_vert_copy /= 10;
				
			make_new_vert(end, alph[i], d, been_vert, set_next_vert);
		}
	
		if(set_next_vert.size() > 0){
			int next_v = make_vert_from_set(set_next_vert);
			printf("%10d", next_v);
		
			if(std::find(been_vert.begin(), been_vert.end(), next_v) == been_vert.end()){
				d.push_back(next_v);
				been_vert.push_back(next_v);
			}
		}else{
			printf("%10c", 'X');
		}
	}

	printf("\n");
}



void build_DKA(){
	std::deque<int> d;
	std::vector<int> been_vert;


	printf("%10c", 'V');
	for(int i = 0; i < alph.size(); ++i){
		printf("%10c", alph[i]);
	}
	std::cout << '\n';

	int curr_vert = 1;
	d.push_back(curr_vert);
	been_vert.push_back(curr_vert);


	while(d.size() != 0){
		print_vert_DKA(d, been_vert);
	}
	
}

void enter_edges(int n_vert){
	std::cout << "enter edges\n";
	edges.push_back({});
	
	for(int i = 1; i <= n_vert; ++i){
		std::cout << i << " : ";
	
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
}
