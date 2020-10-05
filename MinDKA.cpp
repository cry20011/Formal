#include <iostream>
#include <vector>
#include <set>
#include <algorithm>





std::vector<std::vector<std::pair<int, char>>> edges;
std::vector<char> alph;
std::vector<int> group;
int n_groups = 0;
int n_vert, n_lett;


void enter_edges(){
	std::cout << "enter edges\n";
	edges.push_back({});
	
	for(int i = 1; i <= n_vert; ++i){
		std::cout << i << " : ";
	
		int next_vert = 0;
		char letter;
		edges.push_back({});
	
		for(int j = 0; j < alph.size(); ++j){
			std::cin >> next_vert;
			edges[i].push_back({next_vert, alph[j]});
		}
	}
}

void enter_alph(){
	std::cout << "enter alphabet\n";
	for(int i = 0; i < n_lett; ++i){
		char x = 0;
		std::cin >> x;
		alph.push_back(x);
	}
}

void enter_group(){
	group.push_back(0);
	int g = 0;
	std::cout << "enter 1 if vert final, 2 else\n";
	for(int i = 1; i <= n_vert; ++i){
		std::cin >> g;
		group.push_back(g);
	}
	n_groups = 2;
}


void print_egdes(){	
	for(int i = 1; i < edges.size(); ++i){
		std::cout << i << ": ";
		for(int j = 0; j < edges[i].size(); ++j){
			std::cout << edges[i][j].first << edges[i][j].second << ' ';
		}
		std::cout << '\n';
	}
}



int make_vert_from_vect(const std::vector<int>& v){
	int new_vert = 0;
	for(const auto& x : v){
		new_vert = new_vert * 10 + x;
	}
	return new_vert;
}


void find_equ_classes(std::vector<int>& new_group, std::vector<int>& all_equ_classes){
		
		for(int i = 1; i < edges.size(); ++i){
			std::vector<int> equ_classes;
			
			for(int j = 0; j < edges[i].size(); ++j){
				equ_classes.push_back(group[edges[i][j].first]);
			}
			int classes = make_vert_from_vect(equ_classes);

			new_group[i] = classes;
			if(std::find(all_equ_classes.begin(), all_equ_classes.end(), classes) == all_equ_classes.end()){
				all_equ_classes.push_back(classes);
			}
		}
}

void num_equ_classes(std::vector<int>& new_group, std::vector<int>& all_equ_classes){
	int i = 1;
		for(const auto& x : all_equ_classes){
			for(int j = 1; j < new_group.size(); ++j){
				if(x == new_group[j]){
					new_group[j] = i;
				}
			}
			++i;
		}
}


void build_min_DKA(){

	int new_n_groups = n_groups;
	int n_iter = 0;

	printf("vert: ");
	for(int i = 1; i <= n_vert; ++i){
		printf("%4d", i);
	}printf("\n");

	do{
		++n_iter;
		n_groups = new_n_groups;

		std::vector<int> new_group(n_vert + 1);
		std::vector<int> all_equ_classes;

		find_equ_classes(new_group, all_equ_classes);
		new_n_groups = all_equ_classes.size();

		num_equ_classes(new_group, all_equ_classes);		

		printf("Iter%d:", n_iter);
		for(int i = 1; i < new_group.size(); ++i){
			printf("%4d", new_group[i]);
		}printf("\n");

		group = std::move(new_group);
	}while(new_n_groups > n_groups);
}




int main(){

	std::cout << "enter n_vert and n_lett\n";
	std::cin >> n_vert >> n_lett; 

	enter_alph();
	enter_edges();
	enter_group();


	build_min_DKA();


//	print_egdes();

/*
Test1;
9 2
a b
2 4
3 5
1 6
5 7
6 8
4 9
8 1
9 2
7 3
1 2 2 2 1 2 2 2 1

Test2;
8 2
a b
2 8
3 7
3 4
3 5
4 6
7 8
2 6
8 8
2 2 2 2 1 1 1 1
*/




}