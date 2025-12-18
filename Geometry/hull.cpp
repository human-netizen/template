struct Point {
    ll x, y;
    bool operator<(const Point &other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
    bool operator==(const Point &other) const {
        return x == other.x && y == other.y;
    }
};
 
static inline ll dot (const Point &a, const Point &b) {
    return a.x * 1LL * b.x + a.y * 1LL * b.y;
}

static inline ll cross(const Point &a, const Point &b, const Point &c) {
    return (b.x - a.x) * 1LL * (c.y - a.y) - (b.y - a.y) * 1LL * (c.x - a.x);
}
 
vector<Point> convex_hull_including_collinear(vector<Point> pts) {
    int n = (int)pts.size();
    if (n <= 1) return pts;
    sort(pts.begin(), pts.end());
    vector<Point> lower, upper;

    for (const auto &p : pts) {
        while (lower.size() >= 2 && cross(lower[lower.size()-2], lower.back(), p) < 0)  lower.pop_back();
        lower.push_back(p);
    }

    for (int i = n - 1; i >= 0; --i) {
        const auto &p = pts[i];
        while (upper.size() >= 2 && cross(upper[upper.size()-2], upper.back(), p) < 0) upper.pop_back();
        upper.push_back(p);
    }

    lower.pop_back(); upper.pop_back();
    lower.insert(lower.end(), upper.begin(), upper.end());
    return lower;
}

ll area_of_pts(auto pts){
    ll area = 0 ;
    ll n = pts.size() ;
    for(int i = 0 ; i < n-1 ; i++) area += pts[i].x * pts[i+1].y - pts[i+1].x * pts[i].y ;
    area += pts[n-1].x * pts[0].y - pts[0].x * pts[n-1].y ;
    return area ;
}
