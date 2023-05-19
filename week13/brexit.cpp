#include<iostream>
#include<vector>
#include<queue>

using namespace std;

class Country{
public:
    int id;
    bool is_leaving;
    int num_neighbors;
    int num_left_neighbots;
    vector<int> neighbors;
};

void union_member(Country& c1, Country& c2){
    c1.num_neighbors++; c2.num_neighbors++;
    c1.neighbors.push_back(c2.id);
    c2.neighbors.push_back(c1.id);
}

bool leave(Country& c){
    if(c.num_left_neighbots * 2 >= c.num_neighbors && !c.is_leaving){
        c.is_leaving = true;
        return true;
    }

    return false;
}

int main(){
    int c, p, l, x;
    cin >> c >> p >> l >> x;
    l--;    x--;
    vector<Country> countries(c);
    int id = 0;
    for(auto& c : countries){
        c.id = id++;
        c.is_leaving = false;
        c.num_neighbors = 0;
        c.num_left_neighbots = 0;
    }

    while(p--){
        int n1, n2;
        cin >> n1 >> n2;
        n1--;   n2--;
        union_member(countries[n1], countries[n2]);
    }

    queue<int> q;
    countries[l].is_leaving = true;
    for(auto& c : countries[l].neighbors){
        countries[c].num_left_neighbots++;
        if(leave(countries[c])){
            q.push(c);
        }
    }

    while(!q.empty()){
        int curr = q.front();   q.pop();
        for(auto n : countries[curr].neighbors){
            countries[n].num_left_neighbots++;
            if(leave(countries[n])){
                q.push(n);
            }
        }
    }

    if(countries[x].is_leaving){
        printf("leave\n");
    }else{
        printf("stay\n");
    }
}