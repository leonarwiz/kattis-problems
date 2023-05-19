#include<vector>
#include<cmath>
#include<algorithm>
#include<iostream>
#include<set>

using namespace std;

#define point pair<int, int>

point origin;

long long cross_product(const point& a, const point& b);

bool convex(const point& a, const point& b, const point& c);

bool compare_angles(const point& a, const point& b);

vector<point> convex_hull(vector<point> points){
    int n = points.size();

    if(n < 3){
        return points;
    }

    //take the bottom right point (a point we know to lie on the convex hull for sure)
    int index_lowest = 0;
    for(int i=1;i<n;++i){
        if(make_pair(points[i].second, -points[i].first) < make_pair(points[index_lowest].second, -points[index_lowest].first)){
            index_lowest = i;
        }
    }

    swap(points[0], points[index_lowest]);
    origin = points[0];

    //sort the points array
    sort(points.begin()+1, points.end(), compare_angles);

    //st used as a stack to find the points of the convex hull
    vector<point> st;
    st.push_back(points[0]);
    st.push_back(points[1]);

    //pointer : how far we got through the sorted array of points already
    int pointer = 2;
    while(pointer < n){
        point a = st[st.size()-2];
        point b = st[st.size()-1];
        point c = points[pointer];

        if(convex(a, b, c)){
            //pop middle point
            st.push_back(c);
            ++pointer;
        }else{
            st.pop_back();
            if(st.size() < 2){
                st.push_back(c);
                ++pointer;
            }
        }
    }
    return st;

}

long long cross_product(const point& a, const point& b){
    return 1LL*a.first * b.second -1LL* a.second * b.first;
}

bool convex(const point& a, const point& b, const point& c){
    const point ab = make_pair(b.first - a.first, b.second - a.second);
    const point bc = make_pair(c.first - b.first, c.second - b.second);

    return cross_product(ab, bc) > 0;
}

bool compare_angles(const point& a, const point& b){
    if(convex(origin, a, b)){
        return true;
    }else if(convex(origin, b, a)){
        return false;
    } else{
        // the two points are colinear with the origin : compare the distance

        const int distA = abs(a.first - origin.first) + abs(a.second - origin.second);
        const int distB = abs(b.first - origin.first) + abs(b.second - origin.second);

        return distA < distB;
     }
}

int main(){
    int n;
    while(cin >> n && n != 0){
        set<point> pointSet;
        while(n--){
            point p ;
            cin >> p.first >> p.second ;
            pointSet.insert(p);
        }

        vector<point> points(pointSet.begin(), pointSet.end());

        vector<point> res = convex_hull(points);
        printf("%d\n", res.size());
        for(auto p : res){
            printf("%d %d\n", p.first, p.second);
        }
    }
}
