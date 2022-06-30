const long long k1 = 1117;
const long long k2 = 1e9 + 7;

class Solution {
 private:
  unordered_map<int, string> dataBase;
  unordered_map<string, int> urlToKey;

 public:
  Solution() {}

  string encode(string longUrl) {
    if (urlToKey.count(longUrl) > 0) {
      return string("http://tinyurl.com/") + to_string(urlToKey[longUrl]);
    }
    long long key = 0, base = 1;
    for (auto c : longUrl) {
      key = (key + c * base) % k2;
      base = (base * k1) % k2;
    }
    while (dataBase.count(key) > 0) {
      key = (key + 1) % k2;
    }
    dataBase[key] = longUrl;
    urlToKey[longUrl] = key;
    return string("http://tinyurl.com/") + to_string(key);
  }

  string decode(string shortUrl) {
    int p = shortUrl.rfind('/') + 1;
    int key = stoi(shortUrl.substr(p, int(shortUrl.size()) - p));
    return dataBase[key];
  }
};
