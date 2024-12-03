#include <bits/stdc++.h>

using namespace std;

pair<int, vector<pair<string, int>>> getMaximumProfit(vector<int> stock_prices) {
  int days = stock_prices.size();
  vector<int> f(days + 1), g(days + 1);
  f[0] = -1e9;
  g[0] = 0;

  // vector<bool> fIsBuy(days + 1); // fIsBuy[i] = true if leading to f[i], we bought a stock at day i
  // vector<bool> gIsSell(days + 1); // gIsSell[i] = true if leading to g[i], we sold a stock at day i

  for (int i = 1; i <= days; i++) {
    f[i] = max(f[i - 1], g[i - 1] - stock_prices[i - 1]);
    g[i] = max(g[i - 1], f[i - 1] + stock_prices[i - 1]);
    // if (f[i - 1] > g[i - 1] - stock_prices[i - 1]) {
    //   f[i] = f[i - 1];
    //   fIsBuy[i] = false;
    // } else {
    //   f[i] = g[i - 1] - stock_prices[i - 1];
    //   fIsBuy[i] = true;
    // }
    // if (g[i - 1] > f[i - 1] + stock_prices[i - 1]) {
    //   g[i] = g[i - 1];
    //   gIsSell[i] = false;
    // } else {
    //   g[i] = f[i - 1] + stock_prices[i - 1];
    //   gIsSell[i] = true;
    // }
  }

  vector<pair<string, int>> actions; // {{"buy", 2}, {"sell", 3}}

  int numberOfStocks = 0;
  for (int i = days; i >= 1; i--) {
    if (numberOfStocks == 1) {
      if (f[i] != f[i - 1]) {
        numberOfStocks = 0;
        actions.push_back(make_pair("buy", i));
      }
    } else if (numberOfStocks == 0) {
      if (g[i] != g[i - 1]) {
        numberOfStocks = 1;
        actions.push_back(make_pair("sell", i));
      }
    }
  }

  reverse(actions.begin(), actions.end());

  return make_pair(g[days], actions);
}

int main() {
  // vector<int> prices = {18,9,10,4,15,1,13};
  vector<int> prices = {5, 10, 15, 20, 23};
  // vector<int> prices = {50, 40, 30, 20, 10};

  pair<int, vector<pair<string, int>>> res = getMaximumProfit(prices);
  int profit = res.first;
  vector<pair<string, int>> actions = res.second;

  cout << "Maximum profit: " << profit << '\n';
  for (int i = 0; i < actions.size(); i++) {
    cout << actions[i].first << " at day " << actions[i].second << '\n';
  }
  return 0;
}