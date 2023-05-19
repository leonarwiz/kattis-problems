#include<vector>
#include<iostream>
#include<set>
#include<string>
#include<cmath>
using namespace std;


typedef long long ll;
#define point pair<ll, ll>
#define x first
#define y second 

point origin;

ll dst(const point& a, const point& b){
    return abs(a.x - b.x) + abs(a.y - b.y);
}

ll cross_product(const point& a, const point& b){
    return 1LL * a.x * b.y - 1LL * a.y * b.x;
}

bool convex(const point& a, const point& b, const point& c){
    point ab = make_pair(b.x-a.x, b.y-a.y);
    point bc = make_pair(c.x - b.x, c.y - b.y);

    return cross_product(ab, bc) > 0;
}

bool compare_angles(const point& a, const point& b){
    if(convex(origin, a, b)){
        return true;
    }else if(convex(origin, b, a)){
        return false;
    }else{
        ll distA = dst(origin, a);
        ll distB = dst(origin, b);

        return distA < distB;
    }
}

vector<point> convex_hull(vector<point> points){
    int idx_bottom_right = 0;
    int n = points.size();
    int idx = 1;

    point p;
    point bottom_right = points[idx_bottom_right];
    while(idx < n){
        p = points[idx];
        if(make_pair(p.y, -p.x) < make_pair(bottom_right.y, -bottom_right.x)){
            bottom_right = p;
            idx_bottom_right = idx;
        }
        idx++;
    }
    swap(points[0], points[idx_bottom_right]);
    origin = bottom_right;

    sort(points.begin()+1, points.end(), compare_angles);

    vector<point> st;
    st.push_back(points[0]);
    st.push_back(points[1]);

    int pointer = 2;
    while(pointer < n){
        int top = st.size();
        point a = st[top-2];
        point b = st[top-1];
        point c = points[pointer];

        if(convex(a, b, c)){
            st.push_back(c);
            pointer++;
        }else{
            st.pop_back();
            if(st.size() < 2){
                st.push_back(c);
                pointer++;
            }
        }
    }


    return st;
}

ll getArea(vector<point> hull, ll lo, ll mi, ll hi){
    ll n = hull.size();

    lo = (lo + n) % n;
    mi = (mi + n) % n;
    hi = (hi + n) % n;

    point a = hull[lo];
    point b = hull[mi];
    point c = hull[hi];
    ll area = 0;
    area += (a.x*b.y + b.x*c.y + c.x*a.y);
    area -= (a.x*c.y + c.x*b.y + b.x*a.y); 

    return abs(area);
}

int main(){
    ll n;
    cin >> n;
    set<point> pointSet;
    while(n--){
        point p;
        cin >> p.x >> p.y;
        pointSet.insert(p);
    }   
    vector<point> points(pointSet.begin(), pointSet.end());
    vector<point> hull = convex_hull(points);
    n = hull.size();

    ll maxArea = 0;
    // For each start point
    for(ll lo = 0; lo < n; lo++) {
        ll hi = (lo + 1) % n;

        // Initial mid points
        ll mid1 = (hi + 1) % n;
        ll mid2 = (mid1 + 1) % n;

        // For each end point
        while (hi != lo) {
            hi = (hi + 1) % n;

            // Find the point that forms the maximum area triangle with lo and hi
            while (true) {
                ll next_mid = (mid1 + 1) % n;
                if (getArea(hull, lo, next_mid, hi) > getArea(hull, lo, mid1, hi)) {
                    mid1 = next_mid;
                } else {
                    break;
                }
            }

            // Check mid2 similarly
            while (true) {
                ll next_mid = (mid2 + 1) % n;
                if (getArea(hull, lo, next_mid, hi) > getArea(hull, lo, mid2, hi)) {
                    mid2 = next_mid;
                } else {
                    break;
                }
            }

            // Take the maximum of the two
            maxArea = max(maxArea, max(getArea(hull, lo, mid1, hi), getArea(hull, lo, mid2, hi)));
        }
    }

    cout << fixed;
    cout.precision(6);
    cout << maxArea / 2.0 << endl;

}