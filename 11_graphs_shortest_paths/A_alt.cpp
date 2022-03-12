#include <iostream>
#include <queue>
#include <set>
#include <vector>

using namespace std;

int const dx_size = 8;

int dx[] = {2, 2, -2, -2, 1, 1, -1, -1};
int dy[] = {-1, 1, 1, -1, 2, -2, 2, -2};

struct Vertex {
  int x;
  int y;
  vector<pair<int, int>> path;

  Vertex(int x, int y, vector<pair<int, int>> path = vector<pair<int, int>>(0))
      : x(x), y(y), path(path) {}

  bool operator<(const Vertex &o) const {
    return x < o.x || (x == o.x && y < o.y);
  }
};

vector<pair<int, int>> bfs(Vertex start, Vertex end, int n) {
  set<pair<int, int>> used;

  queue<Vertex> q;
  q.push(start);

  while (!q.empty()) {
    Vertex vert = q.front();
    q.pop();

    int x = vert.x;
    int y = vert.y;
    vector<pair<int, int>> path = vert.path;

    if (x == end.x && y == end.y) {
      path.push_back({x, y});
      return path;
    }
    if (used.find({x, y}) == used.end()) {
      used.insert({x, y});

      for (int i = 0; i < 8; ++i) {
        int x1 = x + dx[i];
        int y1 = y + dy[i];

        if (x1 > 0 and y1 > 0 and x1 <= n and y1 <= n and
            (used.find({x1, y1}) == used.end())) {
          vector<pair<int, int>> new_path = path;
          new_path.push_back({x, y});
          q.push({x1, y1, new_path});
        }
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int n, x1, y1, x2, y2;
  cin >> n >> x1 >> y1 >> x2 >> y2;

  Vertex start = {x1, y1};
  Vertex end = {x2, y2};

  vector<pair<int, int>> path = bfs(start, end, n);

  cout << path.size() << '\n';
  for (pair<int, int> &el : path) {
    cout << el.first << ' ' << el.second << '\n';
  }

  return 0;
}
